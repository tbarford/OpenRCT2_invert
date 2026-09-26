/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "Angles.h"
#include "VehicleSubpositionData.h"

#include <cstdint>

namespace OpenRCT2
{
    enum class TrackElemType : uint16_t;
}

namespace OpenRCT2::TrackMetadata
{
    struct TrackDefinition;
}

namespace OpenRCT2::FlyerInversion
{
    /**
     * Classifies what kind of flyer move-info transform a track element needs.
     */
    enum class FlyerTransform : uint8_t
    {
        None,         // Standard handling — no transform needed
        HalfLoopDown, // halfLoopDown, left/rightLargeHalfLoopDown — upright vehicle on inverted-geometry track
    };

    /**
     * Does this track definition transition between upright and inverted?
     * True when rollStart != rollEnd and one of them is upsideDown.
     */
    bool IsInvertingPiece(const TrackMetadata::TrackDefinition& def);

    /**
     * What transform does this track element need for a flying coaster?
     * Returns None for non-inverting elements or when the vehicle is already in the correct state.
     */
    FlyerTransform ClassifyTrack(TrackElemType type, bool carIsInverted);

    /**
     * Invert a pitch value (reflect around 90°).
     * flat ↔ inverted, up25 ↔ up150, etc.
     * Corkscrew/helix/other pitches pass through unchanged.
     */
    constexpr VehiclePitch InvertPitch(VehiclePitch pitch);

    /**
     * Should the inverted car entry (sprite set) be used for painting?
     * For most elements, just returns carIsInverted.
     * (Extensible for future mid-element sprite switching.)
     */
    bool ShouldUseInvertedSprite(TrackElemType type, uint16_t trackProgress, bool carIsInverted);

    /**
     * Transform raw VehicleInfo for a flying coaster on an inverting element.
     * Returns the raw info unmodified if no transform is needed.
     */
    VehicleInfo TransformMoveInfo(const VehicleInfo& raw, FlyerTransform transform);

    // ---- constexpr implementation ----

    constexpr VehiclePitch InvertPitch(VehiclePitch pitch)
    {
        // Enum layout: flat(0), up12(1), up25(2), up42(3), up60(4),
        //   down12(5), down25(6), down42(7), down60(8),
        //   up75(9), up90(10), up105(11), up120(12), up135(13), up150(14), up165(15),
        //   inverted(16),
        //   down75(17), down90(18), down105(19), down120(20), down135(21), down150(22), down165(23)
        static constexpr VehiclePitch kMap[] = {
            VehiclePitch::inverted, // flat(0) → inverted
            VehiclePitch::up165,    // up12(1) → up165
            VehiclePitch::up150,    // up25(2) → up150
            VehiclePitch::up135,    // up42(3) → up135
            VehiclePitch::up120,    // up60(4) → up120
            VehiclePitch::down165,  // down12(5) → down165
            VehiclePitch::down150,  // down25(6) → down150
            VehiclePitch::down135,  // down42(7) → down135
            VehiclePitch::down120,  // down60(8) → down120
            VehiclePitch::up105,    // up75(9) → up105
            VehiclePitch::up90,     // up90(10) → up90
            VehiclePitch::up75,     // up105(11) → up75
            VehiclePitch::up60,     // up120(12) → up60
            VehiclePitch::up42,     // up135(13) → up42
            VehiclePitch::up25,     // up150(14) → up25
            VehiclePitch::up12,     // up165(15) → up12
            VehiclePitch::flat,     // inverted(16) → flat
            VehiclePitch::down105,  // down75(17) → down105
            VehiclePitch::down90,   // down90(18) → down90
            VehiclePitch::down75,   // down105(19) → down75
            VehiclePitch::down60,   // down120(20) → down60
            VehiclePitch::down42,   // down135(21) → down42
            VehiclePitch::down25,   // down150(22) → down25
            VehiclePitch::down12,   // down165(23) → down12
        };
        auto idx = static_cast<uint8_t>(pitch);
        if (idx < std::size(kMap))
            return kMap[idx];
        return pitch; // corkscrew/helix/etc — pass through unchanged
    }

} // namespace OpenRCT2::FlyerInversion
