/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include <gtest/gtest.h>
#include <openrct2/paint/vehicle/VehiclePaint.h>
#include <openrct2/ride/Vehicle.h>
#include <string>

using namespace OpenRCT2;

// The car set an inverted car is drawn with along each legacy flyer-only element it enters inverted, as run lengths
// of I (inverted set) and U (upright set). Recorded from the vehicle painter's per-pose car set swaps before they
// were gathered into InvertedCarDrawsWithUprightSet. The same in all four directions.
struct ExpectedCarSets
{
    TrackElemType trackType;
    const char* runs;
};

static constexpr ExpectedCarSets kExpectedCarSets[] = {
    { TrackElemType::leftFlyerTwistDown, "5I 85U 6I" },
    { TrackElemType::rightFlyerTwistDown, "5I 85U 6I" },
    { TrackElemType::flyerHalfLoopInvertedDown, "5I 155U" },
    { TrackElemType::flyerHalfLoopInvertedUp, "160I" },
    { TrackElemType::leftFlyerLargeHalfLoopInvertedDown, "15I 296U" },
    { TrackElemType::rightFlyerLargeHalfLoopInvertedDown, "15I 296U" },
    { TrackElemType::leftFlyerLargeHalfLoopInvertedUp, "311I" },
    { TrackElemType::rightFlyerLargeHalfLoopInvertedUp, "311I" },
    { TrackElemType::leftFlyerCorkscrewDown, "8I 82U 7I" },
    { TrackElemType::rightFlyerCorkscrewDown, "8I 82U 7I" },
    { TrackElemType::multiDimInvertedUp90ToFlatQuarterLoop, "137I" },
    { TrackElemType::multiDimInvertedFlatToDown90QuarterLoop, "9I 128U" },
};

static std::string CarSetRuns(TrackElemType trackType, uint8_t direction)
{
    constexpr auto kSubposition = VehicleTrackSubposition::standard;
    const auto numSamples = VehicleGetMoveInfoSize(kSubposition, trackType, direction);

    std::string runs;
    char current = 0;
    int32_t count = 0;
    for (int32_t progress = 0; progress <= numSamples; progress++)
    {
        char set = 0;
        if (progress < numSamples)
        {
            const auto& sample = *VehicleGetMoveInfo(kSubposition, trackType, direction, progress);
            set = InvertedCarDrawsWithUprightSet(trackType, sample.pitch, sample.roll) ? 'U' : 'I';
        }
        if (set != current && count > 0)
        {
            runs += (runs.empty() ? "" : " ") + std::to_string(count) + current;
            count = 0;
        }
        current = set;
        count++;
    }
    return runs;
}

TEST(VehiclePaintTest, LegacyElementsEnteredInvertedKeepTheirCarSets)
{
    for (const auto& expected : kExpectedCarSets)
    {
        for (uint8_t direction = 0; direction < 4; direction++)
        {
            EXPECT_EQ(CarSetRuns(expected.trackType, direction), expected.runs)
                << "track type " << EnumValue(expected.trackType) << " direction " << static_cast<int>(direction);
        }
    }
}

TEST(VehiclePaintTest, VerticalDropTrackKeepsTheInvertedSet)
{
    EXPECT_TRUE(InvertedCarDrawsWithUprightSet(TrackElemType::flat, VehiclePitch::down90, VehicleRoll::unbanked));
    EXPECT_FALSE(InvertedCarDrawsWithUprightSet(TrackElemType::down90, VehiclePitch::down90, VehicleRoll::unbanked));
    EXPECT_FALSE(InvertedCarDrawsWithUprightSet(TrackElemType::down60ToDown90, VehiclePitch::down75, VehicleRoll::unbanked));
    EXPECT_FALSE(InvertedCarDrawsWithUprightSet(TrackElemType::down90ToDown60, VehiclePitch::down90, VehicleRoll::unbanked));
}
