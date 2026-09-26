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

    VehicleInfo TransformMoveInfo(const VehicleInfo& raw, FlyerTransform transform)
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
            default:
                return raw;
        }
    }

} // namespace OpenRCT2::FlyerInversion
