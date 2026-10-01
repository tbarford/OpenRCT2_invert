/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "../../../SpriteIds.h"
#include "../../../ride/TrackPaint.h"
#include "../../../ride/ted/TrackElemType.h"
#include "../../../world/tile_element/TrackElement.h"
#include "../../track/Segment.h"

#include <cstdint>

using namespace OpenRCT2;

static constexpr TunnelGroup kTunnelGroup = TunnelGroup::square;
static constexpr uint8_t kSupportHeight = 39;
static constexpr uint8_t kInvertedSpriteOffset = 24;

static constexpr const uint32_t kInvertedRCDiagBrakeImages[kNumOrthogonalDirections] = {
    SPR_TRACKS_BM_INVERT_DIAG_BRAKES,
    SPR_TRACKS_BM_INVERT_DIAG_BRAKES + 1,
    SPR_TRACKS_BM_INVERT_DIAG_BRAKES,
    SPR_TRACKS_BM_INVERT_DIAG_BRAKES + 1,
};

/** rct2: 0x007C6FF4 */
static void InvertedFlyingRCTrackFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    if (trackElement.hasChain())
    {
        switch (direction)
        {
            case 0:
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27131), { 0, 0, height + 24 },
                    { { 0, 6, height + 22 }, { 32, 20, 1 } });
                break;
            case 1:
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27132), { 0, 0, height + 24 },
                    { { 0, 6, height + 22 }, { 32, 20, 1 } });
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27129), { 0, 0, height + 24 },
                    { { 0, 6, height + 22 }, { 32, 20, 1 } });
                break;
            case 1:
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27130), { 0, 0, height + 24 },
                    { { 0, 6, height + 22 }, { 32, 20, 1 } });
                break;
        }
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C7244, 0x007C7254, 0x007C7264 */
static void InvertedFlyingRCTrackStation(
    PaintSession& session, const Ride& ride, [[maybe_unused]] uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    static constexpr ImageIndex imageIds[4][2] = {
        { 27131, SPR_STATION_INVERTED_BAR_C_SW_NE },
        { 27132, SPR_STATION_INVERTED_BAR_C_NW_SE },
        { 27131, SPR_STATION_INVERTED_BAR_C_SW_NE },
        { 27132, SPR_STATION_INVERTED_BAR_C_NW_SE },
    };
    const bool stationDrawn = TrackPaintUtilDrawStationInverted(
        session, ride, direction, height, trackElement, STATION_VARIANT_1);
    PaintAddImageAsParentRotated(
        session, direction, session.TrackColours.WithIndex(imageIds[direction][0]), { 0, 0, height + 24 },
        { { 0, 6, height + 24 }, { 32, 20, 3 } });
    if (stationDrawn)
    {
        PaintAddImageAsChildRotated(
            session, direction, session.SupportColours.WithIndex(imageIds[direction][1]), { 0, 6, height + 24 },
            { { 0, 6, height + 24 }, { 32, 20, 3 } });
        DrawSupportsSideBySide(session, direction, height, session.SupportColours, supportType.metal);
    }
    TrackPaintUtilDrawStationTunnel(session, direction, height);
    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C7004 */
static void InvertedFlyingRCTrack25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    if (trackElement.hasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27249), { 0, 0, height + 24 },
                    { { 0, 6, height + 40 }, { 32, 20, 3 } });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27250), { 0, 0, height + 24 },
                    { { 0, 6, height + 40 }, { 32, 20, 3 } });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27251), { 0, 0, height + 24 },
                    { { 0, 6, height + 40 }, { 32, 20, 3 } });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27252), { 0, 0, height + 24 },
                    { { 0, 6, height + 40 }, { 32, 20, 3 } });
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27221), { 0, 0, height + 24 },
                    { { 0, 6, height + 40 }, { 32, 20, 3 } });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27222), { 0, 0, height + 24 },
                    { { 0, 6, height + 40 }, { 32, 20, 3 } });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27223), { 0, 0, height + 24 },
                    { { 0, 6, height + 40 }, { 32, 20, 3 } });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27224), { 0, 0, height + 24 },
                    { { 0, 6, height + 40 }, { 32, 20, 3 } });
                break;
        }
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 57, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x007C7014 */
static void InvertedFlyingRCTrack60DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27237), { 0, 0, height + 24 },
                { { 0, 6, height + 88 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27238), { 0, 0, height + 24 },
                { { 0, 4, height + 6 }, { 32, 2, 81 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27239), { 0, 0, height + 24 },
                { { 0, 4, height + 6 }, { 32, 2, 81 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27240), { 0, 0, height + 24 },
                { { 0, 6, height + 88 }, { 32, 20, 3 } });
            break;
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 56, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 104);
}

/** rct2: 0x007C7024 */
static void InvertedFlyingRCTrackFlatTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    if (trackElement.hasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27241), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27242), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27243), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27244), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27213), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27214), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27215), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27216), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
        }
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 49, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 48);
}

/** rct2: 0x007C7034 */
static void InvertedFlyingRCTrack25DegUpTo60DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27225), { 0, 0, height + 24 },
                { { 0, 6, height + 56 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27229), { 0, 0, height + 24 },
                { { 0, 10, height + 6 }, { 32, 10, 49 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27226), { 0, 0, height + 24 },
                { { 0, 4, height + 6 }, { 32, 2, 49 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27230), { 0, 0, height + 24 },
                { { 0, 10, height + 6 }, { 32, 10, 49 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27227), { 0, 0, height + 24 },
                { { 0, 4, height + 6 }, { 32, 2, 49 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27228), { 0, 0, height + 24 },
                { { 0, 6, height + 56 }, { 32, 20, 3 } });
            break;
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 24, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

/** rct2: 0x007C7044 */
static void InvertedFlyingRCTrack60DegUpTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27231), { 0, 0, height + 24 },
                { { 0, 6, height + 56 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27235), { 0, 0, height + 24 },
                { { 0, 10, height + 6 }, { 32, 10, 49 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27232), { 0, 0, height + 24 },
                { { 0, 4, height + 6 }, { 32, 2, 49 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27236), { 0, 0, height + 24 },
                { { 0, 10, height + 6 }, { 32, 10, 49 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27233), { 0, 0, height + 24 },
                { { 0, 4, height + 6 }, { 32, 2, 49 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27234), { 0, 0, height + 24 },
                { { 0, 6, height + 56 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 71, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 24, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

/** rct2: 0x007C7054 */
static void InvertedFlyingRCTrack25DegUpToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    if (trackElement.hasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27245), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27246), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27247), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27248), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27217), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27218), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27219), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(27220), { 0, 0, height + 24 },
                    { { 0, 6, height + 32 }, { 32, 20, 3 } });
                break;
        }
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::flatTo25Deg);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 40);
}

/** rct2: 0x007C7064 */
static void InvertedFlyingRCTrack25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7074 */
static void InvertedFlyingRCTrack60DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack60DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7084 */
static void InvertedFlyingRCTrackFlatTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUpToFlat(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7094 */
static void InvertedFlyingRCTrack25DegDownTo60DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack60DegUpTo25DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C70A4 */
static void InvertedFlyingRCTrack60DegDownTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUpTo60DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C70B4 */
static void InvertedFlyingRCTrack25DegDownToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackFlatTo25DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C70C4 */
static void InvertedFlyingRCTrackLeftQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27142), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27147), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27152), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27137), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27141), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27146), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27151), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27136), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27140), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27145), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27150), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27135), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27139), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27144), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27149), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27134), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27138), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27143), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27148), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27133), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C70D4 */
static void InvertedFlyingRCTrackRightQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    InvertedFlyingRCTrackLeftQuarterTurn5(session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C70E4 */
static void InvertedFlyingRCTrackFlatToLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27269), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27270), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27271), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27272), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
              PaintSegment::bottomRight },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C70F4 */
static void InvertedFlyingRCTrackFlatToRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27273), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27274), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27275), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27276), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
              PaintSegment::bottomLeft },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C7104 */
static void InvertedFlyingRCTrackLeftBankToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27275), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27276), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27273), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27274), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
              PaintSegment::bottomRight },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C7114 */
static void InvertedFlyingRCTrackRightBankToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27271), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27272), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27269), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27270), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
              PaintSegment::bottomLeft },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C7124 */
static void InvertedFlyingRCTrackBankedLeftQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27162), { 0, 0, height + 24 },
                        { { 0, 6, height + 24 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27167), { 0, 0, height + 24 },
                        { { 0, 6, height + 24 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27172), { 0, 0, height + 24 },
                        { { 0, 6, height + 24 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27157), { 0, 0, height + 24 },
                        { { 0, 6, height + 24 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27161), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27166), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27171), { 0, 0, height + 24 },
                        { { 0, 16, height + 24 }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27156), { 0, 0, height + 24 },
                        { { 0, 16, height + 24 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27160), { 0, 0, height + 24 },
                        { { 0, 16, height + 24 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27165), { 0, 0, height + 24 },
                        { { 16, 16, height + 24 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27170), { 0, 0, height + 24 },
                        { { 16, 0, height + 24 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27155), { 0, 0, height + 24 }, { 16, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27159), { 0, 0, height + 24 },
                        { { 16, 0, height + 24 }, { 16, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27164), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27169), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27154), { 0, 0, height + 24 },
                        { { 16, 0, height + 24 }, { 16, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27158), { 0, 0, height + 24 },
                        { { 6, 0, height + 24 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27163), { 0, 0, height + 24 },
                        { { 6, 0, height + 24 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27168), { 0, 0, height + 24 },
                        { { 6, 0, height + 24 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27153), { 0, 0, height + 24 },
                        { { 6, 0, height + 24 }, { 20, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7134 */
static void InvertedFlyingRCTrackBankedRightQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    InvertedFlyingRCTrackBankedLeftQuarterTurn5(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7144 */
static void InvertedFlyingRCTrackLeftBankTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27277), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27278), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27279), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27280), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
              PaintSegment::bottomRight },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 48);
}

/** rct2: 0x007C7154 */
static void InvertedFlyingRCTrackRightBankTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27281), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27282), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27283), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27284), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
              PaintSegment::bottomLeft },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 48);
}

/** rct2: 0x007C7164 */
static void InvertedFlyingRCTrack25DegUpToLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27285), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27286), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27287), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27288), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
              PaintSegment::bottomRight },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::flatTo25Deg);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 40);
}

/** rct2: 0x007C7174 */
static void InvertedFlyingRCTrack25DegUpToRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27289), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27290), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27291), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27292), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
              PaintSegment::bottomLeft },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::flatTo25Deg);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 40);
}

/** rct2: 0x007C7184 */
static void InvertedFlyingRCTrackLeftBankTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUpToRightBank(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7194 */
static void InvertedFlyingRCTrackRightBankTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUpToLeftBank(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C71A4 */
static void InvertedFlyingRCTrack25DegDownToLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightBankTo25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C71B4 */
static void InvertedFlyingRCTrack25DegDownToRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftBankTo25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C71C4 */
static void InvertedFlyingRCTrackLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27293), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27294), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27295), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27296), { 0, 0, height + 24 },
                { { 0, 6, height + 22 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
              PaintSegment::bottomRight },
            direction),
        0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C71D4 */
static void InvertedFlyingRCTrackRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftBank(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C71E4 */
static void InvertedFlyingRCTrackLeftQuarterTurn525DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27317), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27322), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27327), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27332), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 49, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27318), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27323), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27328), { 0, 16, height + 24 }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27333), { 0, 16, height + 24 }, { 32, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27319), { 0, 16, height + 24 }, { 16, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27324), { 16, 16, height + 24 }, { 16, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27329), { 16, 0, height + 24 }, { 16, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27334), { 0, 0, height + 24 }, { 16, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27320), { 16, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27325), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27330), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27335), { 16, 0, height + 24 }, { 16, 32, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27321), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27326), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27331), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27336), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 49, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x007C71F4 */
static void InvertedFlyingRCTrackRightQuarterTurn525DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27297), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27302), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27307), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27312), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 49, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27298), { 0, 16, height + 24 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27303), { 0, 16, height + 24 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27308), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27313), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27299), { 0, 0, height + 24 }, { 16, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27304), { 16, 0, height + 24 }, { 16, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27309), { 16, 16, height + 24 }, { 16, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27314), { 0, 16, height + 24 }, { 16, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27300), { 16, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27305), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27310), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27315), { 16, 0, height + 24 }, { 16, 32, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27301), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27306), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27311), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27316), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 49, session.SupportColours);

            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x007C7204 */
static void InvertedFlyingRCTrackLeftQuarterTurn525DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    InvertedFlyingRCTrackRightQuarterTurn525DegUp(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7214 */
static void InvertedFlyingRCTrackRightQuarterTurn525DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    InvertedFlyingRCTrackLeftQuarterTurn525DegUp(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7224 */
static void InvertedFlyingRCTrackSBendLeft(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27253), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27257), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27256), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27260), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27254), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 26, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27258), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 26, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27255), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 26, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27259), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 26, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 0, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 1:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 0, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27255), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 26, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27259), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 26, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27254), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 26, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27258), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 26, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 2:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 0, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 3:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 0, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27256), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27260), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27253), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27257), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7234 */
static void InvertedFlyingRCTrackSBendRight(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27261), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27265), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27264), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27268), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27262), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 26, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27266), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 26, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27263), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 26, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27267), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 26, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 0, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 1:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27263), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 26, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27267), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 26, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27262), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 26, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27266), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 26, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 2:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 0, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 3:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27264), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27268), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27261), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27265), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7274 */
static void InvertedFlyingRCTrackLeftQuarterTurn3(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27392), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27395), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27398), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27389), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27391), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27394), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27397), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27388), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27390), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27393), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27396), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27387), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7284 */
static void InvertedFlyingRCTrackRightQuarterTurn3(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    InvertedFlyingRCTrackLeftQuarterTurn3(session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7294 */
static void InvertedFlyingRCTrackLeftQuarterTurn3Bank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27404), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27407), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27410), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27401), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27403), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27406), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27409), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27400), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27402), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27405), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27408), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27399), { 0, 0, height + 24 },
                        { { 6, 0, height + 22 }, { 20, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C72A4 */
static void InvertedFlyingRCTrackRightQuarterTurn3Bank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    InvertedFlyingRCTrackLeftQuarterTurn3Bank(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C72B4 */
static void InvertedFlyingRCTrackLeftQuarterTurn325DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27422), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27424), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27426), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27420), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 47, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 2:
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27421), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27423), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27425), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27419), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 47, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x007C72C4 */
static void InvertedFlyingRCTrackRightQuarterTurn325DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27411), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27413), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27415), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27417), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 47, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 2:
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27412), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27414), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27416), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27418), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 47, session.SupportColours);

            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x007C72D4 */
static void InvertedFlyingRCTrackLeftQuarterTurn325DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    InvertedFlyingRCTrackRightQuarterTurn325DegUp(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C72E4 */
static void InvertedFlyingRCTrackRightQuarterTurn325DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    InvertedFlyingRCTrackLeftQuarterTurn325DegUp(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C73B4 */
static void InvertedFlyingRCTrackLeftQuarterTurn160DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27352), { 0, 0, height - 5 },
                { { 2, 2, height - 5 }, { 28, 28, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27348), { 0, 0, height - 5 },
                { { 2, 2, height + 94 }, { 28, 28, 1 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27353), { 0, 0, height - 5 },
                { { 2, 2, height - 5 }, { 28, 28, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27349), { 0, 0, height - 5 },
                { { 2, 2, height + 94 }, { 28, 28, 1 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27354), { 0, 0, height - 5 },
                { { 2, 2, height - 5 }, { 28, 28, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27350), { 0, 0, height - 5 },
                { { 2, 2, height + 94 }, { 28, 28, 1 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27351), { 0, 0, height - 5 },
                { { 2, 2, height - 5 }, { 28, 28, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27347), { 0, 0, height - 5 },
                { { 2, 2, height + 94 }, { 28, 28, 1 } });
            break;
    }

    TrackPaintUtilLeftQuarterTurn1TileTunnel(
        session, kTunnelGroup, direction, height, -8, TunnelSubType::slopeStart, +56, TunnelSubType::slopeEnd);
    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 104);
}

/** rct2: 0x007C7394 */
static void InvertedFlyingRCTrackRightQuarterTurn160DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27343), { 0, 0, height - 5 },
                { { 2, 2, height - 5 }, { 28, 28, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27339), { 0, 0, height - 5 },
                { { 2, 2, height + 94 }, { 28, 28, 1 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27344), { 0, 0, height - 5 },
                { { 2, 2, height - 5 }, { 28, 28, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27340), { 0, 0, height - 5 },
                { { 2, 2, height + 94 }, { 28, 28, 1 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27345), { 0, 0, height - 5 },
                { { 2, 2, height - 5 }, { 28, 28, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27341), { 0, 0, height - 5 },
                { { 2, 2, height + 94 }, { 28, 28, 1 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27346), { 0, 0, height - 5 },
                { { 2, 2, height - 5 }, { 28, 28, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27342), { 0, 0, height - 5 },
                { { 2, 2, height + 94 }, { 28, 28, 1 } });
            break;
    }
    TrackPaintUtilRightQuarterTurn1TileTunnel(
        session, kTunnelGroup, direction, height, -8, TunnelSubType::slopeStart, +56, TunnelSubType::slopeEnd);
    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 104);
}

/** rct2: 0x007C73A4 */
static void InvertedFlyingRCTrackLeftQuarterTurn160DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightQuarterTurn160DegUp(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C73C4 */
static void InvertedFlyingRCTrackRightQuarterTurn160DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftQuarterTurn160DegUp(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C73D4 */
static void InvertedFlyingRCTrackBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27337), { 0, 0, height + 24 },
                { { 0, 6, height + 24 }, { 32, 20, 3 } });
            break;
        case 1:
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27338), { 0, 0, height + 24 },
                { { 0, 6, height + 24 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static void InvertedFlyingRCTrackBooster(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    const auto imageId = (direction & 1) ? SPR_TRACKS_BM_INVERT_BOOSTER_2 : SPR_TRACKS_BM_INVERT_BOOSTER_1;
    PaintAddImageAsParentRotated(
        session, direction, session.TrackColours.WithIndex(imageId), { 0, 0, height + 24 },
        { { 0, 6, height + 22 }, { 32, 20, 1 } });

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C7674 */
static void InvertedFlyingRCTrackLeftQuarterBankedHelixLargeUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27202), { 0, 0, height + 24 },
                        { { 0, 6, height + 30 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27207), { 0, 0, height + 24 },
                        { { 0, 6, height + 30 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27212), { 0, 0, height + 24 },
                        { { 0, 6, height + 30 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27197), { 0, 0, height + 24 },
                        { { 0, 6, height + 30 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 41, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::tall);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27201), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27206), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27211), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27196), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27200), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27205), { 0, 0, height + 24 },
                        { { 16, 16, height + 38 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27210), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27195), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27199), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27204), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27209), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27194), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27198), { 0, 0, height + 24 },
                        { { 6, 0, height + 38 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27203), { 0, 0, height + 24 },
                        { { 6, 0, height + 38 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27208), { 0, 0, height + 24 },
                        { { 6, 0, height + 38 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27193), { 0, 0, height + 24 },
                        { { 6, 0, height + 38 }, { 20, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 53, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 16, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 16, kTunnelGroup, TunnelSubType::tall);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C7684 */
static void InvertedFlyingRCTrackRightQuarterBankedHelixLargeUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27173), { 0, 0, height + 24 },
                        { { 0, 6, height + 30 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27178), { 0, 0, height + 24 },
                        { { 0, 6, height + 30 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27183), { 0, 0, height + 24 },
                        { { 0, 6, height + 30 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27188), { 0, 0, height + 24 },
                        { { 0, 6, height + 30 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 41, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::tall);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27174), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27179), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27184), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27189), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27175), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27180), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27185), { 0, 0, height + 24 },
                        { { 16, 16, height + 38 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27190), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27176), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27181), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27186), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27191), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27177), { 0, 0, height + 24 },
                        { { 6, 0, height + 38 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27182), { 0, 0, height + 24 },
                        { { 6, 0, height + 38 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27187), { 0, 0, height + 24 },
                        { { 6, 0, height + 38 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27192), { 0, 0, height + 24 },
                        { { 6, 0, height + 38 }, { 20, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 53, session.SupportColours);

            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 16, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 16, kTunnelGroup, TunnelSubType::tall);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C7694 */
static void InvertedFlyingRCTrackLeftQuarterBankedHelixLargeDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27182), { 0, 0, height + 24 },
                        { { 0, 6, height + 38 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27187), { 0, 0, height + 24 },
                        { { 0, 6, height + 38 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27192), { 0, 0, height + 24 },
                        { { 0, 6, height + 38 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27177), { 0, 0, height + 24 },
                        { { 0, 6, height + 38 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 53, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height + 16, kTunnelGroup, TunnelSubType::tall);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27181), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27186), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27191), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27176), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27180), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27185), { 0, 0, height + 24 },
                        { { 16, 16, height + 38 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27190), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27175), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27179), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27184), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27189), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27174), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27178), { 0, 0, height + 24 },
                        { { 6, 0, height + 30 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27183), { 0, 0, height + 24 },
                        { { 6, 0, height + 30 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27188), { 0, 0, height + 24 },
                        { { 6, 0, height + 30 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27173), { 0, 0, height + 24 },
                        { { 6, 0, height + 30 }, { 20, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 41, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::tall);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C76A4 */
static void InvertedFlyingRCTrackRightQuarterBankedHelixLargeDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27193), { 0, 0, height + 24 },
                        { { 0, 6, height + 38 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27198), { 0, 0, height + 24 },
                        { { 0, 6, height + 38 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27203), { 0, 0, height + 24 },
                        { { 0, 6, height + 38 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27208), { 0, 0, height + 24 },
                        { { 0, 6, height + 38 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 53, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height + 16, kTunnelGroup, TunnelSubType::tall);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27194), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27199), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27204), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27209), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27195), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27200), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27205), { 0, 0, height + 24 },
                        { { 16, 16, height + 38 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27210), { 0, 0, height + 24 },
                        { { 0, 16, height + 38 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27196), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27201), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27206), { 0, 0, height + 24 },
                        { { 0, 0, height + 38 }, { 16, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27211), { 0, 0, height + 24 },
                        { { 16, 0, height + 38 }, { 16, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27197), { 0, 0, height + 24 },
                        { { 6, 0, height + 30 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27202), { 0, 0, height + 24 },
                        { { 6, 0, height + 30 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27207), { 0, 0, height + 24 },
                        { { 6, 0, height + 30 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27212), { 0, 0, height + 24 },
                        { { 6, 0, height + 30 }, { 20, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 41, session.SupportColours);

            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::tall);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C78B4 */
static void InvertedFlyingRCTrack25DegUpLeftBanked(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27711), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27712), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27713), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27714), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 57, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

/** rct2: 0x007C78C4 */
static void InvertedFlyingRCTrack25DegUpRightBanked(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27715), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27716), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27717), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27718), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 57, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

/** rct2: 0x007C73E4 */
static void InvertedFlyingRCTrackOnRidePhoto(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    TrackPaintUtilOnridePhotoPlatformPaint(session, direction, height, supportType.metal);

    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27129), { 0, 0, height + 24 },
                { { 0, 6, height + 24 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27130), { 0, 0, height + 24 },
                { { 0, 6, height + 24 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27129), { 0, 0, height + 24 },
                { { 0, 6, height + 24 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27130), { 0, 0, height + 24 },
                { { 0, 6, height + 24 }, { 32, 20, 3 } });
            break;
    }
    TrackPaintUtilOnridePhotoPaint2(session, direction, trackElement, height, kGeneralSupportHeightOnRidePhotoInverted);
}

/** rct2: 0x007C78D4 */
static void InvertedFlyingRCTrack25DegDownLeftBanked(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUpRightBanked(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C78E4 */
static void InvertedFlyingRCTrack25DegDownRightBanked(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUpLeftBanked(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7404 */
static void InvertedFlyingRCTrackLeftEighthToDiag(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27507), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27511), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27515), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27519), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27508), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27512), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 34, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27516), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27520), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27509), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27513), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27517), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27521), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27510), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27514), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 18, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27518), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27522), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::bottomCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7414 */
static void InvertedFlyingRCTrackRightEighthToDiag(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27491), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27495), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27499), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27503), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27492), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27496), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27500), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 34, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27504), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27493), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27497), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27501), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27505), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27494), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27498), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27502), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 18, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27506), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7424 */
static void InvertedFlyingRCTrackLeftEighthToOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    InvertedFlyingRCTrackRightEighthToDiag(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7434 */
static void InvertedFlyingRCTrackRightEighthToOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    InvertedFlyingRCTrackLeftEighthToDiag(session, ride, trackSequence, (direction + 3) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7444 */
static void InvertedFlyingRCTrackLeftEighthBankToDiag(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27539), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27543), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27547), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27551), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27540), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27544), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 34, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27548), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27552), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27541), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27545), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27549), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27553), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27542), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27546), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 18, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27550), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27554), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::bottomCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7454 */
static void InvertedFlyingRCTrackRightEighthBankToDiag(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27523), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27527), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27531), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27535), { 0, 0, height + 24 },
                        { { 0, 6, height + 22 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27524), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27528), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27532), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 34, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27536), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 32, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27525), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27529), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27533), { 0, 0, height + 24 },
                        { { 4, 4, height + 22 }, { 28, 28, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27537), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27526), { 0, 0, height + 24 },
                        { { 16, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27530), { 0, 0, height + 24 },
                        { { 0, 0, height + 22 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27534), { 0, 0, height + 24 },
                        { { 0, 16, height + 22 }, { 16, 18, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27538), { 0, 0, height + 24 },
                        { { 16, 16, height + 22 }, { 16, 16, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7464 */
static void InvertedFlyingRCTrackLeftEighthBankToOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    InvertedFlyingRCTrackRightEighthBankToDiag(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7474 */
static void InvertedFlyingRCTrackRightEighthBankToOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    InvertedFlyingRCTrackLeftEighthBankToDiag(
        session, ride, trackSequence, (direction + 3) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C73F4 */
static void InvertedFlyingRCTrackDiagFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27614), { -16, -16, height + 24 },
                            { { -16, -16, height + 22 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27558), { -16, -16, height + 24 },
                            { { -16, -16, height + 22 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27611), { -16, -16, height + 24 },
                            { { -16, -16, height + 22 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27555), { -16, -16, height + 24 },
                            { { -16, -16, height + 22 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27613), { -16, -16, height + 24 },
                            { { -16, -16, height + 22 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27557), { -16, -16, height + 24 },
                            { { -16, -16, height + 22 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27612), { -16, -16, height + 24 },
                            { { -16, -16, height + 22 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27556), { -16, -16, height + 24 },
                            { { -16, -16, height + 22 }, { 32, 32, 3 } });
                        break;
                }
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C74A4 */
static void InvertedFlyingRCTrackDiag25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27626), { -16, -16, height + 24 },
                            { { -16, -16, height + 40 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27570), { -16, -16, height + 24 },
                            { { -16, -16, height + 40 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 1:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27623), { -16, -16, height + 24 },
                            { { -16, -16, height + 40 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27567), { -16, -16, height + 24 },
                            { { -16, -16, height + 40 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 2:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27625), { -16, -16, height + 24 },
                            { { -16, -16, height + 40 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27569), { -16, -16, height + 24 },
                            { { -16, -16, height + 40 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 3:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27624), { -16, -16, height + 24 },
                            { { -16, -16, height + 40 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27568), { -16, -16, height + 24 },
                            { { -16, -16, height + 40 }, { 32, 32, 3 } });
                        break;
                }
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 51, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

/** rct2: 0x007C7504 */
static void InvertedFlyingRCTrackDiag60DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27582), { -16, -16, height + 24 },
                        { { -16, -16, height + 88 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27579), { -16, -16, height + 24 },
                        { { -16, -16, height + 88 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27581), { -16, -16, height + 24 },
                        { { -16, -16, height + 88 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27580), { -16, -16, height + 24 },
                        { { -16, -16, height + 24 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::leftCorner, 32, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 1:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topCorner, 36, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 2:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::rightCorner, 32, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 3:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomCorner, 36, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
    }
}

/** rct2: 0x007C7484 */
static void InvertedFlyingRCTrackDiagFlatTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27618), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27562), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27615), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27559), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27617), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27561), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27616), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27560), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 43, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C74E4 */
static void InvertedFlyingRCTrackDiag25DegUpTo60DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27574), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27571), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27573), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27572), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::leftCorner, 16, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 1:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topCorner, 16, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 2:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::rightCorner, 16, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 3:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomCorner, 16, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x007C74F4 */
static void InvertedFlyingRCTrackDiag60DegUpTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27578), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27575), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27577), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27576), { -16, -16, height + 24 },
                        { { 0, 0, height + 56 }, { 16, 16, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::leftCorner, 21, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 1:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topCorner, 21, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 2:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::rightCorner, 21, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 3:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomCorner, 21, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x007C7494 */
static void InvertedFlyingRCTrackDiag25DegUpToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27622), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27566), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 1:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27619), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27563), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 2:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27621), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27565), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 3:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27620), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(27564), { -16, -16, height + 24 },
                            { { -16, -16, height + 32 }, { 32, 32, 3 } });
                        break;
                }
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 45, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

/** rct2: 0x007C74D4 */
static void InvertedFlyingRCTrackDiag25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27568), { -16, -16, height + 24 },
                        { { -16, -16, height + 40 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27569), { -16, -16, height + 24 },
                        { { -16, -16, height + 40 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27567), { -16, -16, height + 24 },
                        { { -16, -16, height + 40 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27570), { -16, -16, height + 24 },
                        { { -16, -16, height + 40 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 51, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

/** rct2: 0x007C7534 */
static void InvertedFlyingRCTrackDiag60DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27580), { -16, -16, height + 24 },
                        { { -16, -16, height + 24 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27581), { -16, -16, height + 24 },
                        { { -16, -16, height + 88 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27579), { -16, -16, height + 24 },
                        { { -16, -16, height + 88 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27582), { -16, -16, height + 24 },
                        { { -16, -16, height + 88 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::leftCorner, 24, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 1:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topCorner, 28, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 2:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::rightCorner, 24, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 3:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomCorner, 28, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
    }
}

/** rct2: 0x007C74B4 */
static void InvertedFlyingRCTrackDiagFlatTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27564), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27565), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27563), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27566), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 45, session.SupportColours);
            break;
    }

    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x007C7514 */
static void InvertedFlyingRCTrackDiag25DegDownTo60DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27576), { -16, -16, height + 24 },
                        { { 0, 0, height + 56 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27577), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27575), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27578), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::leftCorner, 17, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 1:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topCorner, 17, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 2:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::rightCorner, 17, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 3:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomCorner, 17, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x007C7524 */
static void InvertedFlyingRCTrackDiag60DegDownTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27572), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27573), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27571), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27574), { -16, -16, height + 24 },
                        { { -16, -16, height + 56 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::leftCorner, 8, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 1:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topCorner, 8, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 2:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::rightCorner, 8, height + kSupportHeight,
                        session.SupportColours);
                    break;
                case 3:
                    MetalBSupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomCorner, 8, height + kSupportHeight,
                        session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x007C74C4 */
static void InvertedFlyingRCTrackDiag25DegDownToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27560), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27561), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27559), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27562), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 43, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C7564 */
static void InvertedFlyingRCTrackDiagFlatToLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27590), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27587), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27589), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27588), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7574 */
static void InvertedFlyingRCTrackDiagFlatToRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27594), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27591), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27593), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27592), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7584 */
static void InvertedFlyingRCTrackDiagLeftBankToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27592), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27593), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27591), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27594), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7594 */
static void InvertedFlyingRCTrackDiagRightBankToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27588), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27589), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27587), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27590), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C75C4 */
static void InvertedFlyingRCTrackDiagLeftBankTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27606), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27603), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27605), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27604), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 43, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C75D4 */
static void InvertedFlyingRCTrackDiagRightBankTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27610), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27607), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27609), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27608), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 43, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C75A4 */
static void InvertedFlyingRCTrackDiag25DegUpToLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27598), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27595), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27597), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27596), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 45, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

/** rct2: 0x007C75B4 */
static void InvertedFlyingRCTrackDiag25DegUpToRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27602), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27599), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27601), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27600), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 45, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

/** rct2: 0x007C75E4 */
static void InvertedFlyingRCTrackDiagLeftBankTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27600), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27601), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27599), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27602), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 45, session.SupportColours);
            break;
    }

    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x007C75F4 */
static void InvertedFlyingRCTrackDiagRightBankTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27596), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27597), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27595), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27598), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 45, session.SupportColours);
            break;
    }

    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x007C7604 */
static void InvertedFlyingRCTrackDiag25DegDownToLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27608), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27609), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27607), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27610), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 43, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C7614 */
static void InvertedFlyingRCTrackDiag25DegDownToRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27604), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27605), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27603), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27606), { -16, -16, height + 24 },
                        { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + 43, session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x007C7544 */
static void InvertedFlyingRCTrackDiagLeftBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27586), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27583), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27585), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27584), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7554 */
static void InvertedFlyingRCTrackDiagRightBank(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27584), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27585), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27583), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27586), { -16, -16, height + 24 },
                        { { -16, -16, height + 22 }, { 32, 32, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
                session.SupportColours);

            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7664 */
static void InvertedFlyingRCTrackBlockBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27337), { 0, 0, height + 24 },
                { { 0, 6, height + 24 }, { 32, 20, 3 } });
            break;
        case 1:
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27338), { 0, 0, height + 24 },
                { { 0, 6, height + 24 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);
    }

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x007C76B4 */
static void InvertedFlyingRCTrackLeftBankedQuarterTurn325DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27762), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27764), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27766), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27760), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 47, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27761), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27763), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27765), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27759), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 47, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
    }
}

/** rct2: 0x007C76C4 */
static void InvertedFlyingRCTrackRightBankedQuarterTurn325DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27751), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27753), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27755), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27757), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 47, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27752), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27754), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27756), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27758), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 47, session.SupportColours);

            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
    }
}

/** rct2: 0x007C76D4 */
static void InvertedFlyingRCTrackLeftBankedQuarterTurn325DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    InvertedFlyingRCTrackRightBankedQuarterTurn325DegUp(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C76E4 */
static void InvertedFlyingRCTrackRightBankedQuarterTurn325DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    InvertedFlyingRCTrackLeftBankedQuarterTurn325DegUp(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C76F4 */
static void InvertedFlyingRCTrackLeftBankedQuarterTurn525DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27787), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27792), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27797), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27802), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 49, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27788), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27793), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27798), { 0, 16, height + 24 }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27803), { 0, 16, height + 24 }, { 32, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27789), { 0, 16, height + 24 }, { 16, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27794), { 16, 16, height + 24 }, { 16, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27799), { 16, 0, height + 24 }, { 16, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27804), { 0, 0, height + 24 }, { 16, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27790), { 16, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27795), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27800), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27805), { 16, 0, height + 24 }, { 16, 32, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27791), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27796), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27801), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27806), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 49, session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
    }
}

/** rct2: 0x007C7704 */
static void InvertedFlyingRCTrackRightBankedQuarterTurn525DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27767), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27772), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27777), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27782), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 49, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27768), { 0, 16, height + 24 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27773), { 0, 16, height + 24 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27778), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27783), { 0, 0, height + 24 }, { 32, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27769), { 0, 0, height + 24 }, { 16, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27774), { 16, 0, height + 24 }, { 16, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27779), { 16, 16, height + 24 }, { 16, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27784), { 0, 16, height + 24 }, { 16, 16, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
        case 4:
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 5:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27770), { 16, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27775), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27780), { 0, 0, height + 24 }, { 16, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27785), { 16, 0, height + 24 }, { 16, 32, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 6:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27771), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27776), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27781), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27786), { 6, 0, height + 24 }, { 20, 32, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 49, session.SupportColours);

            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
    }
}

/** rct2: 0x007C7714 */
static void InvertedFlyingRCTrackLeftBankedQuarterTurn525DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    InvertedFlyingRCTrackRightBankedQuarterTurn525DegUp(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7724 */
static void InvertedFlyingRCTrackRightBankedQuarterTurn525DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    InvertedFlyingRCTrackLeftBankedQuarterTurn525DegUp(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7734 */
static void InvertedFlyingRCTrack25DegUpToLeftBanked25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27719), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27720), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27721), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27722), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 57, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

/** rct2: 0x007C7744 */
static void InvertedFlyingRCTrack25DegUpToRightBanked25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27723), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27724), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27725), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27726), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 57, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

/** rct2: 0x007C7754 */
static void InvertedFlyingRCTrackLeftBanked25DegUpTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27727), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27728), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27729), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27730), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 57, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

/** rct2: 0x007C7764 */
static void InvertedFlyingRCTrackRightBanked25DegUpTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27731), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27732), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27733), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27734), { 0, 0, height + 24 },
                { { 0, 6, height + 40 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 57, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

/** rct2: 0x007C7774 */
static void InvertedFlyingRCTrack25DegDownToLeftBanked25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightBanked25DegUpTo25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7784 */
static void InvertedFlyingRCTrack25DegDownToRightBanked25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftBanked25DegUpTo25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7794 */
static void InvertedFlyingRCTrackLeftBanked25DegDownTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUpToRightBanked25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C77A4 */
static void InvertedFlyingRCTrackRightBanked25DegDownTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack25DegUpToLeftBanked25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C77B4 */
static void InvertedFlyingRCTrackLeftBankedFlatToLeftBanked25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27735), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27736), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27737), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27738), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 49, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 64);
}

/** rct2: 0x007C77C4 */
static void InvertedFlyingRCTrackRightBankedFlatToRightBanked25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27739), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27740), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27741), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27742), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 49, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 64);
}

/** rct2: 0x007C77F4 */
static void InvertedFlyingRCTrackLeftBanked25DegUpToLeftBankedFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27743), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27744), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27745), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27746), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::flatTo25Deg);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x007C7804 */
static void InvertedFlyingRCTrackRightBanked25DegUpToRightBankedFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27747), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27748), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27749), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27750), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::flatTo25Deg);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x007C7814 */
static void InvertedFlyingRCTrackLeftBankedFlatToLeftBanked25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightBanked25DegUpToRightBankedFlat(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7824 */
static void InvertedFlyingRCTrackRightBankedFlatToRightBanked25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftBanked25DegUpToLeftBankedFlat(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C77D4 */
static void InvertedFlyingRCTrackLeftBanked25DegDownToLeftBankedFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightBankedFlatToRightBanked25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C77E4 */
static void InvertedFlyingRCTrackRightBanked25DegDownToRightBankedFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftBankedFlatToLeftBanked25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7834 */
static void InvertedFlyingRCTrackFlatToLeftBanked25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27695), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27696), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27697), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27698), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 49, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 64);
}

/** rct2: 0x007C7844 */
static void InvertedFlyingRCTrackFlatToRightBanked25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27699), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27700), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27701), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27702), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 49, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 64);
}

/** rct2: 0x007C7854 */
static void InvertedFlyingRCTrackLeftBanked25DegUpToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27703), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27704), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27705), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27706), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::flatTo25Deg);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x007C7864 */
static void InvertedFlyingRCTrackRightBanked25DegUpToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27707), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27708), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27709), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(27710), { 0, 0, height + 24 },
                { { 0, 6, height + 32 }, { 32, 20, 3 } });
            break;
    }

    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::topRightSide, direction, 0, height + 47, session.SupportColours);
    }

    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::flatTo25Deg);
    }
    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x007C7874 */
static void InvertedFlyingRCTrackFlatToLeftBanked25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightBanked25DegUpToFlat(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7884 */
static void InvertedFlyingRCTrackFlatToRightBanked25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftBanked25DegUpToFlat(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C7894 */
static void InvertedFlyingRCTrackLeftBanked25DegDownToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackFlatToRightBanked25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x007C78A4 */
static void InvertedFlyingRCTrackRightBanked25DegDownToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackFlatToLeftBanked25DegUp(
        session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrack90DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    direction = (direction + 2) & 3;

    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17526), { 0, 0, height },
                        { { 4, 6, height + 8 }, { 2, 20, 31 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17527), { 0, 0, height },
                        { { 24, 6, height + 8 }, { 2, 20, 31 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17528), { 0, 0, height },
                        { { 24, 6, height + 8 }, { 2, 20, 31 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17529), { 0, 0, height },
                        { { 4, 6, height + 8 }, { 2, 20, 31 } });
                    break;
            }
            PaintUtilSetVerticalTunnel(session, height + 32);
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            break;
    }
}

static void InvertedFlyingRCTrack90DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrack90DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackDiagBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    TrackPaintUtilDiagTilesPaint(
        session, 1, height + 24, direction, trackSequence, kInvertedRCDiagBrakeImages, defaultDiagTileOffsets,
        defaultDiagBoundLengths, nullptr);

    PaintSegments blockedSegments = BlockedSegments::kDiagStraightFlat[trackSequence];
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(blockedSegments, direction), 0xFFFF, 0);

    if (trackSequence == 3)
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height + kSupportHeight,
            session.SupportColours);
    }
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static void InvertedFlyingRCTrackDiagBlockBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackDiagBrakes(session, ride, trackSequence, direction, height, trackElement, supportType);
}

/** rct2: 0x007C7644 */
static void InvertedFlyingRCTrackLeftFlyerTwistDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27427), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27433), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27432), { 0, 6, height + 24 },
                        { { 0, 6, height + 24 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27438), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27428), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27434), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27431), { 0, 6, height + 24 },
                        { { 0, 6, height + 24 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27437), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27429), { 0, 6, height - 5 },
                        { { 0, 6, height + 6 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27435), { 0, 6, height - 5 },
                        { { 0, 6, height + 6 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27430), { 0, 6, height - 5 },
                        { { 0, 6, height + 6 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27436), { 0, 6, height - 5 },
                        { { 0, 6, height + 6 }, { 32, 20, 3 } });
                    break;
            }
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height - 5, session.SupportColours);
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7654 */
static void InvertedFlyingRCTrackRightFlyerTwistDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27439), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27445), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27444), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27450), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27440), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27446), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27443), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27449), { 0, 6, height + 24 }, { 32, 20, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27441), { 0, 6, height - 5 },
                        { { 0, 6, height + 6 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27447), { 0, 6, height - 5 },
                        { { 0, 6, height + 6 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27442), { 0, 6, height - 5 },
                        { { 0, 6, height + 6 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27448), { 0, 6, height - 5 },
                        { { 0, 6, height + 6 }, { 32, 20, 3 } });
                    break;
            }
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height - 5, session.SupportColours);
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x007C7304 */
static void FlyingRCTrackFlyerHalfLoopDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17629), { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17637), { 0, 0, height + 32 }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17630), { 0, 16, height + 32 }, { 32, 12, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17638), { 0, 16, height + 32 }, { 32, 12, 3 });
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17628), { 16, 0, height }, { 2, 16, 119 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17636), { 12, 0, height },
                        { { 12, 0, height }, { 3, 16, 119 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17631), { 10, 16, height }, { 4, 12, 119 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17639), { 16, 16, height },
                        { { 15, 6, height }, { 2, 16, 119 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 168);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17627), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 20, height, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17635), { 0, 14, height },
                        { { 28, 6, height }, { 3, 20, 63 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 15, height, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17632), { 0, 6, height },
                        { { 28, 6, height }, { 3, 20, 63 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 16, height, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17640), { 0, 6, height }, { 32, 20, 3 });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 16, height, session.SupportColours);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17626), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17634), { 0, 6, height }, { 32, 20, 11 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17633), { 0, 6, height }, { 32, 20, 9 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(17641), { 0, 6, height }, { 32, 20, 7 });
                    break;
            }
            MetalASupportsPaintSetup(session, supportType.metal, MetalSupportPlace::centre, 8, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

// inversions
static void InvertedFlyingRCTrackLeftEighthDiveLoopUpToOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::left, PaintSegment::centre,
                      PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 4)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, 0, height + 103 }, { 16, 30, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 12)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, 0, height + 88 }, { 10, 10, 1 } });
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 112);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 0)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { -16, -16, height + 93 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::topRight, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 136);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::topRight, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomCorner, 0, height + 92, session.SupportColours);
                    break;
                case 1:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + 109, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 8)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 1, 30, height + 0 }, { 1, 32, 32 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topCorner, 0, height + 92, session.SupportColours);
                    break;
                case 3:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::rightCorner, 0, height + 92, session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 144);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 1)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, -1, height + 33 }, { 32, 1, 64 } });

                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 5)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { -8, -8, height + kInvertedSpriteOffset }, { 3, 3, 15 } });

                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 9)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 4, 4, height + 100 }, { 28, 28, 1 } });

                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 13)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 20, 2, height + 100 }, { 28, 28, 1 } });

                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::topRight, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottom,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 136);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 2)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, 1, height + 0 }, { 1, 32, 64 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 6)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, 1, height + 0 }, { 32, 1, 64 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 10)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 30, 30, height + 0 }, { 8, 8, 64 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 14)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 0, 20, height + kInvertedSpriteOffset + 26 }, { 32, 1, 10 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topRight, PaintSegment::centre, PaintSegment::right, PaintSegment::bottomLeft,
                      PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 5:

            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 3)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + 36, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 7)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 11 }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + 36, session.SupportColours);
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 11)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 11 }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + 36, session.SupportColours);
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 15)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + 33, session.SupportColours);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
    }
}

static void InvertedFlyingRCTrackRightEighthDiveLoopUpToOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 20)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, 0, height + 103 }, { 16, 30, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 28)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, 0, height + 88 }, { 10, 10, 1 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::left, PaintSegment::centre,
                      PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 112);
            break;
        case 1:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 24)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { -16, -16, height + 93 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::left, PaintSegment::centre,
                      PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 136);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::topRight, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 16)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 1, 30, height + 0 }, { 1, 32, 32 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topCorner, 0, height + 92, session.SupportColours);
                    break;
                case 1:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::rightCorner, 0, height + 109, session.SupportColours);
                    break;
                case 2:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomCorner, 0, height + 92, session.SupportColours);
                    break;
                case 3:
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::leftCorner, 0, height + 92, session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 144);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 17)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 4, 4, height + 100 }, { 28, 28, 1 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 21)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { -8, -8, height + kInvertedSpriteOffset }, { 3, 3, 15 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 25)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, -1, height + 33 }, { 1, 32, 64 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 29)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 2, 2, height + 100 }, { 28, 28, 1 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::topRight, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottom,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 136);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 18)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 30, 30, height + 0 }, { 8, 8, 64 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 22)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 0, 1, height + 0 }, { 32, 1, 64 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 26)),
                        { -16, -16, height + kInvertedSpriteOffset }, { { 1, 0, height + 0 }, { 32, 1, 64 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 30)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 20, 0, height + kInvertedSpriteOffset + 26 }, { 1, 32, 10 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topRight, PaintSegment::centre, PaintSegment::right, PaintSegment::bottomLeft,
                      PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 5:

            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 19)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 6, 0, height + kInvertedSpriteOffset + 11 }, { 20, 32, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + 36, session.SupportColours);
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 23)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 6, 0, height + kInvertedSpriteOffset + 11 }, { 20, 32, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + 36, session.SupportColours);
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 27)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 6, 0, height + kInvertedSpriteOffset }, { 20, 32, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + 35, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_DIVE_LOOP + 31)),
                        { -16, -16, height + kInvertedSpriteOffset },
                        { { 6, 0, height + kInvertedSpriteOffset }, { 20, 32, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + 35, session.SupportColours);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
    }
}

static void InvertedFlyingRCTrackLeftEighthDiveLoopDownToDiag(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightEighthDiveLoopUpToOrthogonal(
        session, ride, 5 - trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackRightEighthDiveLoopToDownOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftEighthDiveLoopUpToOrthogonal(
        session, ride, 5 - trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackLeftMediumHalfLoopUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 0),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 5),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 10),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 15),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 3 } });
                    break;
            }

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 1),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 80 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 6),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 80 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 11),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 80 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 16),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 80 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::top },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kInvertedSpriteOffset + 88);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 2),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 28, 0, height + kInvertedSpriteOffset + 50 }, { 1, 26, 50 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 7),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, -16, height + 8 }, { 32, 1, 140 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 12),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 8 }, { 32, 1, 140 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 17),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 28, 0, height + kInvertedSpriteOffset + 50 }, { 1, 26, 50 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::centre, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 168);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 3),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 28, 6, height + 120 }, { 1, 20, 30 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 8),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 8 }, { 32, 1, 140 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 13),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 0, height + 8 }, { 32, 1, 140 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 18),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 25, height + 8 }, { 32, 1, 140 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::bottomRight, PaintSegment::centre, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 168);
            break;
        case 4:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottom, PaintSegment::bottomRight,
                      PaintSegment::right },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 4),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 1 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 9),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 1 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 14),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 19),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 1 } });
                    break;
            }
            MetalASupportsPaintSetup(session, supportType.metal, MetalSupportPlace::centre, 48, height, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height + 48, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void InvertedFlyingRCTrackRightMediumHalfLoopUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 20),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 25),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 30),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 35),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 3 } });
                    break;
            }

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 21),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 80 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 26),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 80 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 31),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 80 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 36),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 80 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topRight, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottom,
                      PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 22),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 28, 0, height + kInvertedSpriteOffset + 50 }, { 1, 26, 50 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 27),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 8 }, { 32, 1, 140 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 32),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, -16, height + 8 }, { 32, 1, 140 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 37),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 28, 0, height + kInvertedSpriteOffset + 50 }, { 1, 26, 50 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::bottomRight, PaintSegment::centre, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 160);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 23),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 25, height + 8 }, { 32, 1, 140 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 28),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 0, height + 8 }, { 32, 1, 140 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 33),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 8 }, { 32, 1, 140 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 38),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 28, 6, height + 120 }, { 1, 20, 30 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 160);
            break;
        case 4:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::bottomLeft,
                      PaintSegment::top },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 24),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 1 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 29),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 1 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 34),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_BM_INVERT_MEDIUM_HALF_LOOP + 39),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 48 }, { 32, 20, 1 } });
                    break;
            }
            MetalASupportsPaintSetup(session, supportType.metal, MetalSupportPlace::centre, 48, height, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height + 48, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void InvertedFlyingRCTrackLeftMediumHalfLoopDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightMediumHalfLoopUp(session, ride, 4 - trackSequence, direction, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackRightMediumHalfLoopDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftMediumHalfLoopUp(session, ride, 4 - trackSequence, direction, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackLeftZeroGRollUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 0)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 1)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 1 } });

                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 0, height + kInvertedSpriteOffset + 30,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 4)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 5)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 31, height + kInvertedSpriteOffset }, { 40, 1, 32 } });

                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 0, height + kInvertedSpriteOffset + 30,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 8)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 8 }, { 32, 20, 3 } });

                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + kInvertedSpriteOffset + 30,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 12)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 8 }, { 32, 20, 3 } });

                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 0, height + kInvertedSpriteOffset + 30,
                        session.SupportColours);
                    break;
            }

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }

            PaintUtilSetGeneralSupportHeight(session, height + 78);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 2)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 1 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 6)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 40, 20, 1 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 9)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 26, height + kInvertedSpriteOffset }, { 32, 1, 32 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 13)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 26, height + kInvertedSpriteOffset }, { 32, 1, 32 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottomRight, PaintSegment::bottomLeft, PaintSegment::bottom,
                      PaintSegment::centre, PaintSegment::topRight },
                    direction),

                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:

            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 3)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 3 }, { 40, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 7)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 3 }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 10)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 11)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 7 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 14)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 15)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 7 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);
                    break;
            }
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);

            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
    }
}

static void InvertedFlyingRCTrackRightZeroGRollUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::topRight, PaintSegment::centre, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 16)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 0, height + kInvertedSpriteOffset + 29,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 20)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 0, height + kInvertedSpriteOffset + 30,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 24)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 25)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 31, height + kInvertedSpriteOffset }, { 40, 1, 32 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + kInvertedSpriteOffset + 30,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 28)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 29)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 3 }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 0, height + kInvertedSpriteOffset + 30,
                        session.SupportColours);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 86);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 17)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 26, height + kInvertedSpriteOffset }, { 32, 1, 32 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 21)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 26)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 40, 20, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 30)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 1 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::topLeft, PaintSegment::left, PaintSegment::bottomLeft,
                      PaintSegment::centre, PaintSegment::topRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 18)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 19)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 7 }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);

                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 22)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 23)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 7 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);

                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 27)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 3 }, { 32, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 1,
                        session.SupportColours);

                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_ZERO_G_ROLL + 31)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 3 }, { 40, 20, 1 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);

                    break;
            }
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
    }
}

static void InvertedFlyingRCTrackLeftZeroGRollDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftZeroGRollUp(
        session, ride, 2 - trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackRightZeroGRollDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightZeroGRollUp(
        session, ride, 2 - trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackLeftLargeZeroGRollUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topRight, PaintSegment::right, PaintSegment::bottomRight, PaintSegment::centre,
                      PaintSegment::bottom },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 0)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 93 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 0, height + 83, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 5)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height + kInvertedSpriteOffset }, { 24, 1, 50 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 0, height + 106,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 9)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 4, height + kInvertedSpriteOffset + 11 }, { 32, 1, 50 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 10)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 26, height + kInvertedSpriteOffset + 11 }, { 32, 1, 50 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + 104, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 15)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 93 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 0, height + 100, session.SupportColours);
                    break;
            }

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }

            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 1:

            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 1)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height + 11 }, { 26, 2, 81 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 2)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height + 93 }, { 26, 20, 1 } });

                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 6)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height + 11 }, { 32, 2, 81 } });

                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 11)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 26, height + 11 }, { 32, 2, 92 } });

                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 16)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 26, height + 11 }, { 32, 2, 81 } });

                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottomRight, PaintSegment::bottomLeft, PaintSegment::bottom,
                      PaintSegment::centre, PaintSegment::topRight },
                    direction),

                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 96);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 3)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height }, { 32, 1, 64 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 7)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height }, { 32, 1, 48 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 12)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 26, height }, { 30, 1, 64 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 17)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 30, height }, { 30, 1, 64 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 18)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 26, height }, { 30, 1, 64 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottomRight, PaintSegment::bottomLeft, PaintSegment::bottom,
                      PaintSegment::centre, PaintSegment::topRight },
                    direction),

                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 3:

            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 4)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 6, height + 21, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 8)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 6, height + 21, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 13)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 14)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 6, height + 21, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 19)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 6, height + 21, session.SupportColours);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
    }
}

static void InvertedFlyingRCTrackRightLargeZeroGRollUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topRight, PaintSegment::top, PaintSegment::topLeft, PaintSegment::centre,
                      PaintSegment::left },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 20)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 93 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 0, height + 100, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 25)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 4, height + kInvertedSpriteOffset + 11 }, { 24, 1, 50 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 26)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 26, height + kInvertedSpriteOffset + 11 }, { 24, 1, 50 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 0, height + 104,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 31)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height + kInvertedSpriteOffset }, { 24, 1, 50 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + 106, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 35)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 93 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 0, height + 83, session.SupportColours);
                    break;
            }

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }

            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 21)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 26, height + 11 }, { 32, 1, 81 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 27)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 26, height + 11 }, { 32, 1, 92 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 32)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height + 11 }, { 32, 1, 81 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 36)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height + 11 }, { 26, 1, 81 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 37)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height + 93 }, { 26, 20, 1 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::topRight }, // FIXED: Mirrored perfectly from Left across TR-C-BL
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 96);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 22)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 1, 26, height }, { 30, 1, 64 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 23)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 1, 26, height }, { 30, 1, 64 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 28)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 1, 26, height }, { 30, 1, 64 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 33)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height }, { 32, 1, 48 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 38)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 4, height }, { 32, 1, 64 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::topRight }, // FIXED: Mirrored perfectly from Left across TR-C-BL
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 3:

            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 24)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 6, height + 21, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 29)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 30)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 6, height + 21, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 34)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 6, height + 21, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_ZERO_G_ROLL + 39)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 4, 16, height + 31 }, { 28, 14, 2 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 6, height + 21, session.SupportColours);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
    }
}

static void InvertedFlyingRCTrackLeftLargeZeroGRollDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftLargeZeroGRollUp(
        session, ride, 3 - trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackRightLargeZeroGRollDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightLargeZeroGRollUp(
        session, ride, 3 - trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackLeftBarrelRollUpToDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::bottomRight, PaintSegment::topRight, PaintSegment::centre },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 0)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 1)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 14,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 6)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 7)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 17,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 12)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 13)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 14,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 18)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 19)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 14,
                        session.SupportColours);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }

            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 2)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 3)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 28 }, { 32, 20, 0 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 8)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 9)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 28 }, { 32, 20, 0 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 14)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 15)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 20)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 21)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 4)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 5)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 2,
                        session.SupportColours);

                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 10)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 11)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 2,
                        session.SupportColours);

                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 16)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 17)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + +kInvertedSpriteOffset + 2 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);

                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 22)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 23)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + +kInvertedSpriteOffset + 2 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);

                    break;
            }
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height + 32, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height + 32, kTunnelGroup, TunnelSubType::tall);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);

            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void InvertedFlyingRCTrackRightBarrelRollUpToDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::centre },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 24)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 25)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 14,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 30)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 31)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 14,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 36)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 37)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 17,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 42)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 43)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 28 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 14,
                        session.SupportColours);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }

            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 26)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 27)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 28 }, { 32, 20, 0 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 32)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 33)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 28 }, { 32, 20, 0 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 38)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 39)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 44)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 45)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + kInvertedSpriteOffset }, { 32, 20, 0 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 28)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 29)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 34)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 35)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 3,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 40)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 41)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 2,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 46)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_BARREL_ROLL + 47)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 0, 6, height + kInvertedSpriteOffset + 2 }, { 32, 20, 0 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height + kInvertedSpriteOffset + 2,
                        session.SupportColours);
                    break;
            }
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height + 32, kTunnelGroup, TunnelSubType::tall);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height + 32, kTunnelGroup, TunnelSubType::tall);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void InvertedFlyingRCTrackLeftBarrelRollDownToUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftBarrelRollUpToDown(
        session, ride, 2 - trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackRightBarrelRollDownToUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightBarrelRollUpToDown(
        session, ride, 2 - trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackLeftLargeCorkscrewUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 0)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 32 }, { 32, 20, 3 } });

                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 6)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 32 }, { 32, 20, 3 } });

                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 12)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 32 }, { 32, 20, 3 } });

                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 18)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 32 }, { 32, 20, 3 } });

                    break;
            }

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }

            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 1:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::centre, PaintSegment::bottomRight, PaintSegment::right, PaintSegment::bottom,
                      PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 1)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 40 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + 52, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 7)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height }, { 32, 1, 40 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 8)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 40 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 0, height + 50, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 13)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 40 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 0, height + 52, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 19)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 40 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 0, height + 54, session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 2)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 16, 0, height + 16 }, { 16, 16, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 3)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 16, 0, height + 48 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 9)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 0, height + 16 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 14)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 16, height + 16 }, { 16, 16, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 15)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 16, height + 48 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 20)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 16, 16, height + 48 }, { 16, 16, 3 } });

                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::topRight, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 4:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::topRight, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottom,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 4)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + kInvertedSpriteOffset }, { 20, 32, 3 } });

                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 10)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + kInvertedSpriteOffset }, { 20, 32, 3 } });

                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 16)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + kInvertedSpriteOffset }, { 20, 32, 3 } });

                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 21)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 6, 0, height + kInvertedSpriteOffset + 24 }, { 20, 32, 3 } });

                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 5:

            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 5)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + 40 }, { 20, 32, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 6, height + 34, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 11)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + 40 }, { 20, 32, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 6, height + 34, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 17)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + 40 }, { 20, 32, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 6, height + 34, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 22)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + 40 }, { 20, 32, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 6, height + 34, session.SupportColours);
                    break;
            }

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, 3 - direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void InvertedFlyingRCTrackRightLargeCorkscrewUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 23)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 32 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 28)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 32 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 34)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 32 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 40)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 32 }, { 32, 20, 3 } });
                    break;
            }

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }

            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 1:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::topLeft,
                      PaintSegment::top },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 24)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 40 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomLeftSide, 0, height + 54, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 29)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 40 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topLeftSide, 0, height + 52, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 35)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height }, { 32, 1, 40 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 36)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 40 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::topRightSide, 0, height + 50, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 41)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 6, height + 40 }, { 32, 20, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::bottomRightSide, 0, height + 52, session.SupportColours);
                    break;
            }

            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 25)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 16, 16, height + 48 }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 30)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 16, height + 16 }, { 16, 16, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 31)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 16, height + 48 }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 37)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 0, 0, height + 16 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 42)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 16, 0, height + 16 }, { 16, 16, 3 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 43)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 16, 0, height + 48 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::topRight, PaintSegment::left, PaintSegment::centre,
                      PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 4:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::topRight, PaintSegment::left,
                      PaintSegment::centre, PaintSegment::right, PaintSegment::bottomLeft, PaintSegment::bottom,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 26)),
                        { 0, 0, height + kInvertedSpriteOffset },
                        { { 6, 0, height + kInvertedSpriteOffset + 24 }, { 20, 32, 3 } });

                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 32)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + kInvertedSpriteOffset }, { 20, 32, 3 } });

                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 38)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + kInvertedSpriteOffset }, { 20, 32, 3 } });

                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 44)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + kInvertedSpriteOffset }, { 20, 32, 3 } });

                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 5:

            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 27)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + 40 }, { 20, 32, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 6, height + 34, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 33)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + 40 }, { 20, 32, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 6, height + 34, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 39)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + 40 }, { 20, 32, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 6, height + 34, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_BM_INVERT_LARGE_CORKSCREW + 45)),
                        { 0, 0, height + kInvertedSpriteOffset }, { { 6, 0, height + 40 }, { 20, 32, 3 } });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 6, height + 34, session.SupportColours);
                    break;
            }

            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, 3 - direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void InvertedFlyingRCTrackLeftLargeCorkscrewDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightLargeCorkscrewUp(
        session, ride, 5 - trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

static void InvertedFlyingRCTrackRightLargeCorkscrewDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftLargeCorkscrewUp(
        session, ride, 5 - trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A9668 */
static void InvertedFlyingRCTrackLeftCorkscrewUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27467), { 0, 0, height + 29 },
                        { { 0, 6, height + 33 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27470), { 0, 0, height + 29 },
                        { { 0, 6, height + 33 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27473), { 0, 0, height + 29 },
                        { { 0, 6, height + 33 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27476), { 0, 0, height + 29 },
                        { { 0, 6, height + 33 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::right, PaintSegment::bottom, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 50, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27468), { 0, 0, height + 14 },
                        { { 6, 6, height + 24 }, { 20, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27471), { 0, 0, height + 14 },
                        { { 6, 6, height + 24 }, { 20, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27474), { 0, 0, height + 14 },
                        { { 6, 6, height + 24 }, { 20, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27477), { 0, 0, height + 14 },
                        { { 6, 6, height + 24 }, { 20, 20, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27469), { 0, 0, height + 29 },
                        { { 6, 0, height + 39 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27472), { 0, 0, height + 29 },
                        { { 6, 0, height + 39 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27475), { 0, 0, height + 29 },
                        { { 6, 0, height + 39 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27478), { 0, 0, height + 29 },
                        { { 6, 0, height + 39 }, { 20, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 28, session.SupportColours);
            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
    }
}

/** rct2: 0x008A9678 */
static void InvertedFlyingRCTrackRightCorkscrewUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27479), { 0, 0, height + 29 },
                        { { 0, 6, height + 33 }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27482), { 0, 0, height + 29 },
                        { { 0, 6, height + 33 }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27485), { 0, 0, height + 29 },
                        { { 0, 6, height + 33 }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27488), { 0, 0, height + 29 },
                        { { 0, 6, height + 33 }, { 32, 20, 3 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 50, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27480), { 0, 0, height + 14 },
                        { { 6, 6, height + 24 }, { 20, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27483), { 0, 0, height + 14 },
                        { { 6, 6, height + 24 }, { 20, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27486), { 0, 0, height + 14 },
                        { { 6, 6, height + 24 }, { 20, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27489), { 0, 0, height + 14 },
                        { { 6, 6, height + 24 }, { 20, 20, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 88);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27481), { 0, 0, height + 29 },
                        { { 6, 0, height + 39 }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27484), { 0, 0, height + 29 },
                        { { 6, 0, height + 39 }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27487), { 0, 0, height + 29 },
                        { { 6, 0, height + 39 }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27490), { 0, 0, height + 29 },
                        { { 6, 0, height + 39 }, { 20, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + 28, session.SupportColours);
            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 40, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
    }
}

/** rct2: 0x008A9688 */
static void InvertedFlyingRCTrackLeftCorkscrewDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackRightCorkscrewUp(
        session, ride, 2 - trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A9698 */
static void InvertedFlyingRCTrackRightCorkscrewDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    InvertedFlyingRCTrackLeftCorkscrewUp(
        session, ride, 2 - trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A9608 */
static void InvertedFlyingRCTrackLeftTwistDownToUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27427), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27433), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27432), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27438), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27428), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27434), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27431), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27437), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27429), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27435), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27430), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27436), { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            MetalASupportsPaintSetup(session, supportType.metal, MetalSupportPlace::centre, 0, height, session.SupportColours);
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x008A9618 */
static void InvertedFlyingRCTrackRightTwistDownToUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27439), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27445), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27444), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27450), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27440), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27446), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27443), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27449), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27441), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27447), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27442), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27448), { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            MetalASupportsPaintSetup(session, supportType.metal, MetalSupportPlace::centre, 0, height, session.SupportColours);
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x008A9628 */
static void InvertedFlyingRCTrackLeftTwistUpToDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27430), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27436), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27429), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27435), { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            MetalASupportsPaintSetup(session, supportType.metal, MetalSupportPlace::centre, 0, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27431), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27437), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27428), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27434), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27432), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27438), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27427), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27433), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x008A9638 */
static void InvertedFlyingRCTrackRightTwistUpToDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27442), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27448), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27441), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27447), { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            MetalASupportsPaintSetup(session, supportType.metal, MetalSupportPlace::centre, 0, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27443), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27449), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27440), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27446), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27444), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27450), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27439), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(27445), { 0, 6, height + 29 }, { 32, 20, 3 });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::centre, 0, height + kSupportHeight, session.SupportColours);

            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

TrackPaintFunction GetTrackPaintFunctionFlyingRCInverted(TrackElemType trackType)
{
    switch (trackType)
    {
        case TrackElemType::flat:
            return InvertedFlyingRCTrackFlat;
        case TrackElemType::endStation:
        case TrackElemType::beginStation:
        case TrackElemType::middleStation:
            return InvertedFlyingRCTrackStation;
        case TrackElemType::up25:
            return InvertedFlyingRCTrack25DegUp;
        case TrackElemType::up60:
            return InvertedFlyingRCTrack60DegUp;
        case TrackElemType::flatToUp25:
            return InvertedFlyingRCTrackFlatTo25DegUp;
        case TrackElemType::up25ToUp60:
            return InvertedFlyingRCTrack25DegUpTo60DegUp;
        case TrackElemType::up60ToUp25:
            return InvertedFlyingRCTrack60DegUpTo25DegUp;
        case TrackElemType::up25ToFlat:
            return InvertedFlyingRCTrack25DegUpToFlat;
        case TrackElemType::down25:
            return InvertedFlyingRCTrack25DegDown;
        case TrackElemType::down60:
            return InvertedFlyingRCTrack60DegDown;
        case TrackElemType::flatToDown25:
            return InvertedFlyingRCTrackFlatTo25DegDown;
        case TrackElemType::down25ToDown60:
            return InvertedFlyingRCTrack25DegDownTo60DegDown;
        case TrackElemType::down60ToDown25:
            return InvertedFlyingRCTrack60DegDownTo25DegDown;
        case TrackElemType::down25ToFlat:
            return InvertedFlyingRCTrack25DegDownToFlat;
        case TrackElemType::leftQuarterTurn5Tiles:
            return InvertedFlyingRCTrackLeftQuarterTurn5;
        case TrackElemType::rightQuarterTurn5Tiles:
            return InvertedFlyingRCTrackRightQuarterTurn5;
        case TrackElemType::flatToLeftBank:
            return InvertedFlyingRCTrackFlatToLeftBank;
        case TrackElemType::flatToRightBank:
            return InvertedFlyingRCTrackFlatToRightBank;
        case TrackElemType::leftBankToFlat:
            return InvertedFlyingRCTrackLeftBankToFlat;
        case TrackElemType::rightBankToFlat:
            return InvertedFlyingRCTrackRightBankToFlat;
        case TrackElemType::bankedLeftQuarterTurn5Tiles:
            return InvertedFlyingRCTrackBankedLeftQuarterTurn5;
        case TrackElemType::bankedRightQuarterTurn5Tiles:
            return InvertedFlyingRCTrackBankedRightQuarterTurn5;
        case TrackElemType::leftBankToUp25:
            return InvertedFlyingRCTrackLeftBankTo25DegUp;
        case TrackElemType::rightBankToUp25:
            return InvertedFlyingRCTrackRightBankTo25DegUp;
        case TrackElemType::up25ToLeftBank:
            return InvertedFlyingRCTrack25DegUpToLeftBank;
        case TrackElemType::up25ToRightBank:
            return InvertedFlyingRCTrack25DegUpToRightBank;
        case TrackElemType::leftBankToDown25:
            return InvertedFlyingRCTrackLeftBankTo25DegDown;
        case TrackElemType::rightBankToDown25:
            return InvertedFlyingRCTrackRightBankTo25DegDown;
        case TrackElemType::down25ToLeftBank:
            return InvertedFlyingRCTrack25DegDownToLeftBank;
        case TrackElemType::down25ToRightBank:
            return InvertedFlyingRCTrack25DegDownToRightBank;
        case TrackElemType::leftBank:
            return InvertedFlyingRCTrackLeftBank;
        case TrackElemType::rightBank:
            return InvertedFlyingRCTrackRightBank;
        case TrackElemType::leftQuarterTurn5TilesUp25:
            return InvertedFlyingRCTrackLeftQuarterTurn525DegUp;
        case TrackElemType::rightQuarterTurn5TilesUp25:
            return InvertedFlyingRCTrackRightQuarterTurn525DegUp;
        case TrackElemType::leftQuarterTurn5TilesDown25:
            return InvertedFlyingRCTrackLeftQuarterTurn525DegDown;
        case TrackElemType::rightQuarterTurn5TilesDown25:
            return InvertedFlyingRCTrackRightQuarterTurn525DegDown;
        case TrackElemType::sBendLeft:
            return InvertedFlyingRCTrackSBendLeft;
        case TrackElemType::sBendRight:
            return InvertedFlyingRCTrackSBendRight;
        case TrackElemType::leftQuarterTurn3Tiles:
            return InvertedFlyingRCTrackLeftQuarterTurn3;
        case TrackElemType::rightQuarterTurn3Tiles:
            return InvertedFlyingRCTrackRightQuarterTurn3;
        case TrackElemType::leftBankedQuarterTurn3Tiles:
            return InvertedFlyingRCTrackLeftQuarterTurn3Bank;
        case TrackElemType::rightBankedQuarterTurn3Tiles:
            return InvertedFlyingRCTrackRightQuarterTurn3Bank;
        case TrackElemType::leftQuarterTurn3TilesUp25:
            return InvertedFlyingRCTrackLeftQuarterTurn325DegUp;
        case TrackElemType::rightQuarterTurn3TilesUp25:
            return InvertedFlyingRCTrackRightQuarterTurn325DegUp;
        case TrackElemType::leftQuarterTurn3TilesDown25:
            return InvertedFlyingRCTrackLeftQuarterTurn325DegDown;
        case TrackElemType::rightQuarterTurn3TilesDown25:
            return InvertedFlyingRCTrackRightQuarterTurn325DegDown;
        case TrackElemType::leftQuarterTurn1TileUp60:
            return InvertedFlyingRCTrackLeftQuarterTurn160DegUp;
        case TrackElemType::rightQuarterTurn1TileUp60:
            return InvertedFlyingRCTrackRightQuarterTurn160DegUp;
        case TrackElemType::leftQuarterTurn1TileDown60:
            return InvertedFlyingRCTrackLeftQuarterTurn160DegDown;
        case TrackElemType::rightQuarterTurn1TileDown60:
            return InvertedFlyingRCTrackRightQuarterTurn160DegDown;
        case TrackElemType::brakes:
            return InvertedFlyingRCTrackBrakes;
        case TrackElemType::leftQuarterBankedHelixLargeUp:
            return InvertedFlyingRCTrackLeftQuarterBankedHelixLargeUp;
        case TrackElemType::rightQuarterBankedHelixLargeUp:
            return InvertedFlyingRCTrackRightQuarterBankedHelixLargeUp;
        case TrackElemType::leftQuarterBankedHelixLargeDown:
            return InvertedFlyingRCTrackLeftQuarterBankedHelixLargeDown;
        case TrackElemType::rightQuarterBankedHelixLargeDown:
            return InvertedFlyingRCTrackRightQuarterBankedHelixLargeDown;
        case TrackElemType::up25LeftBanked:
            return InvertedFlyingRCTrack25DegUpLeftBanked;
        case TrackElemType::up25RightBanked:
            return InvertedFlyingRCTrack25DegUpRightBanked;
        case TrackElemType::onRidePhoto:
            return InvertedFlyingRCTrackOnRidePhoto;
        case TrackElemType::down25LeftBanked:
            return InvertedFlyingRCTrack25DegDownLeftBanked;
        case TrackElemType::down25RightBanked:
            return InvertedFlyingRCTrack25DegDownRightBanked;
        case TrackElemType::leftEighthToDiag:
            return InvertedFlyingRCTrackLeftEighthToDiag;
        case TrackElemType::rightEighthToDiag:
            return InvertedFlyingRCTrackRightEighthToDiag;
        case TrackElemType::leftEighthToOrthogonal:
            return InvertedFlyingRCTrackLeftEighthToOrthogonal;
        case TrackElemType::rightEighthToOrthogonal:
            return InvertedFlyingRCTrackRightEighthToOrthogonal;
        case TrackElemType::leftEighthBankToDiag:
            return InvertedFlyingRCTrackLeftEighthBankToDiag;
        case TrackElemType::rightEighthBankToDiag:
            return InvertedFlyingRCTrackRightEighthBankToDiag;
        case TrackElemType::leftEighthBankToOrthogonal:
            return InvertedFlyingRCTrackLeftEighthBankToOrthogonal;
        case TrackElemType::rightEighthBankToOrthogonal:
            return InvertedFlyingRCTrackRightEighthBankToOrthogonal;
        case TrackElemType::diagFlat:
            return InvertedFlyingRCTrackDiagFlat;
        case TrackElemType::diagUp25:
            return InvertedFlyingRCTrackDiag25DegUp;
        case TrackElemType::diagUp60:
            return InvertedFlyingRCTrackDiag60DegUp;
        case TrackElemType::diagFlatToUp25:
            return InvertedFlyingRCTrackDiagFlatTo25DegUp;
        case TrackElemType::diagUp25ToUp60:
            return InvertedFlyingRCTrackDiag25DegUpTo60DegUp;
        case TrackElemType::diagUp60ToUp25:
            return InvertedFlyingRCTrackDiag60DegUpTo25DegUp;
        case TrackElemType::diagUp25ToFlat:
            return InvertedFlyingRCTrackDiag25DegUpToFlat;
        case TrackElemType::diagDown25:
            return InvertedFlyingRCTrackDiag25DegDown;
        case TrackElemType::diagDown60:
            return InvertedFlyingRCTrackDiag60DegDown;
        case TrackElemType::diagFlatToDown25:
            return InvertedFlyingRCTrackDiagFlatTo25DegDown;
        case TrackElemType::diagDown25ToDown60:
            return InvertedFlyingRCTrackDiag25DegDownTo60DegDown;
        case TrackElemType::diagDown60ToDown25:
            return InvertedFlyingRCTrackDiag60DegDownTo25DegDown;
        case TrackElemType::diagDown25ToFlat:
            return InvertedFlyingRCTrackDiag25DegDownToFlat;
        case TrackElemType::diagFlatToLeftBank:
            return InvertedFlyingRCTrackDiagFlatToLeftBank;
        case TrackElemType::diagFlatToRightBank:
            return InvertedFlyingRCTrackDiagFlatToRightBank;
        case TrackElemType::diagLeftBankToFlat:
            return InvertedFlyingRCTrackDiagLeftBankToFlat;
        case TrackElemType::diagRightBankToFlat:
            return InvertedFlyingRCTrackDiagRightBankToFlat;
        case TrackElemType::diagLeftBankToUp25:
            return InvertedFlyingRCTrackDiagLeftBankTo25DegUp;
        case TrackElemType::diagRightBankToUp25:
            return InvertedFlyingRCTrackDiagRightBankTo25DegUp;
        case TrackElemType::diagUp25ToLeftBank:
            return InvertedFlyingRCTrackDiag25DegUpToLeftBank;
        case TrackElemType::diagUp25ToRightBank:
            return InvertedFlyingRCTrackDiag25DegUpToRightBank;
        case TrackElemType::diagLeftBankToDown25:
            return InvertedFlyingRCTrackDiagLeftBankTo25DegDown;
        case TrackElemType::diagRightBankToDown25:
            return InvertedFlyingRCTrackDiagRightBankTo25DegDown;
        case TrackElemType::diagDown25ToLeftBank:
            return InvertedFlyingRCTrackDiag25DegDownToLeftBank;
        case TrackElemType::diagDown25ToRightBank:
            return InvertedFlyingRCTrackDiag25DegDownToRightBank;
        case TrackElemType::diagLeftBank:
            return InvertedFlyingRCTrackDiagLeftBank;
        case TrackElemType::diagRightBank:
            return InvertedFlyingRCTrackDiagRightBank;
        case TrackElemType::blockBrakes:
            return InvertedFlyingRCTrackBlockBrakes;
        case TrackElemType::leftBankedQuarterTurn3TileUp25:
            return InvertedFlyingRCTrackLeftBankedQuarterTurn325DegUp;
        case TrackElemType::rightBankedQuarterTurn3TileUp25:
            return InvertedFlyingRCTrackRightBankedQuarterTurn325DegUp;
        case TrackElemType::leftBankedQuarterTurn3TileDown25:
            return InvertedFlyingRCTrackLeftBankedQuarterTurn325DegDown;
        case TrackElemType::rightBankedQuarterTurn3TileDown25:
            return InvertedFlyingRCTrackRightBankedQuarterTurn325DegDown;
        case TrackElemType::leftBankedQuarterTurn5TileUp25:
            return InvertedFlyingRCTrackLeftBankedQuarterTurn525DegUp;
        case TrackElemType::rightBankedQuarterTurn5TileUp25:
            return InvertedFlyingRCTrackRightBankedQuarterTurn525DegUp;
        case TrackElemType::leftBankedQuarterTurn5TileDown25:
            return InvertedFlyingRCTrackLeftBankedQuarterTurn525DegDown;
        case TrackElemType::rightBankedQuarterTurn5TileDown25:
            return InvertedFlyingRCTrackRightBankedQuarterTurn525DegDown;
        case TrackElemType::up25ToLeftBankedUp25:
            return InvertedFlyingRCTrack25DegUpToLeftBanked25DegUp;
        case TrackElemType::up25ToRightBankedUp25:
            return InvertedFlyingRCTrack25DegUpToRightBanked25DegUp;
        case TrackElemType::leftBankedUp25ToUp25:
            return InvertedFlyingRCTrackLeftBanked25DegUpTo25DegUp;
        case TrackElemType::rightBankedUp25ToUp25:
            return InvertedFlyingRCTrackRightBanked25DegUpTo25DegUp;
        case TrackElemType::down25ToLeftBankedDown25:
            return InvertedFlyingRCTrack25DegDownToLeftBanked25DegDown;
        case TrackElemType::down25ToRightBankedDown25:
            return InvertedFlyingRCTrack25DegDownToRightBanked25DegDown;
        case TrackElemType::leftBankedDown25ToDown25:
            return InvertedFlyingRCTrackLeftBanked25DegDownTo25DegDown;
        case TrackElemType::rightBankedDown25ToDown25:
            return InvertedFlyingRCTrackRightBanked25DegDownTo25DegDown;
        case TrackElemType::leftBankedFlatToLeftBankedUp25:
            return InvertedFlyingRCTrackLeftBankedFlatToLeftBanked25DegUp;
        case TrackElemType::rightBankedFlatToRightBankedUp25:
            return InvertedFlyingRCTrackRightBankedFlatToRightBanked25DegUp;
        case TrackElemType::leftBankedUp25ToLeftBankedFlat:
            return InvertedFlyingRCTrackLeftBanked25DegUpToLeftBankedFlat;
        case TrackElemType::rightBankedUp25ToRightBankedFlat:
            return InvertedFlyingRCTrackRightBanked25DegUpToRightBankedFlat;
        case TrackElemType::leftBankedFlatToLeftBankedDown25:
            return InvertedFlyingRCTrackLeftBankedFlatToLeftBanked25DegDown;
        case TrackElemType::rightBankedFlatToRightBankedDown25:
            return InvertedFlyingRCTrackRightBankedFlatToRightBanked25DegDown;
        case TrackElemType::leftBankedDown25ToLeftBankedFlat:
            return InvertedFlyingRCTrackLeftBanked25DegDownToLeftBankedFlat;
        case TrackElemType::rightBankedDown25ToRightBankedFlat:
            return InvertedFlyingRCTrackRightBanked25DegDownToRightBankedFlat;
        case TrackElemType::flatToLeftBankedUp25:
            return InvertedFlyingRCTrackFlatToLeftBanked25DegUp;
        case TrackElemType::flatToRightBankedUp25:
            return InvertedFlyingRCTrackFlatToRightBanked25DegUp;
        case TrackElemType::leftBankedUp25ToFlat:
            return InvertedFlyingRCTrackLeftBanked25DegUpToFlat;
        case TrackElemType::rightBankedUp25ToFlat:
            return InvertedFlyingRCTrackRightBanked25DegUpToFlat;
        case TrackElemType::flatToLeftBankedDown25:
            return InvertedFlyingRCTrackFlatToLeftBanked25DegDown;
        case TrackElemType::flatToRightBankedDown25:
            return InvertedFlyingRCTrackFlatToRightBanked25DegDown;
        case TrackElemType::leftBankedDown25ToFlat:
            return InvertedFlyingRCTrackLeftBanked25DegDownToFlat;
        case TrackElemType::rightBankedDown25ToFlat:
            return InvertedFlyingRCTrackRightBanked25DegDownToFlat;
        case TrackElemType::leftFlyerTwistDown:
            return InvertedFlyingRCTrackLeftFlyerTwistDown;
        case TrackElemType::rightFlyerTwistDown:
            return InvertedFlyingRCTrackRightFlyerTwistDown;
        case TrackElemType::flyerHalfLoopInvertedDown:
            return FlyingRCTrackFlyerHalfLoopDown;
        // OpenRCT2-specific paint code
        case TrackElemType::booster:
            return InvertedFlyingRCTrackBooster;
        case TrackElemType::up90:
            return InvertedFlyingRCTrack90DegUp;
        case TrackElemType::down90:
            return InvertedFlyingRCTrack90DegDown;
        // OpenRCT2-specific track elements
        case TrackElemType::diagBrakes:
            return InvertedFlyingRCTrackDiagBrakes;
        case TrackElemType::diagBlockBrakes:
            return InvertedFlyingRCTrackDiagBlockBrakes;
            // New Inversions
        //  Medium half loops
        case TrackElemType::leftMediumHalfLoopUp:
            return InvertedFlyingRCTrackLeftMediumHalfLoopUp;
        case TrackElemType::rightMediumHalfLoopUp:
            return InvertedFlyingRCTrackRightMediumHalfLoopUp;
        case TrackElemType::leftMediumHalfLoopDown:
            return InvertedFlyingRCTrackLeftMediumHalfLoopDown;
        case TrackElemType::rightMediumHalfLoopDown:
            return InvertedFlyingRCTrackRightMediumHalfLoopDown;

        // barrell rolls
        case TrackElemType::leftBarrelRollUpToDown:
            return InvertedFlyingRCTrackLeftBarrelRollUpToDown;
        case TrackElemType::rightBarrelRollUpToDown:
            return InvertedFlyingRCTrackRightBarrelRollUpToDown;
        case TrackElemType::leftBarrelRollDownToUp:
            return InvertedFlyingRCTrackLeftBarrelRollDownToUp;
        case TrackElemType::rightBarrelRollDownToUp:
            return InvertedFlyingRCTrackRightBarrelRollDownToUp;

        // large corkscrew
        case TrackElemType::leftLargeCorkscrewUp:
            return InvertedFlyingRCTrackLeftLargeCorkscrewUp;
        case TrackElemType::rightLargeCorkscrewUp:
            return InvertedFlyingRCTrackRightLargeCorkscrewUp;
        case TrackElemType::leftLargeCorkscrewDown:
            return InvertedFlyingRCTrackLeftLargeCorkscrewDown;
        case TrackElemType::rightLargeCorkscrewDown:
            return InvertedFlyingRCTrackRightLargeCorkscrewDown;

        // zero-g rolls
        case TrackElemType::leftZeroGRollUp:
            return InvertedFlyingRCTrackLeftZeroGRollUp;
        case TrackElemType::rightZeroGRollUp:
            return InvertedFlyingRCTrackRightZeroGRollUp;
        case TrackElemType::leftZeroGRollDown:
            return InvertedFlyingRCTrackLeftZeroGRollDown;
        case TrackElemType::rightZeroGRollDown:
            return InvertedFlyingRCTrackRightZeroGRollDown;
        case TrackElemType::leftLargeZeroGRollUp:
            return InvertedFlyingRCTrackLeftLargeZeroGRollUp;
        case TrackElemType::rightLargeZeroGRollUp:
            return InvertedFlyingRCTrackRightLargeZeroGRollUp;
        case TrackElemType::leftLargeZeroGRollDown:
            return InvertedFlyingRCTrackLeftLargeZeroGRollDown;
        case TrackElemType::rightLargeZeroGRollDown:
            return InvertedFlyingRCTrackRightLargeZeroGRollDown;

        // dive loops
        case TrackElemType::leftEighthDiveLoopUpToOrthogonal:
            return InvertedFlyingRCTrackLeftEighthDiveLoopUpToOrthogonal;
        case TrackElemType::rightEighthDiveLoopUpToOrthogonal:
            return InvertedFlyingRCTrackRightEighthDiveLoopUpToOrthogonal;
        case TrackElemType::leftEighthDiveLoopDownToDiag:
            return InvertedFlyingRCTrackLeftEighthDiveLoopDownToDiag;
        case TrackElemType::rightEighthDiveLoopDownToDiag:
            return InvertedFlyingRCTrackRightEighthDiveLoopToDownOrthogonal;

        case TrackElemType::leftTwistDownToUp:
            return InvertedFlyingRCTrackLeftTwistDownToUp;
        case TrackElemType::rightTwistDownToUp:
            return InvertedFlyingRCTrackRightTwistDownToUp;
        case TrackElemType::leftTwistUpToDown:
            return InvertedFlyingRCTrackLeftTwistUpToDown;
        case TrackElemType::rightTwistUpToDown:
            return InvertedFlyingRCTrackRightTwistUpToDown;
        case TrackElemType::leftCorkscrewUp:
            return InvertedFlyingRCTrackLeftCorkscrewUp;
        case TrackElemType::rightCorkscrewUp:
            return InvertedFlyingRCTrackRightCorkscrewUp;
        case TrackElemType::leftCorkscrewDown:
            return InvertedFlyingRCTrackLeftCorkscrewDown;
        case TrackElemType::rightCorkscrewDown:
            return InvertedFlyingRCTrackRightCorkscrewDown;

        default:
            return GetTrackPaintFunctionFlyingRC(trackType);
    }
}