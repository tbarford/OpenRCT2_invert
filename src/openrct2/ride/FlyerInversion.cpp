/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "FlyerInversion.h"

#include "Track.h"
#include "Vehicle.h"
#include "ted/TrackElementDescriptor.h"

namespace OpenRCT2::FlyerInversion
{
    using namespace OpenRCT2::TrackMetadata;

    bool IsInvertingPiece(const TrackDefinition& def)
    {
        return (def.rollStart != def.rollEnd)
            && (def.rollStart == TrackRoll::upsideDown || def.rollEnd == TrackRoll::upsideDown);
    }

    FlyerTransform ClassifyTrack(TrackElemType type, bool carIsInverted)
    {
        switch (type)
        {
            case TrackElemType::halfLoopDown:
            case TrackElemType::leftLargeHalfLoopDown:
            case TrackElemType::rightLargeHalfLoopDown:
                // Upright vehicle traversing the downward half of a loop needs its
                // move-info inverted so it renders right-side-up on inverted geometry.
                // If the car is already flagged as inverted, no transform needed.
                return carIsInverted ? FlyerTransform::None : FlyerTransform::HalfLoopDown;

            case TrackElemType::leftTwistUpToDown:
            case TrackElemType::rightTwistUpToDown:
                return FlyerTransform::TwistUpToDown;

            case TrackElemType::leftTwistDownToUp:
            case TrackElemType::rightTwistDownToUp:
                return FlyerTransform::TwistDownToUp;

            default:
                return FlyerTransform::None;
        }
    }

    bool ShouldUseInvertedSprite(
        [[maybe_unused]] TrackElemType type, [[maybe_unused]] uint16_t trackProgress, bool carIsInverted)
    {
        // Currently, the sprite switch happens at element boundaries via
        // UpdateInversionFromTrack(). The subposition data tables already
        // encode the correct roll for mid-element visual transitions (twists).
        // This function is the hook point for future mid-element sprite switching.
        return carIsInverted;
    }

    VehicleInfo TransformMoveInfo(
        const VehicleInfo& raw, FlyerTransform transform, TrackElemType type, VehicleTrackSubposition subposition,
        uint8_t direction, uint16_t trackProgress)
    {
        switch (transform)
        {
            case FlyerTransform::HalfLoopDown:
            {
                VehicleInfo out = raw;
                out.z += 16;
                out.yaw = (out.yaw + 16) & 31;
                out.pitch = InvertPitch(out.pitch);
                return out;
            }
            case FlyerTransform::TwistUpToDown:
            {
                // Upright -> Inverted
                if (trackProgress >= 90)
                {
                    VehicleInfo out = raw;
                    out.z = -16;
                    out.yaw = (out.yaw + 16) & 31;
                    out.pitch = VehiclePitch::flat;
                    out.roll = VehicleRoll::unbanked;
                    return out;
                }
                auto rollElem = (type == TrackElemType::leftTwistUpToDown) ? TrackElemType::leftTwistDownToUp
                                                                           : TrackElemType::rightTwistDownToUp;
                const auto* rollInfo = vehicle_get_move_info(subposition, rollElem, direction, trackProgress);
                VehicleInfo out = *rollInfo;
                out.z = 0;
                return out;
            }
            case FlyerTransform::TwistDownToUp:
            {
                // Inverted -> Upright
                auto unrollElem = (type == TrackElemType::leftTwistDownToUp) ? TrackElemType::leftTwistUpToDown
                                                                             : TrackElemType::rightTwistUpToDown;
                const auto* unrollInfo = vehicle_get_move_info(subposition, unrollElem, direction, trackProgress);
                VehicleInfo out = *unrollInfo;
                out.z = 0;
                if (trackProgress < 5)
                {
                    out.yaw = (out.yaw + 16) & 31;
                    out.pitch = VehiclePitch::flat;
                    out.roll = VehicleRoll::unbanked;
                }
                return out;
            }
            default:
                return raw;
        }
    }

} // namespace OpenRCT2::FlyerInversion
