/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include <cstdint>

namespace OpenRCT2
{
    struct TrackElement;
    struct VehicleInfo;
} // namespace OpenRCT2

namespace OpenRCT2::TrackMetadata
{
    struct TrackDefinition;
}

/**
 * Inversion rules for rides with an inverted track variant (the Flying Roller Coaster).
 *
 * Model: every inverting piece toggles the car between upright and inverted. A track element's
 * inverted bit records the state the car is in when it ENTERS the element; the exit state is the
 * opposite for inverting pieces and the same for everything else.
 *
 * Standard inversion elements are reused in the direction the flyer paint draws them, which is the
 * reverse of the descriptor's roll labels: the flyer is inverted where the descriptor says the roll
 * is none. In this direction the standard descriptor geometry (block offsets and zEnd) already
 * matches the flyer exactly, so no Z adjustment exists.
 */
namespace OpenRCT2::FlyerInversion
{
    /**
     * Height difference between a car riding on top of the rails and one hanging below them.
     * Shared by the vehicle painter and the move-info transform.
     */
    inline constexpr int16_t kInvertedCarZOffset = 16;

    /**
     * Does this track definition transition between upright and inverted?
     * True when rollStart != rollEnd and one of them is upsideDown.
     */
    bool IsInvertingPiece(const TrackMetadata::TrackDefinition& def);

    /**
     * Is this an inverting piece from the standard element set (not one of the legacy
     * flyer-specific elements, which carry their own subposition data)?
     */
    bool UsesStandardInversion(const TrackMetadata::TrackDefinition& def);

    /**
     * The state a car is in when it enters a standard inverting piece. This is the value stored
     * in the element's inverted bit when the piece is placed.
     */
    bool EntersInverted(const TrackMetadata::TrackDefinition& def);

    /** Car state at the start of an existing element (its inverted bit). */
    bool IsInvertedAtStart(const TrackElement& trackElement);

    /** Car state at the end of an existing element: the start state, toggled by inverting pieces. */
    bool IsInvertedAtEnd(const TrackElement& trackElement);

    /**
     * Which car set draws a flyer car at this standard subposition sample on a standard inverting
     * piece. The flyer's pose is the standard pose rolled half a turn about the rail, so a level
     * unbanked standard sample is a hanging flyer (inverted set), while rolled and over-the-top
     * samples are drawn with the upright set. Corkscrew-type pitches keep the entry state.
     */
    bool UsesInvertedCarSet(const VehicleInfo& raw, bool enteredInverted);

    /**
     * Re-express a standard subposition sample for a flyer car on a standard inverting piece, in the
     * frame of the car set chosen by UsesInvertedCarSet. The pose and total height match the legacy
     * flyer subposition tables sample-for-sample; only the set that draws each pose differs:
     *  - samples drawn with the upright set are rolled half a turn: rolled samples are mirrored to
     *    the opposite side (rollX -> other side, 180 - X), unbanked ones get the inverted pitch and
     *    a half-revolution yaw;
     *  - a car that entered upright is lifted by kInvertedCarZOffset, since the painter only adds
     *    that offset to cars flagged inverted.
     */
    VehicleInfo TransformMoveInfo(const VehicleInfo& raw, bool enteredInverted);
} // namespace OpenRCT2::FlyerInversion
