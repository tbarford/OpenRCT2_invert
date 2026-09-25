# Inverting Track Refactor Plan

## Objective

Refactor the vehicle inversion toggle mechanism and track element clearance modeling to eliminate legacy RCT2 hacks, deduplicate vehicle subposition data, and cleanly centralize track-driven vehicle state transitions across a structured 3-part series of pull requests.

---

## Roadmap Overview (3-PR Series)

1. **PR 1 (Current Focus - Small & Targeted)**: **Centralize & De-hack the Inversion Mechanism**:
   - Centralize track-boundary inversion updates into `Vehicle::UpdateInversionFromTrack(const TrackElement&)`.
   - Replace duplicated inline inversion blocks in `trackMotionForwardsGetNewTrack`, `trackMotionBackwardsGetNewTrack`, and `VehicleCreateCar`.
   - Purge all 25 `carEntry--;` branches from `VehiclePaint.cpp`.
   - Purge all 8 `uninvertingXX` pitch/roll angles from `Angles.h` and update legacy subposition tables in `VehicleSubpositionData.cpp` to use standard angles (`down60`, `left22`, etc.).
   - Verify like-for-like behavior on existing parks with `flyingInversion` track elements.
   - *Scope boundary*: Zero changes to TED clearances, zero subposition table deletions, zero new pieces.
2. **PR 2**: **TED 3-Way Clearances & Inversion Subposition Deduplication**:
   - Overhaul the TED `.clearance` descriptor in `TrackElementDescriptor.h` to support 3 entries (`// upright`, `// inverted`, `// flying`), mirroring `.blockedSegments`.
   - Update `ConstructionClearance.cpp` and `TrackPlaceAction.cpp` to resolve clearances per coaster type (enabling flying-specific clearances, e.g. in-line twist with `z = -16`).
   - With clearances properly abstracted per vehicle type on the same track geometry, deduplicate the track subposition tables in `VehicleSubpositionData.cpp` (redirecting legacy flyer elements in `TrackVehicleInfoListDefault` to standard tables and deleting the duplicate arrays, delivering the large net negative line diff).
3. **PR 3**: **Enable Deduped Inversion Track Pieces in UI & Track Paint Code**:
   - Enable standard inversions (half-loops, corkscrews, inline twists) on Flying Roller Coaster, Lay-Down Roller Coaster, and Multi-Dimension Roller Coaster in their `RideTypeDescriptor`s (`rtd/coaster/*.h`).
   - Implement any missing track paint code / sprite drawing for these coasters on standard inversion pieces.
   - Deprecate/hide duplicate legacy track elements from construction menus.

---

## Architectural Context & Key Design Decisions (For Future Reference)

### 1. Absence of Hysteresis in `carEntryIndex`
- In `rideEntry->Cars`, vehicles are structured in archetype pairs:
  - Even index (`0`, `2`, `4`): upright vehicle variant (e.g. `FrontCar`, `DefaultCar`, `RearCar`).
  - Odd index (`1`, `3`, `5`): inverted/flying vehicle variant.
- In [`src/openrct2/paint/entity/Paint.Vehicle.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/paint/entity/Paint.Vehicle.cpp#L44-L55):
  ```cpp
  auto carEntryIndex = vehicle.vehicle_type;
  if (vehicle.flags.has(VehicleFlag::carIsInverted))
  {
      carEntryIndex++;
      zOffset += 16;
  }
  carEntry = &rideEntry->Cars[carEntryIndex];
  ```
- **Why there is no hysteresis**: `carEntryIndex` is a local stack variable recomputed fresh on every frame. When `carIsInverted == true`, it selects `Cars[1]`. When `carIsInverted == false`, the `if` block does not execute, and `carEntryIndex` immediately falls back to `vehicle.vehicle_type` (`Cars[0]`). There is zero persistent state, zero lag, and no `else` condition required.

### 2. Why `carEntry--;` Existed in Original RCT2
- In original RCT2, `VehicleFlag::carIsInverted` was only set or unset when a vehicle moved between upright track and inverted track. While a vehicle traversed an "uninverting" element (such as a half-loop down or an in-line twist down), the vehicle's flag remained `carIsInverted = true` throughout the entire piece.
- Because `carIsInverted` remained true, `Paint.Vehicle.cpp` selected `Cars[1]`.
- To draw the train upright when it reached the bottom half of the loop or the second half of the twist, Chris Sawyer introduced special **`uninvertingXX` pitch angles** (`uninvertingDown25`, `uninvertingDown42`, `uninvertingDown60`) and **`uninvertingXX` roll angles** (`uninvertingLeft22`, `uninvertingLeft45`, `uninvertingRight22`, `uninvertingRight45`) in dedicated duplicate subposition tables.
- Inside [`VehiclePaint.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/paint/vehicle/VehiclePaint.cpp), whenever an `uninvertingXX` angle was encountered, it executed `carEntry--;` to decrement the pointer back to `Cars[0]`.
- By managing `VehicleFlag::carIsInverted` cleanly via `UpdateInversionFromTrack`, this render hack and all 8 `uninvertingXX` angles become completely obsolete.

### 3. Preserving the Develop Baseline (Gating on `hasInvertedVariant`)
- In `develop`, `Vehicle.TrackMotion.cpp` and `Ride.cpp` explicitly require `GetRideTypeDescriptor(rideType).flags.has(RtdFlag::hasInvertedVariant)` to set `VehicleFlag::carIsInverted`.
- Non-inverting ride types (like Junior Coaster) do not invert on these track elements in `develop`. Matching the `develop` baseline is our authoritative reference for backwards compatibility and clean regression testing.
- Hacky behavior from older RCT2 releases on arbitrary ride type changes is already rejected by `develop`, so we do not need to contort the design to preserve it.
- Note: Special elements like `multiDimQuarterLoop` (`TrackElemType::multiDimInvertedFlatToDown90QuarterLoop`, `multiDimUp90ToInvertedFlatQuarterLoop`, etc.) are explicitly left out of this refactor for now and remain untouched.

### 4. Legacy Track Element Backward Compatibility via Pointer Redirection (PR 2)
- Legacy `.sv6`, `.park`, and `.td6` files contain tiles referencing legacy track element IDs (e.g. `TrackElemType::flyerHalfLoopInvertedDown = 192`, `leftFlyerTwistDown = 189`, etc.).
- In PR 2, instead of keeping thousands of lines of duplicated `TrackVehicleInfo` subposition tables, the 4 direction pointers in `TrackVehicleInfoListDefault` for these legacy elements are redirected directly to the standard subposition tables (e.g. `HalfLoopDown`).
- This allows existing legacy parks to load, run, and validate the refactored engine with zero duplicated data.

### 5. TED 3-Way Clearance Overhaul (PR 2)
- In PR 2, `SequenceDescriptor`'s single `.clearance` is overhauled to mirror `.blockedSegments`:
  ```cpp
  enum class ClearanceType : uint8_t
  {
      upright,
      inverted,
      flying,
  };
  constexpr size_t kClearanceTypeCount = 3;
  using ClearancesPerType = std::array<SequenceClearance, kClearanceTypeCount>;
  ```
- Coaster types have different clearance envelopes on the exact same physical track piece (e.g. in-line twists have `clearance.z = 0` for standard coasters, but require `clearance.z = -16` for Flying Roller Coasters where riders are suspended below).
- Mirroring `.blockedSegments` solves this cleanly and enables deduplicating the underlying track pieces.

---

## PR 1 Detailed Scope (Current Focus)

### 1. Proposed Helper API

In [`src/openrct2/ride/Vehicle.h`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.h):
```cpp
bool UpdateInversionFromTrack(const TrackElement& trackElement, ride_type_t rideType);
```

In [`src/openrct2/ride/Vehicle.TrackMotion.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.TrackMotion.cpp):
```cpp
bool Vehicle::UpdateInversionFromTrack(const TrackElement& trackElement, ride_type_t rideType)
{
    const auto& rtd = GetRideTypeDescriptor(rideType);
    const bool shouldBeInverted = rtd.flags.has(RtdFlag::hasInvertedVariant) && trackElement.isInverted();
    const bool previousIsInverted = flags.has(VehicleFlag::carIsInverted);

    if (previousIsInverted != shouldBeInverted)
    {
        flags.set(VehicleFlag::carIsInverted, shouldBeInverted);
        EntityTweener::get().removeEntity(this);
        return true;
    }

    return false;
}
```

### 2. Call Sites Deduplicated in PR 1

- Forward motion: [`Vehicle::trackMotionForwardsGetNewTrack`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.TrackMotion.cpp#L670-L686)
  ```cpp
  auto rideType = OpenRCT2::GetRide(tileElement->asTrack()->getRideIndex())->type;
  UpdateInversionFromTrack(*tileElement->asTrack(), rideType);
  ```
- Backward motion: [`Vehicle::trackMotionBackwardsGetNewTrack`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.TrackMotion.cpp#L1051-L1065)
  ```cpp
  UpdateInversionFromTrack(*tileElement->asTrack(), curRide.type);
  ```
- Train spawn: [`Ride::VehicleCreateCar`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Ride.cpp#L3150-L3156)
  ```cpp
  vehicle->UpdateInversionFromTrack(*trackElement, ride.type);
  ```

### 3. De-hacking Paint & Angles in PR 1

- In [`src/openrct2/ride/Angles.h`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Angles.h):
  - Remove `uninvertingDown25`, `uninvertingDown42`, `uninvertingDown60` from `VehiclePitch`.
  - Remove `uninvertingUnbanked`, `uninvertingLeft22`, `uninvertingLeft45`, `uninvertingRight22`, `uninvertingRight45` from `VehicleRoll`.
- In [`src/openrct2/paint/vehicle/VehiclePaint.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/paint/vehicle/VehiclePaint.cpp):
  - Remove all 25 `carEntry--;` branches.
  - Remove switch cases and helper functions specifically created for `uninvertingXX` angles.
- In [`src/openrct2/ride/VehicleSubpositionData.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/VehicleSubpositionData.cpp):
  - Replace occurrences of `uninvertingDownXX` with `downXX`, and `uninvertingLeft/RightXX` with standard banking angles.

---

## Specific Files Touched in PR 1

- [`src/openrct2/ride/Vehicle.h`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.h)
- [`src/openrct2/ride/Vehicle.TrackMotion.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.TrackMotion.cpp)
- [`src/openrct2/ride/Ride.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Ride.cpp)
- [`src/openrct2/ride/Angles.h`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Angles.h)
- [`src/openrct2/math/Trigonometry.hpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/math/Trigonometry.hpp)
- [`src/openrct2/ride/VehicleGeometry.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/VehicleGeometry.cpp)
- [`src/openrct2/paint/vehicle/VehiclePaint.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/paint/vehicle/VehiclePaint.cpp)
- [`src/openrct2/ride/VehicleSubpositionData.cpp`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/VehicleSubpositionData.cpp) (angle names only in PR 1)
- [`refactor_plan.md`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/refactor_plan.md)

---

## Verification Plan

### Automated Tests & Compilation
- Compile `libopenrct2` and verify clean build with zero warnings:
  ```bash
  cmake --build build --target libopenrct2 -j8
  ```
- Verify code formatting adheres to OpenRCT2 standards:
  ```bash
  git diff -U0 --no-color HEAD | clang-format-diff -p1
  ```

### Manual & Regression Verification
1. **Legacy Park Testing**: Load existing park saves with `flyingInversion` track elements (half-loops down, twists) and confirm trains traverse smoothly, sprite swapping occurs without glitching, and tweener interpolation remains jitter-free.
2. **Backward Rolling & Rollback**: Verify trains rolling backwards through inversions cleanly update inversion state.
3. **Arbitrary Ride Type Changes**: Verify hacked ride types (e.g. Junior Coaster on flyer track) continue functioning properly.

---

## Acceptance Criteria for PR 1

- All duplicate inversion state-mutation blocks in motion code are replaced with `Vehicle::UpdateInversionFromTrack`.
- All 8 `uninvertingXX` angles and all 25 `carEntry--;` branches in `VehiclePaint.cpp` are completely eliminated.
- Legacy parks with flying inversions load and render seamlessly with like-for-like behavior.
- Clean compilation under `-Werror` and zero clang-format deviations.
- Scope remains narrow and surgical, laying the clean foundation for PR 2.

# Flyer Inversion Refactor — Single Source of Truth

> **Purpose**: This document captures everything learned during the refactoring of the Flying Roller Coaster inversion mechanism in OpenRCT2. If this work is restarted from a fresh branch, this document contains all the architectural knowledge, quirks, asymmetries, and failed approaches needed to design a clean solution from first principles.

---

## Table of Contents

1. [Project Context](#1-project-context)
2. [The Rendering Pipeline — How Vehicle Z & Sprites Are Determined](#2-the-rendering-pipeline)
3. [Chris Sawyer's Original Design (The Legacy Architecture)](#3-chris-sawyers-original-design)
4. [What PR 1 (v1 / v1.1) Accomplished](#4-what-pr-1-accomplished)
5. [The Central Unsolved Problem — Z Offset vs Subposition Tables](#5-the-central-unsolved-problem)
6. [Subposition Table Z-Value Reference](#6-subposition-table-z-value-reference)
7. [Approaches Tried & Their Outcomes](#7-approaches-tried--their-outcomes)
8. [Known Quirks & Asymmetries](#8-known-quirks--asymmetries)
9. [Car Entry Selection (Cars[0] vs Cars[1])](#9-car-entry-selection)
10. [Track Element Flag Reference](#10-track-element-flag-reference)
11. [Key File Map](#11-key-file-map)
12. [Proposed Clean Architecture (First Principles)](#12-proposed-clean-architecture)

---

## 1. Project Context

| Item | Value |
|---|---|
| **Repository** | `/Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert` |
| **Branch** | `flyer-inversion-refactor` |
| **Upstream base** | OpenRCT2 `develop` at commit `d99eb5dc` |
| **Commit v1** | `dd2cade` — Core refactor (centralize inversion, purge uninverting angles, purge `carEntry--`) |
| **Commit v1.1** | `a345e33` — Minor fixup (revert `isBackwards` parameter from `UpdateInversionFromTrack`) |
| **Original plan** | [refactor_plan.md](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/refactor_plan.md) — a 3-PR series |

### What the 3-PR Series Aims To Do

1. **PR 1** (current): Centralize inversion flag management, purge `uninvertingXX` angles, purge `carEntry--` branches.
2. **PR 2**: Overhaul TED clearances to support per-coaster-type clearance envelopes, deduplicate subposition tables.
3. **PR 3**: Enable standard inversion pieces on Flying/Lay-Down/Multi-Dim coasters, deprecate legacy elements.

---

## 2. The Rendering Pipeline

### How Vehicle Z Position Is Computed

```
Final Z = TrackLocation.z + subposition.z + VehicleZOffset + zOffset(paint)
```

Where:
- `TrackLocation.z` = The Z coordinate of the track tile the vehicle is on
- `subposition.z` = The Z value from the subposition table entry at the vehicle's current progress along the track piece
- `VehicleZOffset` = `GetRideTypeDescriptor(rideType).Heights.VehicleZOffset` = **8** for flyers
- `zOffset` = Additional offset applied in `PaintVehicle()` (currently **+16** when `carIsInverted`)

### How Inverted Track Tiles Are Placed

```
Inverted flat track tile: TrackLocation.z = VisualHeight - 16
```

The engine places inverted track tiles 16 units lower than their visual height. The rails are painted at `VisualHeight + 8` visually.

### The Math For Inverted Flat Track

```
vehicle.z = (H - 16) + 0 + 8 = H - 8          (without zOffset)
vehicle.z = (H - 16) + 0 + 8 + 16 = H + 8     (with zOffset += 16)
```

**The +16 zOffset is necessary** to place the vehicle flush on inverted rails.

### How Car Entry (Sprite Set) Is Selected

In [Paint.Vehicle.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/paint/entity/Paint.Vehicle.cpp):

```cpp
auto carEntryIndex = vehicle.vehicle_type;    // Usually 0
if (vehicle.flags.has(VehicleFlag::carIsInverted))
{
    carEntryIndex++;   // Selects Cars[1] — inverted sprite set
    zOffset += 16;     // Compensates for inverted tile Z placement
}
carEntry = &rideEntry->Cars[carEntryIndex];
```

> [!IMPORTANT]
> `carEntryIndex` is a **local stack variable** recomputed every frame. There is zero persistent state, zero hysteresis, and no `else` branch needed. When `carIsInverted` is cleared, `carEntryIndex` immediately falls back to `Cars[0]`.

### When `carIsInverted` Changes

The flag is set/cleared in [`Vehicle::UpdateInversionFromTrack()`](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.TrackMotion.cpp#L565-L579), which is called at **track piece boundaries** only (when the vehicle transitions from one track element to the next). The flag is NOT updated mid-element.

This means: on an inverted-to-normal twist (`leftFlyerTwistDown`), `carIsInverted` remains **true** for the ENTIRE twist element, even as the vehicle physically rotates to upright.

---

## 3. Chris Sawyer's Original Design

### The Problem He Solved

Since `carIsInverted` is true for the entire duration of transitional elements (twists, loops), the engine needs a way to:
1. **Switch sprites** from `Cars[1]` (inverted) back to `Cars[0]` (upright) mid-element
2. **Handle the Z offset** correctly when subposition tables have different Z encoding

### His Solution: Two Hacks Working Together

#### Hack 1: `uninvertingXX` Angles + `carEntry--`

Special pitch angles (`uninvertingDown25`, `uninvertingDown42`, `uninvertingDown60`) and roll angles (`uninvertingLeft22`, `uninvertingLeft45`, `uninvertingRight22`, `uninvertingRight45`) were defined. The subposition tables for transitional elements used these angles at the point where the vehicle becomes visually upright.

In `VehiclePaint.cpp`, whenever one of these angles was encountered, the code executed `carEntry--` to switch from `Cars[1]` back to `Cars[0]`. This was done in **25 separate branches** throughout the paint code.

#### Hack 2: Duplicate Subposition Tables With Z - 16

For loop elements (half-loops, large half-loops), Chris created **duplicate subposition tables** where every Z value was shifted by -16 compared to the standard loop tables. This compensated for the unconditional `zOffset += 16` that was applied when `carIsInverted` was true.

| Standard Table | Duplicate Table | Z Difference |
|---|---|---|
| `TrackVehicleInfo_8E7AFA` (HalfLoopDown) | `TrackVehicleInfo_8E91A6` (FlyerHalfLoopInvertedDown) | -16 everywhere |
| `TrackVehicleInfo_927982` (LargeHalfLoopDown) | `TrackVehicleInfo_LeftFlyerLargeHalfLoopDown0` | -16 everywhere |
| `TrackVehicleInfo_92847C` (LargeHalfLoopDown right) | `TrackVehicleInfo_RightFlyerLargeHalfLoopDown0` | -16 everywhere |

This meant: `(H - 16) + (standard_Z - 16) + 8 + 16 = (H - 16) + standard_Z + 8`, which is the same result as using standard tables without the +16 offset. Everything worked because the two hacks cancelled each other out.

### Why This Was Bad

- ~1100 lines of duplicated subposition data
- 25 fragile `carEntry--` branches scattered across paint code
- 8 fake angle values polluting the angle enums
- Completely opaque — you can't understand WHY without reverse-engineering both hacks simultaneously

---

## 4. What PR 1 Accomplished

### Committed Changes (v1 + v1.1)

| Change | Files | Lines |
|---|---|---|
| Created `Vehicle::UpdateInversionFromTrack()` | `Vehicle.TrackMotion.cpp`, `Vehicle.h` | +22, replaced 3 inline blocks |
| Purged all 25 `carEntry--` branches | `VehiclePaint.cpp` | -256 lines |
| Purged 8 `uninvertingXX` angles | `Angles.h`, `VehicleGeometry.cpp`, `Trigonometry.hpp` | -35 lines |
| Replaced uninverting angle names in subposition tables | `VehicleSubpositionData.cpp` | ~1064 lines changed (renames) |
| Added `refactor_plan.md` | repo root | +179 lines |

### Uncommitted Working Tree Changes (3 files)

#### [Paint.Vehicle.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/paint/entity/Paint.Vehicle.cpp)

Added `ShouldUseInvertedCarEntry()` function (lines 25-56) that gates `carEntryIndex++` on pitch/roll/track-flag checks. The `zOffset += 16` remains unconditional when `carIsInverted`.

#### [Vehicle.h](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.h)

Reverted `isBackwards` parameter from `UpdateInversionFromTrack` signature.

#### [VehicleSubpositionData.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/VehicleSubpositionData.cpp)

Three categories of changes:

1. **Redirected `FlyerHalfLoopInvertedDown`** from duplicate tables (`8E91A6` etc.) to standard HalfLoopDown tables (`8E7AFA` etc.) across all 17 vehicle info lists. Deleted the 4 duplicate table definitions (~230 lines).

2. **Redirected `LeftFlyerLargeHalfLoopInvertedDown` and `RightFlyerLargeHalfLoopInvertedDown`** from duplicates to standard LargeHalfLoopDown tables (`927982` etc.). Deleted 8 duplicate table definitions (~878 lines).

3. **Corrected TwistDown subpositions 90-95** — fixed yaw and pitch values in all 8 TwistDown tables (4 left, 4 right).

---

## 5. The Central Unsolved Problem

### The Conflict

After removing the duplicate subposition tables and redirecting to standard tables, we have a conflict:

**Some elements need `zOffset += 16`, others don't.** Currently it's applied unconditionally.

The reason is that **different elements encode the inverted Z elevation differently in their subposition tables**:

| Element Type | Subposition Z at inverted entry | Needs `zOffset += 16`? | Why |
|---|---|---|---|
| Inverted flat track | 0 | ✅ YES | Tile is at `H-16`, needs +16 to reach `H+8` with VehicleZOffset |
| Inverted slopes | 0 | ✅ YES | Same as flat |
| Inverted banked curves | 0 | ✅ YES | Same as flat |
| TwistDown (all 8 tables) | 0 throughout | ✅ YES | Z=0 in all 96 subpositions |
| HalfLoopDown (standard `8E7AFA`) | **16** at entry | ❌ NO | +16 already baked into Z data |
| LargeHalfLoopDown (standard `927982`) | **16** at entry | ❌ NO | +16 already baked into Z data |
| LargeHalfLoopUp (standard `9221B2`) | 0 at entry → **264** at apex | ⚠️ DEPENDS | Starts upright (Z=0, no offset needed). Goes over top to inverted (Z already accounts for height). Complex. |
| SmallHalfLoopUp | 0 at entry | ✅ YES (if inverted entry) | Works in both directions currently |
| SmallHalfLoopDown | 16 at entry | ❌ NO | Already baked |

> [!CAUTION]
> **This is the fundamental architectural tension**: Chris Sawyer's duplicate tables existed precisely to neutralize the unconditional `zOffset += 16`. By deleting the duplicates and redirecting to standard tables, we've exposed the fact that the +16 is baked into some tables but not others. We need a way to discriminate.

### In-Game Symptoms

| Element | Current Behavior | Bug |
|---|---|---|
| `leftFlyerTwistDown` / `rightFlyerTwistDown` | Vehicles at correct height | ✅ Works (Z=0 in table, +16 applied, correct) |
| `flyerHalfLoopInvertedDown` | Vehicles float +16 above rails | ❌ Broken (Z=16 in table + 16 applied = +32 total, 16 too high) |
| `flyerLargeHalfLoopInvertedUp` | Vehicles float +16 | ❌ Broken (same issue) |
| `flyerLargeHalfLoopInvertedDown` | Vehicles float +16 | ❌ Broken (same issue) |
| `flyerSmallHalfLoops` | Correct in both directions | ✅ Works |
| Inverted flat / slopes / curves | Correct height | ✅ Works |

---

## 6. Subposition Table Z-Value Reference

### TwistDown Tables (Z = 0 throughout)

All 8 TwistDown tables have Z = 0 for all 96 subpositions:

| Table | Direction | Element Side |
|---|---|---|
| `TrackVehicleInfo_8DD21E` | 0 | Left |
| `TrackVehicleInfo_8DD580` | 1 | Left |
| `TrackVehicleInfo_8DD8E2` | 2 | Left |
| `TrackVehicleInfo_8DDC44` | 3 | Left |
| `TrackVehicleInfo_8DDFA6` | 0 | Right |
| `TrackVehicleInfo_8DE308` | 1 | Right |
| `TrackVehicleInfo_8DE66A` | 2 | Right |
| `TrackVehicleInfo_8DE9CC` | 3 | Right |

### HalfLoopDown Standard Tables (Z starts at 16)

| Table | Direction | Entry Z |
|---|---|---|
| `TrackVehicleInfo_8E7AFA` | 0 | 16 |
| `TrackVehicleInfo_8E80A5` | 1 | 16 |
| `TrackVehicleInfo_8E8650` | 2 | 16 |
| `TrackVehicleInfo_8E8BFB` | 3 | 16 |

These were previously used for standard HalfLoopDown. Now also used for FlyerHalfLoopInvertedDown (after redirection).

### HalfLoopUp Standard Tables (Z starts at 0)

| Table | Direction | Entry Z |
|---|---|---|
| `TrackVehicleInfo_8E644E` | 0 | 0 |
| `TrackVehicleInfo_8E69F9` | 1 | 0 |
| `TrackVehicleInfo_8E6FA4` | 2 | 0 |
| `TrackVehicleInfo_8E754F` | 3 | 0 |

### LargeHalfLoopDown Standard Tables (Z starts at 16)

| Table | Direction | Entry Z |
|---|---|---|
| `TrackVehicleInfo_927982` | 0 (left) | 16 |
| `TrackVehicleInfo_928F76` | 1 (left) | 16 |
| `TrackVehicleInfo_92A56A` | 2 (left) | 16 |
| `TrackVehicleInfo_92BB5E` | 3 (left) | 16 |
| `TrackVehicleInfo_92847C` | 0 (right) | 16 |
| `TrackVehicleInfo_929A70` | 1 (right) | 16 |
| `TrackVehicleInfo_92B064` | 2 (right) | 16 |
| `TrackVehicleInfo_92C658` | 3 (right) | 16 |

### LargeHalfLoopUp Standard Tables (Z starts at 0)

| Table | Direction | Entry Z |
|---|---|---|
| `TrackVehicleInfo_9221B2` | 0 (left) | 0 |
| `TrackVehicleInfo_9237A6` | 1 (left) | 0 |
| `TrackVehicleInfo_924D9A` | 2 (left) | 0 |
| `TrackVehicleInfo_92638E` | 3 (left) | 0 |
| `TrackVehicleInfo_922CAC` | 0 (right) | 0 |
| `TrackVehicleInfo_9242A0` | 1 (right) | 0 |
| `TrackVehicleInfo_925894` | 2 (right) | 0 |
| `TrackVehicleInfo_926E88` | 3 (right) | 0 |

### Deleted Duplicate Tables (formerly used for FlyerXxxInvertedDown)

These were the -16 shifted duplicates that Chris Sawyer created. All have been deleted from the working tree and redirected to standard tables:

**Small half-loop duplicates (4 tables, ~230 lines):**
- `TrackVehicleInfo_8E91A6` → now `TrackVehicleInfo_8E7AFA`
- `TrackVehicleInfo_8E9751` → now `TrackVehicleInfo_8E80A5`
- `TrackVehicleInfo_8E9CFC` → now `TrackVehicleInfo_8E8650`
- `TrackVehicleInfo_8EA2A7` → now `TrackVehicleInfo_8E8BFB`

**Large half-loop duplicates (8 tables, ~878 lines):**
- `LeftFlyerLargeHalfLoopDown0-3` → now `927982` / `928F76` / `92A56A` / `92BB5E`
- `RightFlyerLargeHalfLoopDown0-3` → now `92847C` / `929A70` / `92B064` / `92C658`

---

## 7. Approaches Tried & Their Outcomes

### Approach 1: Original Sawyer (Baseline — `develop`)

**What it does:** `carIsInverted` → unconditional `carEntryIndex++` and `zOffset += 16`. Duplicate subposition tables with Z-16 for loops. `uninvertingXX` angles + `carEntry--` for sprite switching.

**Result:** ✅ Works perfectly, but at the cost of ~1100 lines of duplicated data, 25 paint code branches, and 8 fake angles.

---

### Approach 2: Purge uninverting angles + carEntry--, keep everything else (v1 commit)

**What it did:** Removed all 8 `uninvertingXX` angles, removed all 25 `carEntry--` branches, replaced angle names in subposition tables with standard equivalents. Added `UpdateInversionFromTrack()`.

**Result:** ⚠️ Partially works. The `carEntry--` removal means `Cars[1]` is now used for the ENTIRE duration of transitional elements (twists, loops), even when the vehicle is visually upright. Sprites are wrong mid-transition. The subposition table redirections (done later in uncommitted changes) break Z heights on loop elements.

---

### Approach 3: Unconditional `zOffset += 16` + gated `carEntryIndex++` via `ShouldUseInvertedCarEntry()` (pitch/roll based)

**What it does:** `ShouldUseInvertedCarEntry()` checks:
- Roll in twist range (≥ 67°) → return false (use Cars[0])
- Pitch in loop/corkscrew range → return false (use Cars[0])
- On `inversionToNormal` element: only return true if pitch=flat AND roll=unbanked (i.e. at the very start of the element before any rotation begins)
- Otherwise: return true (use Cars[1])

`zOffset += 16` remains unconditional.

**Result:** ❌ Two bugs:

1. **TwistDown vehicles sink -16**: When `ShouldUseInvertedCarEntry` returns false mid-twist, the `carEntryIndex++` is skipped (correct for sprites), but this doesn't affect `zOffset`. The TwistDown bug was actually about something else — the subposition data corrections on entries 90-95 were needed. But the fundamental concern is that pitch/roll gating is fragile and doesn't capture the full picture.

2. **LoopDown/LargeLoopDown vehicles float +16**: The standard loop tables have Z=16 baked in. With unconditional `zOffset += 16`, vehicles are 16 too high.

> [!WARNING]
> **User explicitly rejected this approach**: "I don't think the pitch/roll gating is the correct way to determine if we should use inverted car entry. It has much more to do with the track geometry than the sprite call."

---

### Approach 4: Separate `zOffset` from `carEntryIndex` with `NeedsInvertedZOffset()` (planned, not implemented)

**Concept:** A track-type-based function that returns false for loop elements whose subposition tables already encode +16:

```cpp
bool NeedsInvertedZOffset(const Vehicle& vehicle)
{
    switch (vehicle.GetTrackType())
    {
        case TrackElemType::flyerHalfLoopInvertedDown:
        case TrackElemType::leftFlyerLargeHalfLoopInvertedDown:
        case TrackElemType::rightFlyerLargeHalfLoopInvertedDown:
        case TrackElemType::leftFlyerLargeHalfLoopInvertedUp:  // ??
        case TrackElemType::rightFlyerLargeHalfLoopInvertedUp: // ??
        case TrackElemType::flyerHalfLoopInvertedUp:           // ??
            return false;  // subposition Z already includes +16
        default:
            return true;   // flat, slopes, twists — need the +16
    }
}
```

**Status:** Not implemented. Expected to fix the Z offset problem, but `carEntryIndex` selection still needs its own solution.

> [!NOTE]
> The `LargeHalfLoopUp` case is particularly tricky — the vehicle starts upright at Z=0 and goes over the top to inverted. The Z encoding changes mid-element. This may require per-subposition logic rather than a simple track-type switch.

---

## 8. Known Quirks & Asymmetries

### Quirk 1: Loops are asymmetric with twists

TwistDown tables have Z=0 throughout (16 needs to come from `zOffset`).
LoopDown tables have Z=16 at entry (16 is already baked in).

This means you **cannot** apply a single uniform rule for `zOffset` across all transitional elements.

### Quirk 2: Up vs Down loops are asymmetric

HalfLoopUp starts at Z=0 (upright entry). HalfLoopDown starts at Z=16 (inverted entry).
LargeHalfLoopUp starts at Z=0. LargeHalfLoopDown starts at Z=16.

The "Up" variants start from upright and go to inverted. The "Down" variants start from inverted and come back to upright. The subposition Z values reflect the physical geometry differently.

### Quirk 3: `carIsInverted` persists across entire transitional elements

`UpdateInversionFromTrack()` is called at track piece boundaries. On a TwistDown element (inverted→normal), `carIsInverted` is true for the ENTIRE element, even though the vehicle physically transitions to upright mid-element.

This is by design — the flag reflects the **track tile's** inversion state, not the vehicle's visual orientation.

### Quirk 4: Some elements have BOTH normalToInversion AND inversionToNormal flags

- `leftFlyerTwistUp` / `rightFlyerTwistUp`
- `up90ToInvertedFlatQuarterLoop`

Having both flags means the element transitions in both directions. This makes flag-based gating ambiguous.

### Quirk 5: `startsAtHalfHeight` affects tile Z placement

Elements with `TrackElementFlag::startsAtHalfHeight` have their track tile placed differently, which affects `TrackLocation.z`. Examples:
- `kTEDLeftFlyerLargeHalfLoopInvertedUp` has `startsAtHalfHeight`
- `kTEDFlyerHalfLoopInvertedUp` has `startsAtHalfHeight`

### Quirk 6: Cars[1] DOES have sprites for steep slopes

A prior assumption that `Cars[1]` lacks steep slope sprites was **incorrect** per user testing. `Cars[1]` has sprites for flat, gentle slopes, steep slopes, and banked turns. It does NOT have sprites for loop/corkscrew angles or twist roll angles.

### Quirk 7: SmallHalfLoops work correctly in both directions

This was empirically confirmed by the user. The small half-loops work with the current unconditional `zOffset += 16` implementation. This suggests their subposition tables are either the duplicate Z-16 tables (still using legacy tables) or that there's some other compensation at play. **This needs investigation** — are the small half-loop entries in `TrackVehicleInfoListDefault` still pointing to the old tables?

### Quirk 8: The `TrackGetActualBank2()` inversion swap

In [Track.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Track.cpp#L395), `TrackGetActualBank2()` swaps `TrackRoll::none` ↔ `TrackRoll::upsideDown` for rides with `hasInvertedVariant` when inverted. This means the roll values in `TrackDefinition` are not what they appear for flyer vehicles.

---

## 9. Car Entry Selection

### The Problem

When `carIsInverted` is true but the vehicle is mid-transition (physically becoming upright), we need to select `Cars[0]` (upright sprites) even though the flag says inverted.

### What We Know About Cars[1] Sprite Coverage

| Angle Category | Cars[1] Has Sprites? |
|---|---|
| Flat (pitch=0, roll=0) | ✅ Yes |
| Gentle slopes (pitch ≤ 25°) | ✅ Yes |
| Steep slopes (pitch = 42°, 60°) | ✅ Yes |
| Banked turns (roll ≤ 45°) | ✅ Yes |
| Twist angles (roll ≥ 67°) | ❌ No |
| Loop angles (pitch ≥ 105°) | ❌ No |
| Corkscrew angles | ❌ No |
| down75, down90 | ✅ Yes (exception within loop range) |

### Rejected Approach: Pitch/Roll Gating

Check pitch and roll values at render time to decide whether Cars[1] has sprites for the current orientation. The user rejected this because:

> "It has much more to do with the track geometry than the sprite call, though I know the two are related."

The pitch/roll values and the track type are correlated but not identical signals. The track type is the authoritative source of truth for "what is happening" — the pitch/roll values are downstream consequences.

### Suggested Approach: Track-Geometry Based

Use the track element type directly to determine which car entry to use. This would be a `switch` on `vehicle.GetTrackType()`:

- **On inverted flat/slope/curve elements**: use Cars[1] (vehicle is fully inverted)
- **On TwistDown elements**: use Cars[1] at entry (subpositions 0-N where pitch=flat, roll=unbanked), then Cars[0] once rotation begins
- **On LoopDown elements**: use Cars[1] at entry, then Cars[0] once past the top
- **On LoopUp elements**: entered from upright, so Cars[0] → Cars[1] after the apex

The transition point within an element could be determined by:
1. **Subposition index** — a hardcoded cutoff per element type
2. **Pitch/roll threshold** — as a secondary signal within a known track type context (this is different from using pitch/roll alone)
3. **A flag in the subposition data itself** — adding a bit to indicate "vehicle is visually inverted here"

---

## 10. Track Element Flag Reference

### Key Flags in `TrackElementFlag`

| Flag | Meaning |
|---|---|
| `inversionToNormal` | Element transitions from inverted to normal (twist down, loop down, large loop up from inverted) |
| `normalToInversion` | Element transitions from normal to inverted (twist up, loop up) |
| `startsAtHalfHeight` | Track tile placement uses half-height offset |
| `down` | Element descends |
| `up` | Element ascends |

### Flyer-Specific Track Elements and Their Flags

| Track Element | Flags | Direction |
|---|---|---|
| `leftFlyerTwistUp` | `normalToInversion`, `inversionToNormal` | Normal → Inverted |
| `rightFlyerTwistUp` | `normalToInversion`, `inversionToNormal` | Normal → Inverted |
| `leftFlyerTwistDown` | `inversionToNormal` | Inverted → Normal |
| `rightFlyerTwistDown` | `inversionToNormal` | Inverted → Normal |
| `flyerHalfLoopUninvertedUp` | *(standard loop up)* | Normal → Inverted (via top of loop) |
| `flyerHalfLoopInvertedDown` | `down`, `inversionToNormal` | Inverted → Normal (via bottom of loop) |
| `leftFlyerLargeHalfLoopUninvertedUp` | *(standard)* | Normal → Inverted |
| `rightFlyerLargeHalfLoopUninvertedUp` | *(standard)* | Normal → Inverted |
| `leftFlyerLargeHalfLoopInvertedDown` | `down`, `inversionToNormal` | Inverted → Normal |
| `rightFlyerLargeHalfLoopInvertedDown` | `down`, `inversionToNormal` | Inverted → Normal |
| `leftFlyerLargeHalfLoopInvertedUp` | `up`, `inversionToNormal`, `startsAtHalfHeight` | Inverted → Normal (going up) |
| `rightFlyerLargeHalfLoopInvertedUp` | `up`, `inversionToNormal`, `startsAtHalfHeight` | Inverted → Normal (going up) |
| `flyerHalfLoopInvertedUp` | `up`, `inversionToNormal`, `startsAtHalfHeight` | Inverted → Normal (going up) |

### Track Element Type IDs (for switch statements)

```cpp
leftFlyerTwistUp         = 187
rightFlyerTwistUp        = 188
leftFlyerTwistDown       = 189
rightFlyerTwistDown      = 190
flyerHalfLoopUninvertedUp   = 191
flyerHalfLoopInvertedDown   = 192
leftFlyerLargeHalfLoopUninvertedUp  = 283
rightFlyerLargeHalfLoopUninvertedUp = 284
leftFlyerLargeHalfLoopInvertedDown  = 285
rightFlyerLargeHalfLoopInvertedDown = 286
leftFlyerLargeHalfLoopInvertedUp    = 287
rightFlyerLargeHalfLoopInvertedUp   = 288
leftFlyerLargeHalfLoopUninvertedDown  = 289
rightFlyerLargeHalfLoopUninvertedDown = 290
flyerHalfLoopInvertedUp   = 291
flyerHalfLoopUninvertedDown = 292
```

---

## 11. Key File Map

| File | What It Contains | Key Lines |
|---|---|---|
| [Paint.Vehicle.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/paint/entity/Paint.Vehicle.cpp) | `PaintVehicle()` — THE decision point for carEntry and zOffset | Lines 25-56: `ShouldUseInvertedCarEntry()`. Lines 84-91: the carEntry/zOffset block |
| [VehiclePaint.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/paint/vehicle/VehiclePaint.cpp) | All vehicle sprite drawing functions | All 25 `carEntry--` branches have been removed |
| [Vehicle.TrackMotion.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.TrackMotion.cpp) | Vehicle motion, `UpdateInversionFromTrack()` | Line 565: helper. Line 681: forward call. Line 1047: backward call |
| [Vehicle.h](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Vehicle.h) | Vehicle struct, `UpdateInversionFromTrack` declaration | Line ~276 |
| [VehicleSubpositionData.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/VehicleSubpositionData.cpp) | ~41000 lines of subposition tables | Lines ~13051: TwistDown. Lines ~3536-3676: HalfLoop. Lines ~11920-12508: LargeHalfLoop. Lines ~38290+: InfoList arrays |
| [Angles.h](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Angles.h) | `VehiclePitch` and `VehicleRoll` enums | All `uninvertingXX` values removed |
| [TrackData.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/TrackData.cpp) | `TrackElementDescriptor` definitions | Line ~8754: TwistUp TED. Line ~8783: TwistDown TED |
| [TED.Loop.h](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/ted/TED.Loop.h) | Flyer-specific loop TEDs | Line ~1442: HalfLoopInvertedDown. Line ~1596: LargeHalfLoopInvertedUp. Line ~1668: HalfLoopInvertedUp |
| [TrackElemType.h](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/TrackElemType.h) | Track element type enum | Lines ~209-320 |
| [FlyingRollerCoaster.h](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/rtd/coaster/FlyingRollerCoaster.h) | Ride type descriptor | Lines ~31-35: `InvertedTrackPaintFunctions` |
| [Track.cpp](file:///Users/tbarford/Desktop/orct2_invert/OpenRCT2_invert/src/openrct2/ride/Track.cpp) | `TrackGetActualBank2()` swap | Line ~395 |

---

## 12. Proposed Clean Architecture (First Principles)

If re-implementing from scratch, the design should separate three independent concerns:

### Concern 1: When is the vehicle "inverted"? (`carIsInverted` flag)

**Current approach works well.** `UpdateInversionFromTrack()` reads `trackElement.isInverted()` at track piece boundaries. This is clean and correct.

### Concern 2: Which sprite set to use? (`carEntryIndex`)

**Should be driven by track element type**, not pitch/roll angles. Two options:

**Option A — Track type switch + subposition index threshold:**
```
For each transitional track type, define a subposition index at which the visual orientation flips.
Before that index: use Cars[1] (inverted sprites).
After that index: use Cars[0] (upright sprites).
```

**Option B — Encode visual orientation in subposition data:**
Add a bit to `TrackVehicleInfo` entries indicating whether the vehicle is "visually inverted" at that subposition. The renderer reads this bit instead of guessing from pitch/roll.

**Option C — Infer from track type + direction only (no mid-element switching):**
Some elements are fully inverted (inverted flat → Cars[1]), some are fully upright. Transitional elements would need one of the above approaches.

### Concern 3: Z height offset (`zOffset`)

**Should also be driven by track element type.** The rule is simple:

- If the subposition table for this element **already has +16 baked into its Z values** (i.e., it's a standard loop-down table that was designed for inverted entry): **do not add +16**.
- If the subposition table has Z=0 for the inverted section (flat, slopes, twists): **add +16**.

This is a static property of the track element type. A `NeedsInvertedZOffset(trackType)` function returning a boolean is sufficient.

### Key Insight for Clean Design

> The `carEntryIndex` decision and the `zOffset` decision are **correlated but independent**. They must be separate functions, both keyed on track geometry, not on each other.

Both decisions map cleanly to a track-type switch. The awkward cases are the "large half loop up from inverted" elements where the vehicle transitions from inverted to upright mid-element AND the Z encoding changes mid-table. These may need subposition-index-based logic.

### Build & Test Command

```bash
cmake --build build --target libopenrct2 openrct2 -j12
```

### Test Matrix

| Test Case | Expected Behavior |
|---|---|
| Inverted flat/slope/curve | Correct height, Cars[1] sprites |
| TwistDown (both left/right) | No sink, smooth sprite transition mid-twist |
| HalfLoopDown (flyerHalfLoopInvertedDown) | No float, smooth sprite transition |
| LargeHalfLoopDown (left/right) | No float |
| LargeHalfLoopUp (left/right, from inverted) | No float |
| HalfLoopUp (flyerHalfLoopInvertedUp) | No float |
| SmallHalfLoops (both directions) | No regression |
| Backward rolling through all above | Same behavior |
| Non-flyer coasters on same track | No regression (gated on `hasInvertedVariant`) |

---

