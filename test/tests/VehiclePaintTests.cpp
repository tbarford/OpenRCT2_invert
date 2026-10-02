/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include <cstdlib>
#include <gtest/gtest.h>
#include <openrct2/paint/vehicle/VehiclePaint.h>
#include <openrct2/ride/FlyerInversion.h>
#include <openrct2/ride/TrackData.h>
#include <openrct2/ride/Vehicle.h>
#include <openrct2/ride/ted/TrackElementDescriptor.h>
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

// Legacy flyer-only elements that copy a standard inversion in its default direction, and the state they are entered in.
// Not multiDimFlatToDown90QuarterLoop: its own table pitches down two samples earlier than the standard one, twice.
struct LegacyCopy
{
    TrackElemType trackType;
    bool enteredInverted;
};

static constexpr LegacyCopy kDefaultDirectionCopies[] = {
    { TrackElemType::leftFlyerTwistUp, false },
    { TrackElemType::rightFlyerTwistUp, false },
    { TrackElemType::leftFlyerTwistDown, true },
    { TrackElemType::rightFlyerTwistDown, true },
    { TrackElemType::flyerHalfLoopInvertedUp, true },
    { TrackElemType::flyerHalfLoopUninvertedDown, false },
    { TrackElemType::leftFlyerLargeHalfLoopInvertedUp, true },
    { TrackElemType::rightFlyerLargeHalfLoopInvertedUp, true },
    { TrackElemType::leftFlyerLargeHalfLoopUninvertedDown, false },
    { TrackElemType::rightFlyerLargeHalfLoopUninvertedDown, false },
    { TrackElemType::multiDimInvertedUp90ToFlatQuarterLoop, true },
};

static VehiclePitch WithoutUninverting(VehiclePitch pitch)
{
    switch (pitch)
    {
        case VehiclePitch::uninvertingDown25:
            return VehiclePitch::down25;
        case VehiclePitch::uninvertingDown42:
            return VehiclePitch::down42;
        case VehiclePitch::uninvertingDown60:
            return VehiclePitch::down60;
        default:
            return pitch;
    }
}

static VehicleRoll WithoutUninverting(VehicleRoll roll)
{
    switch (roll)
    {
        case VehicleRoll::uninvertingUnbanked:
            return VehicleRoll::unbanked;
        case VehicleRoll::uninvertingLeft22:
            return VehicleRoll::left22;
        case VehicleRoll::uninvertingLeft45:
            return VehicleRoll::left45;
        case VehicleRoll::uninvertingRight22:
            return VehicleRoll::right22;
        case VehicleRoll::uninvertingRight45:
            return VehicleRoll::right45;
        default:
            return roll;
    }
}

// How a legacy element's sample is drawn: its own pose and the inverted car set's swaps.
static VehiclePaintPose LegacyPose(const VehicleInfo& sample, TrackElemType trackType, bool enteredInverted)
{
    const bool usesInvertedCarSet = enteredInverted && !InvertedCarDrawsWithUprightSet(trackType, sample.pitch, sample.roll);
    return { sample.yaw, WithoutUninverting(sample.pitch), WithoutUninverting(sample.roll), usesInvertedCarSet,
             enteredInverted ? 16 : 0 };
}

// The pose as it appears on screen, assuming the inverted set draws each pose rolled half a turn.
static VehiclePaintPose Appearance(const VehiclePaintPose& pose)
{
    return pose.usesInvertedCarSet ? HalfRoll(pose) : pose;
}

// Height of a sample above the connection the element is entered from.
static int32_t SampleHeight(TrackElemType trackType, const VehicleInfo& sample)
{
    const auto& ted = TrackMetadata::GetTrackElementDescriptor(trackType);
    return sample.z + ted.sequenceData.sequences[0].clearance.z - ted.coordinates.zBegin;
}

TEST(VehiclePaintTest, StandardInversionsLookLikeTheLegacyElementsThatCopyThem)
{
    constexpr auto kSubposition = VehicleTrackSubposition::standard;
    for (const auto& copy : kDefaultDirectionCopies)
    {
        const auto standardType = FlyerInversion::GetStandardEquivalent(copy.trackType);
        ASSERT_TRUE(FlyerInversion::SupportsEntry(standardType, copy.enteredInverted));
        for (uint8_t direction = 0; direction < 4; direction++)
        {
            const auto numSamples = VehicleGetMoveInfoSize(kSubposition, standardType, direction);
            ASSERT_EQ(VehicleGetMoveInfoSize(kSubposition, copy.trackType, direction), numSamples);

            const auto& firstSample = *VehicleGetMoveInfo(kSubposition, standardType, direction, 0);
            for (int32_t progress = 0; progress < numSamples; progress++)
            {
                const auto& legacySample = *VehicleGetMoveInfo(kSubposition, copy.trackType, direction, progress);
                const auto& standardSample = *VehicleGetMoveInfo(kSubposition, standardType, direction, progress);
                const auto legacy = Appearance(LegacyPose(legacySample, copy.trackType, copy.enteredInverted));
                const auto drawn = Appearance(GetFlyerPoseOnStandardSample(standardSample, firstSample, copy.enteredInverted));
                const auto where = testing::Message() << "track type " << EnumValue(copy.trackType) << " direction "
                                                      << static_cast<int>(direction) << " progress " << progress;

                EXPECT_EQ(drawn.yaw, legacy.yaw) << where;
                EXPECT_EQ(drawn.pitch, legacy.pitch) << where;
                EXPECT_EQ(drawn.roll, legacy.roll) << where;

                // The original small half loop table is up to 2 units off on a few samples.
                const auto legacyHeight = SampleHeight(copy.trackType, legacySample) + legacy.zOffset;
                const auto drawnHeight = SampleHeight(standardType, standardSample) + drawn.zOffset;
                EXPECT_LE(std::abs(drawnHeight - legacyHeight), 2) << where;
            }
        }
    }
}
