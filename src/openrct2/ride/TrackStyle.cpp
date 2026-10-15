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
            array[EnumValue(TrackGroup::helixUpBankedQuarter)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::helixDownBankedQuarter)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::helixUpUnbankedQuarter)] = BlockedSegmentsType::wide;
            array[EnumValue(TrackGroup::helixDownUnbankedQuarter)] = BlockedSegmentsType::wide;
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

    // these block one more segment than the inverted segments on some eighth turn tiles, which keeps the supports away
    // from the swinging trains.
    // kSegmentsNone uses the inverted segments.
    static_assert(
        EnumValue(TrackElemType::rightEighthToDiag) == EnumValue(TrackElemType::leftEighthToDiag) + 1
        && EnumValue(TrackElemType::leftEighthToOrthogonal) == EnumValue(TrackElemType::leftEighthToDiag) + 2
        && EnumValue(TrackElemType::rightEighthToOrthogonal) == EnumValue(TrackElemType::leftEighthToDiag) + 3);
    static constexpr const auto kSuspendedEighthSegments = []() consteval {
        std::array<std::array<PaintSegments, 5>, 4> array{};
        // leftEighthToDiag
        array[0][0] = { PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottomRight };
        array[0][4] = { PaintSegment::right,    PaintSegment::bottom,     PaintSegment::centre,     PaintSegment::topLeft,
                        PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottomRight };
        // rightEighthToDiag
        array[1][0] = { PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::bottomLeft };
        // leftEighthToOrthogonal
        array[2][4] = { PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottomRight };
        // rightEighthToOrthogonal
        array[3][0] = { PaintSegment::top,      PaintSegment::right,      PaintSegment::centre,     PaintSegment::topLeft,
                        PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottomRight };
        array[3][4] = { PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::bottomRight };
        return array;
    }();

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
            const size_t piece = static_cast<size_t>(EnumValue(trackElemType)) - EnumValue(TrackElemType::leftEighthToDiag);
            if (piece < kSuspendedEighthSegments.size() && sequence < kSuspendedEighthSegments[piece].size()
                && kSuspendedEighthSegments[piece][sequence] != kSegmentsNone)
            {
                return kSuspendedEighthSegments[piece][sequence];
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

    // Per piece overrides of the blocked segments type from the track group table, as one bit per sequence
    struct BlockedSegmentsOverrides
    {
        uint16_t narrow = 0;
        uint16_t wide = 0; // takes precedence over narrow
        uint16_t all = 0;  // blocks all segments
    };
    using TrackElemTypeBlockedSegmentsOverrides = std::array<BlockedSegmentsOverrides, EnumValue(TrackElemType::count)>;

    static constexpr const TrackElemTypeBlockedSegmentsOverrides kBlockedSegmentsOverridesNone{};

    static constexpr const TrackElemTypeBlockedSegmentsOverrides kBlockedSegmentsOverridesMultiDimensionRollerCoaster =
        []() consteval {
            TrackElemTypeBlockedSegmentsOverrides array{};
            constexpr uint16_t kAllSequences = 0xFFFF;
            // multi dimension coaster uses a mix of narrow and wide blocks
            array[EnumValue(TrackElemType::leftQuarterTurn5Tiles)].wide = 1 << 0;
            array[EnumValue(TrackElemType::bankedLeftQuarterTurn5Tiles)] = { kAllSequences, 1 << 0 };
            array[EnumValue(TrackElemType::rightQuarterTurn5Tiles)].wide = 1 << 6;
            array[EnumValue(TrackElemType::bankedRightQuarterTurn5Tiles)] = { kAllSequences, 1 << 6 };
            array[EnumValue(TrackElemType::leftQuarterTurn3Tiles)].wide = 1 << 0;
            array[EnumValue(TrackElemType::leftBankedQuarterTurn3Tiles)] = { kAllSequences, 1 << 0 };
            array[EnumValue(TrackElemType::rightQuarterTurn3Tiles)].wide = 1 << 3;
            array[EnumValue(TrackElemType::rightBankedQuarterTurn3Tiles)] = { kAllSequences, 1 << 3 };
            array[EnumValue(TrackElemType::leftEighthToDiag)].wide = (1 << 0) | (1 << 1) | (1 << 4);
            array[EnumValue(TrackElemType::rightEighthToDiag)].wide = (1 << 0) | (1 << 1) | (1 << 4);
            array[EnumValue(TrackElemType::leftEighthBankToDiag)].wide = (1 << 0) | (1 << 1) | (1 << 4);
            array[EnumValue(TrackElemType::rightEighthBankToDiag)].wide = (1 << 0) | (1 << 1) | (1 << 4);
            array[EnumValue(TrackElemType::leftEighthToOrthogonal)].wide = (1 << 0) | (1 << 3) | (1 << 4);
            array[EnumValue(TrackElemType::rightEighthToOrthogonal)].wide = (1 << 0) | (1 << 3) | (1 << 4);
            array[EnumValue(TrackElemType::leftEighthBankToOrthogonal)].wide = (1 << 0) | (1 << 3) | (1 << 4);
            array[EnumValue(TrackElemType::rightEighthBankToOrthogonal)].wide = (1 << 0) | (1 << 3) | (1 << 4);
            array[EnumValue(TrackElemType::leftHalfBankedHelixUpSmall)].wide = (1 << 0) | (1 << 4) | (1 << 7);
            array[EnumValue(TrackElemType::rightHalfBankedHelixUpSmall)].wide = (1 << 0) | (1 << 3) | (1 << 7);
            array[EnumValue(TrackElemType::leftHalfBankedHelixDownSmall)].wide = (1 << 0) | (1 << 3) | (1 << 4) | (1 << 7);
            array[EnumValue(TrackElemType::rightHalfBankedHelixDownSmall)].wide = (1 << 3) | (1 << 7);
            array[EnumValue(TrackElemType::leftHalfBankedHelixUpLarge)].wide = (1 << 0) | (1 << 7) | (1 << 13);
            array[EnumValue(TrackElemType::rightHalfBankedHelixUpLarge)].wide = (1 << 0) | (1 << 6) | (1 << 13);
            array[EnumValue(TrackElemType::leftHalfBankedHelixDownLarge)].wide = (1 << 0) | (1 << 6) | (1 << 7) | (1 << 13);
            array[EnumValue(TrackElemType::rightHalfBankedHelixDownLarge)].wide = (1 << 6) | (1 << 13);
            // multi dimension sbends have some unique segments
            array[EnumValue(TrackElemType::sBendLeft)].all = (1 << 1) | (1 << 2);
            array[EnumValue(TrackElemType::sBendRight)].all = (1 << 1) | (1 << 2);
            return array;
        }();

    struct TrackBlockedSegmentsProfile
    {
        TrackGroupBlockedSegmentTypes groupTypes;
        const TrackElemTypeBlockedSegmentsOverrides* overrides;
    };

    static constexpr auto kTrackBlockedSegmentsProfiles = std::to_array<TrackBlockedSegmentsProfile>({
        { {}, &kBlockedSegmentsOverridesNone },                                 // none
        { kTrackGroupBlockedSegmentsNarrow, &kBlockedSegmentsOverridesNone },   // narrow
        { kTrackGroupBlockedSegmentsInverted, &kBlockedSegmentsOverridesNone }, // inverted
        { kTrackGroupBlockedSegmentsWide, &kBlockedSegmentsOverridesNone },     // wide
        { kTrackGroupBlockedSegmentsMultiDimensionRollerCoaster,
          &kBlockedSegmentsOverridesMultiDimensionRollerCoaster }, // multiDimensionRollerCoaster
    });
    static_assert(std::size(kTrackBlockedSegmentsProfiles) == EnumValue(TrackBlockedSegments::count));

    TrackSequenceBlockedSegments GetTrackSequenceBlockedSegments(
        const TrackBlockedSegments trackBlockedSegments, const TrackElemType trackElemType, const uint8_t sequence)
    {
        const auto& profile = kTrackBlockedSegmentsProfiles[EnumValue(trackBlockedSegments)];
        const auto& ted = TrackMetadata::GetTrackElementDescriptor(trackElemType);
        const auto& sequenceDesc = ted.sequenceData.sequences[sequence];
        const auto& overrides = (*profile.overrides)[EnumValue(trackElemType)];
        const uint16_t sequenceBit = static_cast<uint16_t>(1u << sequence);

        BlockedSegmentsType segmentsType = profile.groupTypes[EnumValue(ted.definition.group)];
        if (overrides.narrow & sequenceBit)
            segmentsType = BlockedSegmentsType::narrow;
        if (overrides.wide & sequenceBit)
            segmentsType = BlockedSegmentsType::wide;

        const PaintSegments segments = (overrides.all & sequenceBit) ? kSegmentsAll
                                                                     : sequenceDesc.blockedSegments[EnumValue(segmentsType)];
        const bool inverted = segmentsType == BlockedSegmentsType::inverted;
        return { segments, sequenceDesc.invertSegmentBlocking != inverted };
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
