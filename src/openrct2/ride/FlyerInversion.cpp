/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "FlyerInversion.h"

#include "../world/tile_element/TrackElement.h"
#include "TrackData.h"
#include "Vehicle.h"
#include "ted/TrackElementDescriptor.h"

#include <iterator>

namespace OpenRCT2::FlyerInversion
{
    using namespace OpenRCT2::TrackMetadata;

    // Half a revolution in the 32-step yaw space.
    static constexpr uint8_t kYawHalfTurn = 16;

    // Pitch reflected around vertical: flat <-> inverted, up25 <-> up150, etc.
    // Corkscrew/helix pitches are outside the table and pass through unchanged.
    static constexpr VehiclePitch kInvertPitchMap[] = {
        VehiclePitch::inverted, // flat
        VehiclePitch::up165,    // up12
        VehiclePitch::up150,    // up25
        VehiclePitch::up135,    // up42
        VehiclePitch::up120,    // up60
        VehiclePitch::down165,  // down12
        VehiclePitch::down150,  // down25
        VehiclePitch::down135,  // down42
        VehiclePitch::down120,  // down60
        VehiclePitch::up105,    // up75
        VehiclePitch::up90,     // up90
        VehiclePitch::up75,     // up105
        VehiclePitch::up60,     // up120
        VehiclePitch::up42,     // up135
        VehiclePitch::up25,     // up150
        VehiclePitch::up12,     // up165
        VehiclePitch::flat,     // inverted
        VehiclePitch::down105,  // down75
        VehiclePitch::down90,   // down90
        VehiclePitch::down75,   // down105
        VehiclePitch::down60,   // down120
        VehiclePitch::down42,   // down135
        VehiclePitch::down25,   // down150
        VehiclePitch::down12,   // down165
    };

    // Roll mirrored to the opposite side: leftX <-> right(180 - X).
    static constexpr VehicleRoll kMirrorRollMap[] = {
        VehicleRoll::unbanked,  // unbanked
        VehicleRoll::right157,  // left22
        VehicleRoll::right135,  // left45
        VehicleRoll::left157,   // right22
        VehicleRoll::left135,   // right45
        VehicleRoll::right112,  // left67
        VehicleRoll::right90,   // left90
        VehicleRoll::right67,   // left112
        VehicleRoll::right45,   // left135
        VehicleRoll::right22,   // left157
        VehicleRoll::left112,   // right67
        VehicleRoll::left90,    // right90
        VehicleRoll::left67,    // right112
        VehicleRoll::left45,    // right135
        VehicleRoll::left22,    // right157
    };
    static_assert(std::size(kMirrorRollMap) == EnumValue(VehicleRoll::rollCount));

    static VehiclePitch InvertPitch(VehiclePitch pitch)
    {
        const auto index = EnumValue(pitch);
        return index < std::size(kInvertPitchMap) ? kInvertPitchMap[index] : pitch;
    }

    static VehicleRoll MirrorRoll(VehicleRoll roll)
    {
        const auto index = EnumValue(roll);
        return index < std::size(kMirrorRollMap) ? kMirrorRollMap[index] : roll;
    }

    // The legacy flyer-only elements predate this model and keep their own subposition tables.
    static bool IsLegacyFlyerGroup(TrackGroup group)
    {
        switch (group)
        {
            case TrackGroup::inlineTwistUninverted:
            case TrackGroup::inlineTwistInverted:
            case TrackGroup::corkscrewUninverted:
            case TrackGroup::corkscrewInverted:
            case TrackGroup::flyingHalfLoopUninvertedUp:
            case TrackGroup::flyingHalfLoopInvertedDown:
            case TrackGroup::flyingHalfLoopUninvertedDown:
            case TrackGroup::flyingHalfLoopInvertedUp:
            case TrackGroup::flyingLargeHalfLoopUninvertedUp:
            case TrackGroup::flyingLargeHalfLoopInvertedDown:
            case TrackGroup::flyingLargeHalfLoopUninvertedDown:
            case TrackGroup::flyingLargeHalfLoopInvertedUp:
                return true;
            default:
                return false;
        }
    }

    bool IsInvertingPiece(const TrackDefinition& def)
    {
        return (def.rollStart != def.rollEnd)
            && (def.rollStart == TrackRoll::upsideDown || def.rollEnd == TrackRoll::upsideDown);
    }

    bool UsesStandardInversion(const TrackDefinition& def)
    {
        return IsInvertingPiece(def) && !IsLegacyFlyerGroup(def.group);
    }

    static bool LabelledInvertedAtStart(const TrackDefinition& def)
    {
        return def.rollStart == TrackRoll::upsideDown;
    }

    // Families that can also be entered in the descriptor's own direction. The flyer paint dispatchers
    // draw them with the standard sit-down paint when entered that way. Their up and down variants
    // start at different pitches, so offering both directions never makes a choice ambiguous;
    // families whose variants both start level (twists, rolls, corkscrews) stay one-directional.
    static bool HasLabelledDirectionPaint(const TrackDefinition& def)
    {
        switch (def.group)
        {
            case TrackGroup::halfLoop:
            case TrackGroup::halfLoopMedium:
            case TrackGroup::halfLoopLarge:
            case TrackGroup::zeroGRoll:
            case TrackGroup::zeroGRollLarge:
            case TrackGroup::diveLoop:
                return true;
            default:
                return false;
        }
    }

    bool EntersInverted(const TrackDefinition& def)
    {
        // By default the flyer runs standard inversions opposite to the descriptor's roll labels.
        return !LabelledInvertedAtStart(def);
    }

    bool SupportsEntry(const TrackDefinition& def, bool entersInverted)
    {
        if (!UsesStandardInversion(def))
            return true;
        return entersInverted == EntersInverted(def) || HasLabelledDirectionPaint(def);
    }

    bool ResolveEntryInverted(const TrackDefinition& def, bool requestedInverted)
    {
        return SupportsEntry(def, requestedInverted) ? requestedInverted : EntersInverted(def);
    }

    bool RunsWithRollLabels(const TrackDefinition& def, bool entersInverted)
    {
        return entersInverted == LabelledInvertedAtStart(def);
    }

    int16_t GetZBeginOffset(const TrackDefinition& def, bool entersInverted)
    {
        if (!UsesStandardInversion(def) || !RunsWithRollLabels(def, entersInverted))
            return 0;
        return entersInverted ? kInvertedConnectionZOffset : 0;
    }

    int16_t GetZEndOffset(const TrackDefinition& def, bool entersInverted)
    {
        if (!UsesStandardInversion(def) || !RunsWithRollLabels(def, entersInverted))
            return 0;
        return entersInverted ? 0 : kInvertedConnectionZOffset;
    }

    bool IsInvertedAtStart(const TrackElement& trackElement)
    {
        return trackElement.isInverted();
    }

    bool IsInvertedAtEnd(const TrackElement& trackElement)
    {
        const auto& ted = GetTrackElementDescriptor(trackElement.getTrackType());
        return trackElement.isInverted() != IsInvertingPiece(ted.definition);
    }

    // Has a pose turned over: rolled past a quarter turn, or pitched past vertical? Vertical, helix
    // and corkscrew-type pitches do not count; they stay with the current car set and its fallbacks.
    static bool IsTurnedOver(const VehicleInfo& info)
    {
        switch (info.roll)
        {
            case VehicleRoll::left112:
            case VehicleRoll::left135:
            case VehicleRoll::left157:
            case VehicleRoll::right112:
            case VehicleRoll::right135:
            case VehicleRoll::right157:
                return true;
            default:
                break;
        }
        switch (info.pitch)
        {
            case VehiclePitch::up105:
            case VehiclePitch::up120:
            case VehiclePitch::up135:
            case VehiclePitch::up150:
            case VehiclePitch::up165:
            case VehiclePitch::inverted:
            case VehiclePitch::down105:
            case VehiclePitch::down120:
            case VehiclePitch::down135:
            case VehiclePitch::down150:
            case VehiclePitch::down165:
                return true;
            default:
                return false;
        }
    }

    // The same pose rolled half a turn about the rail, expressed in the 32-step yaw / pitch / roll space.
    static VehicleInfo HalfRoll(const VehicleInfo& info)
    {
        VehicleInfo out = info;
        if (out.roll != VehicleRoll::unbanked)
        {
            out.roll = MirrorRoll(out.roll);
        }
        else
        {
            out.pitch = InvertPitch(out.pitch);
            out.yaw = (out.yaw + kYawHalfTurn) & 31;
        }
        return out;
    }

    // Corkscrew frames encode their roll in the pitch value, so they cannot be judged turned over.
    static bool IsCorkscrewFrame(VehiclePitch pitch)
    {
        return pitch >= VehiclePitch::corkscrewUpRight0 && pitch <= VehiclePitch::corkscrewDownRight4;
    }

    bool UsesInvertedCarSet(const VehicleInfo& raw, const VehicleInfo& firstSample, bool enteredInverted)
    {
        if (IsCorkscrewFrame(raw.pitch))
            return enteredInverted;

        // The car keeps the set it entered with until it has turned over relative to its entry pose.
        return enteredInverted != (IsTurnedOver(raw) != IsTurnedOver(firstSample));
    }

    VehicleInfo TransformMoveInfo(
        const VehicleInfo& raw, const VehicleInfo& firstSample, const TrackDefinition& def, bool enteredInverted,
        int16_t firstBlockZ)
    {
        const bool withLabels = RunsWithRollLabels(def, enteredInverted);
        VehicleInfo out = raw;

        // Height. The painter adds kInvertedCarZOffset while the car is flagged inverted (its entry
        // state); that offset only changes at element boundaries, where the entity tweener is reset,
        // so the path is expressed relative to it whichever car set draws a sample.
        if (!withLabels)
        {
            if (!enteredInverted)
                out.z += kInvertedCarZOffset;
        }
        else if (enteredInverted)
        {
            // Start the path at the entry connection, which sits GetZBeginOffset below the standard one.
            out.z = out.z - firstSample.z + GetZBeginOffset(def, true) - firstBlockZ;
        }

        // Pose. The standard sample is the sit-down pose; the flyer matches it when running with the roll
        // labels and is it rolled half a turn when running against them. The upright set draws the flyer
        // pose as is, the inverted set draws it rolled half a turn.
        const bool invertedSet = UsesInvertedCarSet(raw, firstSample, enteredInverted);
        if (withLabels == invertedSet)
        {
            const auto rolled = HalfRoll(out);
            out.pitch = rolled.pitch;
            out.roll = rolled.roll;
            out.yaw = rolled.yaw;
        }
        return out;
    }

} // namespace OpenRCT2::FlyerInversion
