/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "FlyerInversion.h"

#include "../core/EnumUtils.hpp"
#include "TrackData.h"
#include "ted/TrackElementDescriptor.h"

#include <array>

namespace OpenRCT2::FlyerInversion
{
    using namespace OpenRCT2::TrackMetadata;

    struct LegacyAlias
    {
        TrackElemType legacy;
        TrackElemType standard;
    };

    // Legacy flyer-only elements and the standard elements whose geometry and subposition samples they copy.
    static constexpr LegacyAlias kLegacyAliases[] = {
        { TrackElemType::leftFlyerTwistUp, TrackElemType::leftTwistUpToDown },
        { TrackElemType::rightFlyerTwistUp, TrackElemType::rightTwistUpToDown },
        { TrackElemType::leftFlyerTwistDown, TrackElemType::leftTwistDownToUp },
        { TrackElemType::rightFlyerTwistDown, TrackElemType::rightTwistDownToUp },
        { TrackElemType::flyerHalfLoopUninvertedUp, TrackElemType::halfLoopUp },
        { TrackElemType::flyerHalfLoopInvertedDown, TrackElemType::halfLoopDown },
        { TrackElemType::flyerHalfLoopInvertedUp, TrackElemType::halfLoopUp },
        { TrackElemType::flyerHalfLoopUninvertedDown, TrackElemType::halfLoopDown },
        { TrackElemType::leftFlyerLargeHalfLoopUninvertedUp, TrackElemType::leftLargeHalfLoopUp },
        { TrackElemType::rightFlyerLargeHalfLoopUninvertedUp, TrackElemType::rightLargeHalfLoopUp },
        { TrackElemType::leftFlyerLargeHalfLoopInvertedDown, TrackElemType::leftLargeHalfLoopDown },
        { TrackElemType::rightFlyerLargeHalfLoopInvertedDown, TrackElemType::rightLargeHalfLoopDown },
        { TrackElemType::leftFlyerLargeHalfLoopInvertedUp, TrackElemType::leftLargeHalfLoopUp },
        { TrackElemType::rightFlyerLargeHalfLoopInvertedUp, TrackElemType::rightLargeHalfLoopUp },
        { TrackElemType::leftFlyerLargeHalfLoopUninvertedDown, TrackElemType::leftLargeHalfLoopDown },
        { TrackElemType::rightFlyerLargeHalfLoopUninvertedDown, TrackElemType::rightLargeHalfLoopDown },
        { TrackElemType::leftFlyerCorkscrewUp, TrackElemType::leftCorkscrewUp },
        { TrackElemType::rightFlyerCorkscrewUp, TrackElemType::rightCorkscrewUp },
        { TrackElemType::leftFlyerCorkscrewDown, TrackElemType::leftCorkscrewDown },
        { TrackElemType::rightFlyerCorkscrewDown, TrackElemType::rightCorkscrewDown },
        { TrackElemType::multiDimUp90ToInvertedFlatQuarterLoop, TrackElemType::up90ToInvertedFlatQuarterLoop },
        { TrackElemType::multiDimInvertedUp90ToFlatQuarterLoop, TrackElemType::up90ToInvertedFlatQuarterLoop },
        { TrackElemType::multiDimFlatToDown90QuarterLoop, TrackElemType::invertedFlatToDown90QuarterLoop },
        { TrackElemType::multiDimInvertedFlatToDown90QuarterLoop, TrackElemType::invertedFlatToDown90QuarterLoop },
    };

    static constexpr auto kStandardEquivalents = [] {
        std::array<TrackElemType, EnumValue(TrackElemType::count)> table{};
        table.fill(TrackElemType::none);
        for (const auto& alias : kLegacyAliases)
        {
            table[EnumValue(alias.legacy)] = alias.standard;
        }
        return table;
    }();

    bool IsInvertingPiece(const TrackDefinition& definition)
    {
        return (definition.rollStart == TrackRoll::upsideDown) != (definition.rollEnd == TrackRoll::upsideDown);
    }

    TrackElemType GetStandardEquivalent(TrackElemType trackType)
    {
        const auto index = EnumValue(trackType);
        return index < kStandardEquivalents.size() ? kStandardEquivalents[index] : TrackElemType::none;
    }

    bool IsStandardInversion(TrackElemType trackType)
    {
        return IsInvertingPiece(GetTrackElementDescriptor(trackType).definition)
            && GetStandardEquivalent(trackType) == TrackElemType::none;
    }

    bool IsInvertedAtOtherEnd(const TrackDefinition& definition, bool isInverted)
    {
        return isInverted != IsInvertingPiece(definition);
    }

    bool SupportsEntry(TrackElemType trackType, bool entersInverted)
    {
        const auto& definition = GetTrackElementDescriptor(trackType).definition;
        return !IsStandardInversion(trackType) || entersInverted == (definition.rollStart != TrackRoll::upsideDown);
    }

    TrackRoll GetRollIgnoringInversion(TrackRoll roll)
    {
        return roll == TrackRoll::upsideDown ? TrackRoll::none : roll;
    }

    TrackRoll GetRoll(TrackRoll roll, bool isInverted)
    {
        const auto rollIgnoringInversion = GetRollIgnoringInversion(roll);
        return (isInverted && rollIgnoringInversion == TrackRoll::none) ? TrackRoll::upsideDown : rollIgnoringInversion;
    }
} // namespace OpenRCT2::FlyerInversion
