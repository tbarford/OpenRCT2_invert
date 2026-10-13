/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../paint/tile_element/Segment.h"
#include "TrackPaint.h"

#include <cstdint>

enum class TrackStyle : uint8_t
{
    _3DCinema,
    airPoweredVerticalCoaster,
    alpineCoaster,
    boatHire,
    bobsleighCoaster,
    carRide,
    chairlift,
    circus,
    classicStandUpRollerCoaster,
    classicWoodenRollerCoaster,
    classicWoodenTwisterRollerCoaster,
    compactInvertedCoaster,
    corkscrewRollerCoaster,
    crookedHouse,
    dinghySlide,
    dinghySlideCovered,
    dodgems,
    enterprise,
    facility,
    ferrisWheel,
    flyingRollerCoaster,
    flyingRollerCoasterInverted,
    flyingSaucers,
    ghostTrain,
    goKarts,
    hauntedHouse,
    heartlineTwisterCoaster,
    hybridCoaster,
    invertedHairpinCoaster,
    invertedImpulseCoaster,
    invertedRollerCoaster,
    juniorRollerCoaster,
    latticeTriangle,
    latticeTriangleAlt,
    launchedFreefall,
    layDownRollerCoasterInverted,
    lift,
    limLaunchedRollerCoaster,
    logFlume,
    loopingRollerCoaster,
    magicCarpet,
    maze,
    merryGoRound,
    mineRide,
    mineTrainCoaster,
    miniGolf,
    miniHelicopters,
    miniRollerCoaster,
    miniSuspendedCoaster,
    miniatureRailway,
    monorail,
    monorailCycles,
    motionSimulator,
    multiDimensionRollerCoaster,
    multiDimensionRollerCoasterInverted,
    observationTower,
    reverseFreefallCoaster,
    reverserRollerCoaster,
    riverRapids,
    rotoDrop,
    shop,
    sideFrictionRollerCoaster,
    singleRailRollerCoaster,
    spaceRings,
    spiralSlide,
    splashBoats,
    standUpRollerCoaster,
    steelWildMouse,
    steeplechase,
    submarineRide,
    suspendedMonorail,
    suspendedSwingingCoaster,
    swingingInverterShip,
    swingingShip,
    topSpin,
    twist,
    twisterRollerCoaster,
    virginiaReel,
    waterCoaster,
    woodenRollerCoaster,
    woodenWildMouse,

    null = 255,
};

TrackPaintFunction GetTrackPaintFunction(TrackStyle trackStyle, OpenRCT2::TrackElemType trackType);

namespace OpenRCT2
{
    struct TrackSequenceBlockedSegments
    {
        PaintSegments segments = kSegmentsNone;
        bool beforeSupports = false;
    };

    // Styles that return true have their segments blocked by PaintTrack using the track sequence data, instead of by
    // their paint functions.
    constexpr bool trackStyleBlocksSegmentsCentrally(TrackStyle)
    {
        return false;
    }

    TrackSequenceBlockedSegments GetTrackSequenceBlockedSegments(
        TrackStyle trackStyle, TrackElemType trackElemType, uint8_t sequence);
} // namespace OpenRCT2
