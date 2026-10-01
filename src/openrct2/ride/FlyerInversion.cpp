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

    bool EntersInverted(const TrackDefinition& def)
    {
        // The flyer runs standard inversions opposite to the descriptor's roll labels.
        return def.rollStart != TrackRoll::upsideDown;
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

    enum class PitchClass : uint8_t
    {
        level,      // within the range the inverted car set has sprites for
        overTheTop, // past 60 degrees: vertical, beyond vertical, or upside down
        special,    // corkscrew-type pitches that encode their own roll
    };

    static PitchClass ClassifyPitch(VehiclePitch pitch)
    {
        switch (pitch)
        {
            case VehiclePitch::flat:
            case VehiclePitch::up8:
            case VehiclePitch::up12:
            case VehiclePitch::up16:
            case VehiclePitch::up25:
            case VehiclePitch::up42:
            case VehiclePitch::up50:
            case VehiclePitch::up60:
            case VehiclePitch::down8:
            case VehiclePitch::down12:
            case VehiclePitch::down16:
            case VehiclePitch::down25:
            case VehiclePitch::down42:
            case VehiclePitch::down50:
            case VehiclePitch::down60:
            case VehiclePitch::upHalfHelixLarge:
            case VehiclePitch::upHalfHelixSmall:
            case VehiclePitch::downHalfHelixLarge:
            case VehiclePitch::downHalfHelixSmall:
            case VehiclePitch::upQuarterHelix:
            case VehiclePitch::downQuarterHelix:
                return PitchClass::level;
            case VehiclePitch::up75:
            case VehiclePitch::up90:
            case VehiclePitch::up105:
            case VehiclePitch::up120:
            case VehiclePitch::up135:
            case VehiclePitch::up150:
            case VehiclePitch::up165:
            case VehiclePitch::inverted:
            case VehiclePitch::down75:
            case VehiclePitch::down90:
            case VehiclePitch::down105:
            case VehiclePitch::down120:
            case VehiclePitch::down135:
            case VehiclePitch::down150:
            case VehiclePitch::down165:
                return PitchClass::overTheTop;
            default:
                return PitchClass::special;
        }
    }

    bool UsesInvertedCarSet(const VehicleInfo& raw, bool enteredInverted)
    {
        // The flyer's pose is the standard (sit-down) pose rolled half a turn about the rail. A level,
        // unbanked standard pose therefore means the flyer is hanging, which the inverted set draws
        // natively; rolled and over-the-top standard poses mean it is not, so the upright set draws them.
        if (raw.roll != VehicleRoll::unbanked)
            return false;
        switch (ClassifyPitch(raw.pitch))
        {
            case PitchClass::level:
                return true;
            case PitchClass::overTheTop:
                return false;
            default:
                return enteredInverted;
        }
    }

    VehicleInfo TransformMoveInfo(const VehicleInfo& raw, bool enteredInverted)
    {
        VehicleInfo out = raw;

        // The painter adds kInvertedCarZOffset while the car is flagged inverted (its entry state), and
        // that offset may only change at element boundaries, where the entity tweener is reset. Keep the
        // total height at the standard sample plus the offset regardless of which car set draws it.
        if (!enteredInverted)
        {
            out.z += kInvertedCarZOffset;
        }

        if (UsesInvertedCarSet(raw, enteredInverted))
        {
            return out;
        }

        // Drawn with the upright set: express the half-turn roll in that set's frame.
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

} // namespace OpenRCT2::FlyerInversion
