/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "TrackStyle.h"

#include "TrackData.h"
#include "TrackPaint.h"
#include "ted/TrackElementDescriptor.h"
#include "ted/TrackGroup.h"

using TrackPaintFunctionGetter = TrackPaintFunction (*)(OpenRCT2::TrackElemType trackType);
static TrackPaintFunction DummyGetter(OpenRCT2::TrackElemType trackType)
{
    return TrackPaintFunctionDummy;
}

static constexpr TrackPaintFunctionGetter kPaintFunctionMap[] = {
    GetTrackPaintFunction3dCinema,                 // _3DCinema
    GetTrackPaintFunctionAirPoweredVerticalRC,     // airPoweredVerticalCoaster
    OpenRCT2::AlpineRC::GetTrackPaintFunction,     // alpineCoaster
    GetTrackPaintFunctionBoatHire,                 // boatHire
    GetTrackPaintFunctionBobsleighRC,              // bobsleighCoaster
    GetTrackPaintFunctionCarRide,                  // carRide
    GetTrackPaintFunctionChairlift,                // chairlift
    GetTrackPaintFunctionCircus,                   // circus
    GetTrackPaintFunctionClassicStandUpRC,         // classicStandUpRollerCoaster
    GetTrackPaintFunctionClassicWoodenRC,          // classicWoodenRollerCoaster
    GetTrackPaintFunctionClassicWoodenTwisterRC,   // classicWoodenTwisterRollerCoaster
    GetTrackPaintFunctionCompactInvertedRC,        // compactInvertedCoaster
    GetTrackPaintFunctionCorkscrewRC,              // corkscrewRollerCoaster
    GetTrackPaintFunctionCrookedHouse,             // crookedHouse
    GetTrackPaintFunctionDinghySlide,              // dinghySlide
    GetTrackPaintFunctionDinghySlideCovered,       // dinghySlideCovered
    GetTrackPaintFunctionDodgems,                  // dodgems
    GetTrackPaintFunctionEnterprise,               // enterprise
    GetTrackPaintFunctionFacility,                 // facility
    GetTrackPaintFunctionFerrisWheel,              // ferrisWheel
    GetTrackPaintFunctionFlyingRC,                 // flyingRollerCoaster
    GetTrackPaintFunctionFlyingRCInverted,         // flyingRollerCoasterInverted
    GetTrackPaintFunctionFlyingSaucers,            // flyingSaucers
    GetTrackPaintFunctionGhostTrain,               // ghostTrain
    GetTrackPaintFunctionGoKarts,                  // goKarts
    GetTrackPaintFunctionHauntedHouse,             // hauntedHouse
    GetTrackPaintFunctionHeartlineTwisterRC,       // heartlineTwisterCoaster
    OpenRCT2::HybridRC::GetTrackPaintFunction,     // hybridCoaster
    GetTrackPaintFunctionInvertedHairpinRC,        // invertedHairpinCoaster
    GetTrackPaintFunctionInvertedImpulseRC,        // invertedImpulseCoaster
    GetTrackPaintFunctionInvertedRC,               // invertedRollerCoaster
    GetTrackPaintFunctionJuniorRC,                 // juniorRollerCoaster
    GetTrackPaintFunctionLatticeTriangleTrack,     // latticeTriangle
    GetTrackPaintFunctionLatticeTriangleTrackAlt,  // latticeTriangleAlt
    GetTrackPaintFunctionLaunchedFreefall,         // launchedFreefall
    GetTrackPaintFunctionLayDownRCInverted,        // layDownRollerCoasterInverted
    GetTrackPaintFunctionLift,                     // lift
    GetTrackPaintFunctionLimLaunchedRC,            // limLaunchedRollerCoaster
    GetTrackPaintFunctionLogFlume,                 // logFlume
    GetTrackPaintFunctionLoopingRC,                // loopingRollerCoaster
    GetTrackPaintFunctionMagicCarpet,              // magicCarpet
    GetTrackPaintFunctionMaze,                     // maze
    GetTrackPaintFunctionMerryGoRound,             // merryGoRound
    GetTrackPaintFunctionMineRide,                 // mineRide
    GetTrackPaintFunctionMineTrainRC,              // mineTrainCoaster
    GetTrackPaintFunctionMiniGolf,                 // miniGolf
    GetTrackPaintFunctionMiniHelicopters,          // miniHelicopters
    GetTrackPaintFunctionMiniRC,                   // miniRollerCoaster
    GetTrackPaintFunctionMiniSuspendedRC,          // miniSuspendedCoaster
    GetTrackPaintFunctionMiniatureRailway,         // miniatureRailway
    GetTrackPaintFunctionMonorail,                 // monorail
    GetTrackPaintFunctionMonorailCycles,           // monorailCycles
    GetTrackPaintFunctionMotionsimulator,          // motionSimulator
    GetTrackPaintFunctionMultiDimensionRC,         // multiDimensionRollerCoaster
    getTrackPaintFunctionMultiDimensionRCInverted, // multiDimensionRollerCoasterInverted
    GetTrackPaintFunctionObservationTower,         // observationTower
    GetTrackPaintFunctionReverseFreefallRC,        // reverseFreefallCoaster
    GetTrackPaintFunctionReverserRC,               // reverserRollerCoaster
    GetTrackPaintFunctionRiverRapids,              // riverRapids
    GetTrackPaintFunctionRotoDrop,                 // rotoDrop
    GetTrackPaintFunctionShop,                     // shop
    GetTrackPaintFunctionSideFrictionRC,           // sideFrictionRollerCoaster
    OpenRCT2::SingleRailRC::GetTrackPaintFunction, // singleRailRollerCoaster
    GetTrackPaintFunctionSpaceRings,               // spaceRings
    GetTrackPaintFunctionSpiralSlide,              // spiralSlide
    GetTrackPaintFunctionSplashBoats,              // splashBoats
    GetTrackPaintFunctionStandUpRC,                // standUpRollerCoaster
    GetTrackPaintFunctionWildMouse,                // steelWildMouse
    GetTrackPaintFunctionSteeplechase,             // steeplechase
    GetTrackPaintFunctionSubmarineRide,            // submarineRide
    GetTrackPaintFunctionSuspendedMonorail,        // suspendedMonorail
    GetTrackPaintFunctionSuspendedSwingingRC,      // suspendedSwingingCoaster
    GetTrackPaintFunctionSwingingInverterShip,     // swingingInverterShip
    GetTrackPaintFunctionSwingingShip,             // swingingShip
    GetTrackPaintFunctionTopspin,                  // topSpin
    GetTrackPaintFunctionTwist,                    // twist
    GetTrackPaintFunctionTwisterRC,                // twisterRollerCoaster
    GetTrackPaintFunctionVirginiaReel,             // virginiaReel
    GetTrackPaintFunctionWaterRC,                  // waterCoaster
    GetTrackPaintFunctionWoodenRC,                 // woodenRollerCoaster
    GetTrackPaintFunctionWoodenWildMouse,          // woodenWildMouse

    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
    DummyGetter,
};
static_assert(std::size(kPaintFunctionMap) == (sizeof(TrackStyle) * 256));

TrackPaintFunction GetTrackPaintFunction(TrackStyle trackStyle, OpenRCT2::TrackElemType trackType)
{
    return kPaintFunctionMap[static_cast<uint8_t>(trackStyle)](trackType);
}

namespace OpenRCT2
{
    using TrackGroupBlockedSegmentTypes = std::array<BlockedSegmentsType, EnumValue(TrackGroup::count)>;

    static constexpr const TrackGroupBlockedSegmentTypes kTrackGroupBlockedSegmentsNarrow = []() consteval {
        TrackGroupBlockedSegmentTypes array{};
        array.fill(BlockedSegmentsType::narrow);
        return array;
    }();

    static constexpr const TrackGroupBlockedSegmentTypes kTrackGroupBlockedSegmentsInverted = []() consteval {
        TrackGroupBlockedSegmentTypes array{};
        array.fill(BlockedSegmentsType::inverted);
        array[EnumValue(TrackGroup::stationEnd)] = BlockedSegmentsType::wide;
        array[EnumValue(TrackGroup::onridePhoto)] = BlockedSegmentsType::wide;
        return array;
    }();

    static constexpr const TrackGroupBlockedSegmentTypes kTrackGroupBlockedSegmentsWide = []() consteval {
        TrackGroupBlockedSegmentTypes array{};
        array.fill(BlockedSegmentsType::wide);
        return array;
    }();

    static constexpr const TrackGroupBlockedSegmentTypes kTrackGroupBlockedSegmentsCarRideGhostTrain = []() consteval {
        TrackGroupBlockedSegmentTypes array{};
        array.fill(BlockedSegmentsType::narrow);
        array[EnumValue(TrackGroup::curveVerySmall)] = BlockedSegmentsType::wide;
        return array;
    }();

    static constexpr const TrackGroupBlockedSegmentTypes kTrackGroupBlockedSegmentsMultiDimensionRollerCoaster =
        []() consteval {
            TrackGroupBlockedSegmentTypes array{};
            array.fill(BlockedSegmentsType::narrow);
            array[EnumValue(TrackGroup::straight)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::slope)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::slopeSteepUp)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::slopeSteepDown)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::flatRollBanking)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::sBend)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::brakes)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::blockBrakes)] = BlockedSegmentsType::wide;
            return array;
        }();

    static constexpr const TrackGroupBlockedSegmentTypes kTrackGroupBlockedSegmentsWoodenRollerCoaster = []() consteval {
        TrackGroupBlockedSegmentTypes array{};
        array.fill(BlockedSegmentsType::wide);
        array[EnumValue(TrackGroup::verticalLoop)] = BlockedSegmentsType::narrow;
        array[EnumValue(TrackGroup::halfLoopMedium)] = BlockedSegmentsType::narrow;
        array[EnumValue(TrackGroup::halfLoopLarge)] = BlockedSegmentsType::narrow;
        array[EnumValue(TrackGroup::helixUpBankedHalf)] = BlockedSegmentsType::narrow;
        array[EnumValue(TrackGroup::helixDownBankedHalf)] = BlockedSegmentsType::narrow;
        return array;
    }();

    static constexpr const TrackGroupBlockedSegmentTypes kTrackGroupBlockedSegmentsWoodenWildMouse = []() consteval {
        TrackGroupBlockedSegmentTypes array{};
        array.fill(BlockedSegmentsType::wide);
        array[EnumValue(TrackGroup::straight)] = BlockedSegmentsType::narrow;
        return array;
    }();

    static constexpr auto kTrackStyleBlockedSegmentType = std::to_array<TrackGroupBlockedSegmentTypes>({
        {},                                                    // _3DCinema
        kTrackGroupBlockedSegmentsWide,                        // airPoweredVerticalCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // alpineCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // boatHire
        kTrackGroupBlockedSegmentsNarrow,                      // bobsleighCoaster
        kTrackGroupBlockedSegmentsCarRideGhostTrain,           // carRide
        kTrackGroupBlockedSegmentsWide,                        // chairlift
        {},                                                    // circus
        kTrackGroupBlockedSegmentsNarrow,                      // classicStandUpRollerCoaster
        kTrackGroupBlockedSegmentsWoodenRollerCoaster,         // classicWoodenRollerCoaster
        kTrackGroupBlockedSegmentsWoodenRollerCoaster,         // classicWoodenTwisterRollerCoaster
        kTrackGroupBlockedSegmentsInverted,                    // compactInvertedCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // corkscrewRollerCoaster
        {},                                                    // crookedHouse
        kTrackGroupBlockedSegmentsNarrow,                      // dinghySlide
        kTrackGroupBlockedSegmentsNarrow,                      // dinghySlideCovered
        {},                                                    // dodgems
        {},                                                    // enterprise
        {},                                                    // facility
        {},                                                    // ferrisWheel
        kTrackGroupBlockedSegmentsNarrow,                      // flyingRollerCoaster
        kTrackGroupBlockedSegmentsInverted,                    // flyingRollerCoasterInverted
        {},                                                    // flyingSaucers
        kTrackGroupBlockedSegmentsCarRideGhostTrain,           // ghostTrain
        kTrackGroupBlockedSegmentsWide,                        // goKarts
        {},                                                    // hauntedHouse
        kTrackGroupBlockedSegmentsWide,                        // heartlineTwisterCoaster
        kTrackGroupBlockedSegmentsWide,                        // hybridCoaster
        kTrackGroupBlockedSegmentsInverted,                    // invertedHairpinCoaster
        kTrackGroupBlockedSegmentsInverted,                    // invertedImpulseCoaster
        kTrackGroupBlockedSegmentsInverted,                    // invertedRollerCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // juniorRollerCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // latticeTriangle
        kTrackGroupBlockedSegmentsNarrow,                      // latticeTriangleAlt
        {},                                                    // launchedFreefall
        kTrackGroupBlockedSegmentsInverted,                    // layDownRollerCoasterInverted
        {},                                                    // lift
        kTrackGroupBlockedSegmentsNarrow,                      // limLaunchedRollerCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // logFlume
        kTrackGroupBlockedSegmentsNarrow,                      // loopingRollerCoaster
        {},                                                    // magicCarpet
        {},                                                    // maze
        {},                                                    // merryGoRound
        kTrackGroupBlockedSegmentsNarrow,                      // mineRide
        kTrackGroupBlockedSegmentsWoodenRollerCoaster,         // mineTrainCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // miniGolf
        kTrackGroupBlockedSegmentsNarrow,                      // miniHelicopters
        kTrackGroupBlockedSegmentsNarrow,                      // miniRollerCoaster
        kTrackGroupBlockedSegmentsInverted,                    // miniSuspendedCoaster
        kTrackGroupBlockedSegmentsWide,                        // miniatureRailway
        kTrackGroupBlockedSegmentsNarrow,                      // monorail
        kTrackGroupBlockedSegmentsNarrow,                      // monorailCycles
        {},                                                    // motionSimulator
        kTrackGroupBlockedSegmentsMultiDimensionRollerCoaster, // multiDimensionRollerCoaster
        kTrackGroupBlockedSegmentsInverted,                    // multiDimensionRollerCoasterInverted
        {},                                                    // observationTower
        kTrackGroupBlockedSegmentsWide,                        // reverseFreefallCoaster
        kTrackGroupBlockedSegmentsWide,                        // reverserRollerCoaster
        kTrackGroupBlockedSegmentsWide,                        // riverRapids
        {},                                                    // rotoDrop
        {},                                                    // shop
        kTrackGroupBlockedSegmentsWide,                        // sideFrictionRollerCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // singleRailRollerCoaster
        {},                                                    // spaceRings
        {},                                                    // spiralSlide
        kTrackGroupBlockedSegmentsWide,                        // splashBoats
        kTrackGroupBlockedSegmentsNarrow,                      // standUpRollerCoaster
        kTrackGroupBlockedSegmentsNarrow,                      // steelWildMouse
        kTrackGroupBlockedSegmentsNarrow,                      // steeplechase
        kTrackGroupBlockedSegmentsNarrow,                      // submarineRide
        kTrackGroupBlockedSegmentsInverted,                    // suspendedMonorail
        kTrackGroupBlockedSegmentsInverted,                    // suspendedSwingingCoaster
        {},                                                    // swingingInverterShip
        {},                                                    // swingingShip
        {},                                                    // topSpin
        {},                                                    // twist
        kTrackGroupBlockedSegmentsNarrow,                      // twisterRollerCoaster
        kTrackGroupBlockedSegmentsWide,                        // virginiaReel
        kTrackGroupBlockedSegmentsNarrow,                      // waterCoaster
        kTrackGroupBlockedSegmentsWoodenRollerCoaster,         // woodenRollerCoaster
        kTrackGroupBlockedSegmentsWoodenWildMouse,             // woodenWildMouse
    });
    static_assert(std::size(kTrackStyleBlockedSegmentType) == EnumValue(TrackStyle::woodenWildMouse) + 1);

    static BlockedSegmentsType OverrideBlockedSegmentsType(
        const TrackStyle trackStyle, const TrackElemType trackElemType, const uint8_t sequence,
        const BlockedSegmentsType blockedSegmentsType)
    {
        if (trackStyle == TrackStyle::mineTrainCoaster)
        {
            // this is narrow since RCT1
            if (trackElemType == TrackElemType::diagLeftBank || trackElemType == TrackElemType::diagRightBank)
            {
                return BlockedSegmentsType::narrow;
            }
        }
        if (trackStyle == TrackStyle::multiDimensionRollerCoaster)
        {
            // multi dimension coaster uses a mix of narrow and wide blocks
            if ((trackElemType == TrackElemType::leftQuarterTurn5Tiles
                 || trackElemType == TrackElemType::bankedLeftQuarterTurn5Tiles)
                && sequence == 0)
            {
                return BlockedSegmentsType::wide;
            }
            if ((trackElemType == TrackElemType::rightQuarterTurn5Tiles
                 || trackElemType == TrackElemType::bankedRightQuarterTurn5Tiles)
                && sequence == 6)
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::bankedLeftQuarterTurn5Tiles
                || trackElemType == TrackElemType::bankedRightQuarterTurn5Tiles)
            {
                return BlockedSegmentsType::narrow;
            }
            if ((trackElemType == TrackElemType::leftQuarterTurn3Tiles
                 || trackElemType == TrackElemType::leftBankedQuarterTurn3Tiles)
                && sequence == 0)
            {
                return BlockedSegmentsType::wide;
            }
            if ((trackElemType == TrackElemType::rightQuarterTurn3Tiles
                 || trackElemType == TrackElemType::rightBankedQuarterTurn3Tiles)
                && sequence == 3)
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::leftBankedQuarterTurn3Tiles
                || trackElemType == TrackElemType::rightBankedQuarterTurn3Tiles)
            {
                return BlockedSegmentsType::narrow;
            }
            if ((trackElemType == TrackElemType::leftEighthToDiag || trackElemType == TrackElemType::rightEighthToDiag
                 || trackElemType == TrackElemType::leftEighthBankToDiag
                 || trackElemType == TrackElemType::rightEighthBankToDiag)
                && (sequence == 0 || sequence == 1 || sequence == 4))
            {
                return BlockedSegmentsType::wide;
            }
            if ((trackElemType == TrackElemType::leftEighthToOrthogonal
                 || trackElemType == TrackElemType::rightEighthToOrthogonal
                 || trackElemType == TrackElemType::leftEighthBankToOrthogonal
                 || trackElemType == TrackElemType::rightEighthBankToOrthogonal)
                && (sequence == 0 || sequence == 3 || sequence == 4))
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::leftHalfBankedHelixUpSmall && (sequence == 0 || sequence == 4 || sequence == 7))
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::rightHalfBankedHelixUpSmall
                && (sequence == 0 || sequence == 3 || sequence == 7))
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::leftHalfBankedHelixDownSmall
                && (sequence == 0 || sequence == 3 || sequence == 4 || sequence == 7))
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::rightHalfBankedHelixDownSmall && (sequence == 3 || sequence == 7))
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::leftHalfBankedHelixUpLarge
                && (sequence == 0 || sequence == 7 || sequence == 13))
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::rightHalfBankedHelixUpLarge
                && (sequence == 0 || sequence == 6 || sequence == 13))
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::leftHalfBankedHelixDownLarge
                && (sequence == 0 || sequence == 6 || sequence == 7 || sequence == 13))
            {
                return BlockedSegmentsType::wide;
            }
            if (trackElemType == TrackElemType::rightHalfBankedHelixDownLarge && (sequence == 6 || sequence == 13))
            {
                return BlockedSegmentsType::wide;
            }
        }
        return blockedSegmentsType;
    }

    static PaintSegments OverrideBlockedSegments(
        const TrackStyle trackStyle, const TrackElemType trackElemType, const uint8_t sequence, const PaintSegments segments)
    {
        if (trackStyle == TrackStyle::boatHire)
        {
            // lacks one segment compared to the default but that support glitches with the track, so maybe this should be
            // removed
            constexpr PaintSegments leftQuarterTurn1Tile = { PaintSegment::bottomLeft, PaintSegment::centre,
                                                             PaintSegment::topLeft };
            if (trackElemType == TrackElemType::leftQuarterTurn1Tile)
            {
                return leftQuarterTurn1Tile;
            }
            if (trackElemType == TrackElemType::rightQuarterTurn1Tile)
            {
                return paintSegmentsFlipXAxis(leftQuarterTurn1Tile);
            }
            // boat hire accidentally blocks all segments on these elements, fix is to remove this
            if (trackElemType == TrackElemType::leftQuarterTurn3Tiles || trackElemType == TrackElemType::rightQuarterTurn3Tiles
                || trackElemType == TrackElemType::leftQuarterTurn5Tiles
                || trackElemType == TrackElemType::rightQuarterTurn5Tiles || trackElemType == TrackElemType::leftEighthToDiag
                || trackElemType == TrackElemType::rightEighthToDiag || trackElemType == TrackElemType::leftEighthToOrthogonal
                || trackElemType == TrackElemType::rightEighthToOrthogonal || trackElemType == TrackElemType::diagFlat
                || trackElemType == TrackElemType::sBendLeft || trackElemType == TrackElemType::sBendRight)
            {
                return kSegmentsAll;
            }
        }
        if (trackStyle == TrackStyle::goKarts)
        {
            // go karts have some unique small turn segments
            constexpr PaintSegments leftQuarterTurn3TilesSeq1 = { PaintSegment::right, PaintSegment::topRight,
                                                                  PaintSegment::bottomRight };
            if ((trackElemType == TrackElemType::leftQuarterTurn3Tiles
                 || trackElemType == TrackElemType::leftQuarterTurn3TilesUp25
                 || trackElemType == TrackElemType::leftQuarterTurn3TilesDown25)
                && sequence == 1)
            {
                return leftQuarterTurn3TilesSeq1;
            }
            if ((trackElemType == TrackElemType::rightQuarterTurn3Tiles
                 || trackElemType == TrackElemType::rightQuarterTurn3TilesUp25
                 || trackElemType == TrackElemType::rightQuarterTurn3TilesDown25)
                && sequence == 1)
            {
                return paintSegmentsFlipXAxis(leftQuarterTurn3TilesSeq1);
            }
        }
        if (trackStyle == TrackStyle::miniSuspendedCoaster || trackStyle == TrackStyle::suspendedSwingingCoaster)
        {
            // these block more segments presumably so that the supports are away from the swinging trains
            constexpr PaintSegments leftEighthToDiagSeq0 = { PaintSegment::centre, PaintSegment::topRight,
                                                             PaintSegment::bottomLeft, PaintSegment::bottomRight };
            constexpr PaintSegments leftEighthToDiagSeq4 = { PaintSegment::right,      PaintSegment::bottom,
                                                             PaintSegment::centre,     PaintSegment::topLeft,
                                                             PaintSegment::topRight,   PaintSegment::bottomLeft,
                                                             PaintSegment::bottomRight };
            if (trackElemType == TrackElemType::leftEighthToDiag)
            {
                if (sequence == 0)
                    return leftEighthToDiagSeq0;
                else if (sequence == 4)
                    return leftEighthToDiagSeq4;
            }
            else if (trackElemType == TrackElemType::rightEighthToDiag)
            {
                if (sequence == 0)
                    return paintSegmentsFlipXAxis(leftEighthToDiagSeq0);
                else if (sequence == 4)
                    return paintSegmentsFlipXAxis(leftEighthToDiagSeq4);
            }
            else if (trackElemType == TrackElemType::leftEighthToOrthogonal)
            {
                if (sequence == 0)
                    return paintSegmentsRotate(paintSegmentsFlipXAxis(leftEighthToDiagSeq4), 2);
                else if (sequence == 4)
                    return paintSegmentsRotate(paintSegmentsFlipXAxis(leftEighthToDiagSeq0), 2);
            }
            else if (trackElemType == TrackElemType::rightEighthToOrthogonal)
            {
                if (sequence == 0)
                    return paintSegmentsRotate(leftEighthToDiagSeq4, 3);
                else if (sequence == 4)
                    return paintSegmentsRotate(leftEighthToDiagSeq0, 3);
            }
        }
        if (trackStyle == TrackStyle::multiDimensionRollerCoaster)
        {
            // multi dimension sbends have some unique segments
            if ((trackElemType == TrackElemType::sBendLeft || trackElemType == TrackElemType::sBendRight)
                && (sequence == 1 || sequence == 2))
            {
                return kSegmentsAll;
            }
        }
        return segments;
    }

    TrackSequenceBlockedSegments GetTrackSequenceBlockedSegments(
        const TrackStyle trackStyle, const TrackElemType trackElemType, const uint8_t sequence)
    {
        if (EnumValue(trackStyle) >= std::size(kTrackStyleBlockedSegmentType)
            || &GetTrackPaintFunction(trackStyle, trackElemType) == &TrackPaintFunctionDummy)
        {
            return {};
        }

        const auto& ted = TrackMetadata::GetTrackElementDescriptor(trackElemType);
        if (sequence >= ted.sequenceData.numSequences)
        {
            return {};
        }
        const auto& sequenceDesc = ted.sequenceData.sequences[sequence];

        BlockedSegmentsType segmentsType = kTrackStyleBlockedSegmentType[EnumValue(trackStyle)]
                                                                        [EnumValue(ted.definition.group)];
        segmentsType = OverrideBlockedSegmentsType(trackStyle, trackElemType, sequence, segmentsType);

        PaintSegments segments = sequenceDesc.blockedSegments[EnumValue(segmentsType)];
        segments = OverrideBlockedSegments(trackStyle, trackElemType, sequence, segments);

        const bool inverted = segmentsType == BlockedSegmentsType::inverted;

        return { segments, sequenceDesc.invertSegmentBlocking != inverted };
    }
} // namespace OpenRCT2
