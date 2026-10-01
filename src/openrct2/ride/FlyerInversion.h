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
 * Standard inversion elements are reused in the direction the flyer paint draws them. By default
 * that is against the descriptor's roll labels: the flyer is inverted where the descriptor says the
 * roll is none, and the standard geometry (block offsets and zEnd) matches the flyer exactly.
 * Some pieces can also be entered in the descriptor's own direction (see SupportsEntry); there the
 * flyer's inverted connection sits kInvertedConnectionZOffset below a standard upsideDown one.
 */
namespace OpenRCT2::FlyerInversion
{
    /**
     * Height difference between a car riding on top of the rails and one hanging below them.
     * Shared by the vehicle painter and the move-info transform.
     */
    inline constexpr int16_t kInvertedCarZOffset = 16;

    /**
     * Height of an inverted flyer connection relative to a standard upsideDown connection, for pieces
     * run in the descriptor's own direction. Measured from the legacy flyer descriptors: corkscrews and
     * half loops entered that way all differ from their standard counterparts by exactly this.
     */
    inline constexpr int16_t kInvertedConnectionZOffset = -32;

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
     * The default state a car is in when it enters a standard inverting piece: against the
     * descriptor's roll labels.
     */
    bool EntersInverted(const TrackMetadata::TrackDefinition& def);

    /** Can a standard inverting piece be entered in this state? Always true for other pieces. */
    bool SupportsEntry(const TrackMetadata::TrackDefinition& def, bool entersInverted);

    /** The entry state actually used for a piece placed while requesting this one. */
    bool ResolveEntryInverted(const TrackMetadata::TrackDefinition& def, bool requestedInverted);

    /** Does entering in this state run the piece in the descriptor's own direction? */
    bool RunsWithRollLabels(const TrackMetadata::TrackDefinition& def, bool entersInverted);

    /**
     * Adjustments added to the descriptor's zBegin / zEnd for a standard inverting piece entered in
     * the given state. Zero for every other piece and direction.
     */
    int16_t GetZBeginOffset(const TrackMetadata::TrackDefinition& def, bool entersInverted);
    int16_t GetZEndOffset(const TrackMetadata::TrackDefinition& def, bool entersInverted);

    /** Car state at the start of an existing element (its inverted bit). */
    bool IsInvertedAtStart(const TrackElement& trackElement);

    /** Car state at the end of an existing element: the start state, toggled by inverting pieces. */
    bool IsInvertedAtEnd(const TrackElement& trackElement);

    /**
     * Which car set draws a flyer car at this standard subposition sample on a standard inverting
     * piece: the set it entered with, until the sample has turned over (rolled past a quarter turn or
     * pitched past vertical) relative to the element's first sample, then the other set. Corkscrew
     * frames keep the entry set. Missing sprites are left to the vehicle painter's fallbacks.
     */
    bool UsesInvertedCarSet(const VehicleInfo& raw, const VehicleInfo& firstSample, bool enteredInverted);

    /**
     * Re-express a standard subposition sample for a flyer car on a standard inverting piece, in the
     * frame of the car set chosen by UsesInvertedCarSet. Pose and total height match the legacy flyer
     * subposition tables sample-for-sample in both directions; only the set drawing each pose differs.
     *
     * firstSample: sample 0 of the same table. firstBlockZ: the descriptor's sequence 0 z.
     */
    VehicleInfo TransformMoveInfo(
        const VehicleInfo& raw, const VehicleInfo& firstSample, const TrackMetadata::TrackDefinition& def,
        bool enteredInverted, int16_t firstBlockZ);
} // namespace OpenRCT2::FlyerInversion
