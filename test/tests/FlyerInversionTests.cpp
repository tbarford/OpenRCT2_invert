/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include <gtest/gtest.h>
#include <openrct2/core/EnumUtils.hpp>
#include <openrct2/ride/FlyerInversion.h>
#include <openrct2/ride/Ride.h>
#include <openrct2/ride/Track.h>
#include <openrct2/ride/TrackData.h>
#include <openrct2/ride/ted/TrackElementDescriptor.h>

using namespace OpenRCT2;
using namespace OpenRCT2::TrackMetadata;

static constexpr bool kStates[] = { false, true };

static TrackElemType TrackTypeAt(size_t index)
{
    return static_cast<TrackElemType>(index);
}

// Outside the standard inversions, the roll at each end is what the ride has always used: the descriptor roll with
// none and upsideDown swapped on inverted elements.
TEST(FlyerInversionTest, RollsAtEndsMatchTheRideOutsideStandardInversions)
{
    for (size_t i = 0; i < EnumValue(TrackElemType::count); i++)
    {
        const auto trackType = TrackTypeAt(i);
        if (FlyerInversion::IsStandardInversion(trackType))
            continue;

        const auto& definition = GetTrackElementDescriptor(trackType).definition;
        for (const bool isInverted : kStates)
        {
            const bool isInvertedAtEnd = FlyerInversion::IsInvertedAtOtherEnd(definition, isInverted);
            EXPECT_EQ(
                FlyerInversion::GetRoll(definition.rollStart, isInverted),
                TrackGetActualBank2(RIDE_TYPE_FLYING_ROLLER_COASTER, isInverted, definition.rollStart))
                << "track type " << i;
            EXPECT_EQ(
                FlyerInversion::GetRoll(definition.rollEnd, isInvertedAtEnd),
                TrackGetActualBank2(RIDE_TYPE_FLYING_ROLLER_COASTER, isInverted, definition.rollEnd))
                << "track type " << i;
        }
    }
}

// A standard inversion entered in its default direction turns the car over, and its ends report the car state.
TEST(FlyerInversionTest, StandardInversionsTurnTheCarOverInTheirDefaultDirection)
{
    for (size_t i = 0; i < EnumValue(TrackElemType::count); i++)
    {
        const auto trackType = TrackTypeAt(i);
        if (!FlyerInversion::IsStandardInversion(trackType))
            continue;

        const auto& definition = GetTrackElementDescriptor(trackType).definition;
        const bool entersInverted = definition.rollStart != TrackRoll::upsideDown;
        const bool exitsInverted = FlyerInversion::IsInvertedAtOtherEnd(definition, entersInverted);
        const auto upright = TrackRoll::none;
        const auto inverted = TrackRoll::upsideDown;

        EXPECT_TRUE(FlyerInversion::SupportsEntry(trackType, entersInverted)) << "track type " << i;
        EXPECT_FALSE(FlyerInversion::SupportsEntry(trackType, !entersInverted)) << "track type " << i;
        EXPECT_NE(entersInverted, exitsInverted) << "track type " << i;
        EXPECT_EQ(FlyerInversion::GetRoll(definition.rollStart, entersInverted), entersInverted ? inverted : upright)
            << "track type " << i;
        EXPECT_EQ(FlyerInversion::GetRoll(definition.rollEnd, exitsInverted), exitsInverted ? inverted : upright)
            << "track type " << i;
    }
}

// Every inverting piece is either a standard inversion or a legacy flyer-only element that copies one.
TEST(FlyerInversionTest, LegacyElementsCopyAStandardInversion)
{
    size_t numStandard = 0;
    size_t numLegacy = 0;
    for (size_t i = 0; i < EnumValue(TrackElemType::count); i++)
    {
        const auto trackType = TrackTypeAt(i);
        const auto& definition = GetTrackElementDescriptor(trackType).definition;
        const auto standardType = FlyerInversion::GetStandardEquivalent(trackType);
        if (standardType == TrackElemType::none)
        {
            numStandard += FlyerInversion::IsStandardInversion(trackType);
            continue;
        }

        numLegacy++;
        const auto& standard = GetTrackElementDescriptor(standardType).definition;
        EXPECT_TRUE(FlyerInversion::IsInvertingPiece(definition)) << "track type " << i;
        EXPECT_FALSE(FlyerInversion::IsStandardInversion(trackType)) << "track type " << i;
        EXPECT_TRUE(FlyerInversion::IsStandardInversion(standardType)) << "track type " << i;
        EXPECT_EQ(definition.pitchStart, standard.pitchStart) << "track type " << i;
        EXPECT_EQ(definition.pitchEnd, standard.pitchEnd) << "track type " << i;
    }

    // Twists, barrel rolls, quarter loops, dive loops, zero-G rolls, large zero-G rolls, small, medium and large half
    // loops, small and large corkscrews.
    EXPECT_EQ(numStandard, 4u + 4 + 2 + 4 + 4 + 4 + 2 + 4 + 4 + 4 + 4);
    EXPECT_EQ(numLegacy, 24u);
}
