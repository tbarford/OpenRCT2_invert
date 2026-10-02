/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "ted/PitchAndRoll.h"
#include "ted/TrackElemType.h"

namespace OpenRCT2::TrackMetadata
{
    struct TrackDefinition;
}

/**
 * Inversion rules for rides with an inverted track variant (the Flying, Lay-Down and Multi-Dimension coasters).
 *
 * A track element's inverted bit is the state the car is in when it enters the element. Inverting pieces, those with
 * exactly one upsideDown end, turn the car over, so they leave it in the other state. Every other piece keeps it.
 *
 * On these rides an upsideDown roll label only marks which end of an inverting piece is inverted for a sit-down car.
 * The car state at each end replaces it: the end is upsideDown when the car is inverted there and unbanked otherwise.
 * For the legacy flyer-only elements, whose labels all run from none to upsideDown, this is the same as swapping none
 * and upsideDown on inverted elements, as the ride has always done.
 *
 * Standard inversions (the sit-down coaster's twists, barrel rolls, corkscrews, half loops, zero-G rolls and dive loops)
 * are built in their default direction: against the descriptor's roll labels, with the car inverted where the
 * descriptor's roll is none. The standard geometry then matches the flyer's without any height adjustment.
 */
namespace OpenRCT2::FlyerInversion
{
    /** Does this piece turn the car over? True when exactly one end is upsideDown. */
    bool IsInvertingPiece(const TrackMetadata::TrackDefinition& definition);

    /** The standard element a legacy flyer-only element copies, or TrackElemType::none. */
    TrackElemType GetStandardEquivalent(TrackElemType trackType);

    /** Is this an inverting piece from the standard element set, rather than a legacy flyer-only element? */
    bool IsStandardInversion(TrackElemType trackType);

    /** The car state at one end of a piece, given the state at its other end. */
    bool IsInvertedAtOtherEnd(const TrackMetadata::TrackDefinition& definition, bool isInverted);

    /** Can the piece be entered in this state? Standard inversions support their default direction only. */
    bool SupportsEntry(TrackElemType trackType, bool entersInverted);

    /** A roll label with an upsideDown end read as unbanked: the roll the car has at that end, ignoring the car state. */
    TrackMetadata::TrackRoll GetRollIgnoringInversion(TrackMetadata::TrackRoll roll);

    /** The roll at one end of a piece in sit-down terms: upsideDown where an unbanked end has the car inverted. */
    TrackMetadata::TrackRoll GetRoll(TrackMetadata::TrackRoll roll, bool isInverted);
} // namespace OpenRCT2::FlyerInversion
