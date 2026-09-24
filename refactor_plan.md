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

