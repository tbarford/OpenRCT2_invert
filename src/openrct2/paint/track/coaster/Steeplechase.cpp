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
#include "../../../world/tile_element/TrackElement.h"
#include "../../Paint.h"
#include "../../support/MetalSupports.h"
#include "../../tile_element/Paint.TileElement.h"
#include "../../tile_element/Segment.h"
#include "../../track/Segment.h"
#include "../../track/Support.h"
#include "../../track_pieces/QuarterHelix.h"

using namespace OpenRCT2;

static constexpr TunnelGroup kTunnelGroup = TunnelGroup::standard;

static constexpr const uint32_t SteeplechaseRCDiagBrakeImages[kNumOrthogonalDirections] = {
    SPR_TRACKS_STEEPLECHASE_DIAG_BRAKES,
    SPR_TRACKS_STEEPLECHASE_DIAG_BRAKES + 1,
    SPR_TRACKS_STEEPLECHASE_DIAG_BRAKES,
    SPR_TRACKS_STEEPLECHASE_DIAG_BRAKES + 1,
};

static constexpr std::array<std::array<int8_t, kNumOrthogonalDirections>, kQuarterHelixSequenceCount>
    kLeftQuarterHelixSupportHeights = { { { 4, 3, 0, 0 }, {}, {}, {}, {}, {}, { 4, 8, 8, 4 } } };
static constexpr std::array<std::array<int8_t, kNumOrthogonalDirections>, kQuarterHelixSequenceCount>
    kRightQuarterHelixSupportHeights = { { { 1, 0, 4, 4 }, {}, {}, {}, {}, {}, { 4, 8, 7, 4 } } };

/** rct2: 0x008A59A8 */
static void SteeplechaseTrackFlat(
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
                    session, direction, session.TrackColours.WithIndex(28635), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 1:
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28636), { 0, 6, height }, { 32, 20, 3 });
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
                    session, direction, session.TrackColours.WithIndex(28633), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 1:
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28634), { 0, 6, height }, { 32, 20, 3 });
                break;
        }
    }
    MetalASupportsPaintSetupRotated(
        session, supportType.metal, MetalSupportPlace::centre, direction, 0, height, session.SupportColours);
    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

static void SteeplechaseTrackStation(
    PaintSession& session, const Ride& ride, [[maybe_unused]] uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    static constexpr ImageIndex imageIds[4] = {
        28635,
        28636,
        28635,
        28636,
    };
    PaintAddImageAsParentRotated(
        session, direction, session.TrackColours.WithIndex(imageIds[direction]), { 0, 6, height },
        { { 0, 6, height + 1 }, { 32, 20, 3 } });
    if (TrackPaintUtilDrawStation(session, ride, direction, height, trackElement, StationBaseType::b, -2))
    {
        DrawSupportsSideBySide(session, direction, height, session.SupportColours, MetalSupportType::boxed);
    }
    else
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::centre, direction, 0, height, session.SupportColours);
    }
    TrackPaintUtilDrawStationTunnel(session, direction, height);
    PaintUtilSetSegmentSupportHeight(session, kSegmentsAll, 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x008A59B8 */
static void SteeplechaseTrack25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    if (trackElement.hasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28649), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28655), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28651), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28656), { 0, 6, height }, { 32, 20, 3 });
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28637), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28643), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28639), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28644), { 0, 6, height }, { 32, 20, 3 });
                break;
        }
    }
    MetalASupportsPaintSetupRotated(
        session, supportType.metal, MetalSupportPlace::centre, direction, 8, height, session.SupportColours);
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x008A59C8 */
static void SteeplechaseTrackFlatTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    if (trackElement.hasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28650), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28657), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28652), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28658), { 0, 6, height }, { 32, 20, 3 });
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28638), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28645), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28640), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28646), { 0, 6, height }, { 32, 20, 3 });
                break;
        }
    }
    MetalASupportsPaintSetupRotated(
        session, supportType.metal, MetalSupportPlace::centre, direction, direction == 0 ? 3 : 2, height,
        session.SupportColours);
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 48);
}

/** rct2: 0x008A59D8 */
static void SteeplechaseTrack25DegUpToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    if (trackElement.hasChain())
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28654), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28660), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28653), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28659), { 0, 6, height }, { 32, 20, 3 });
                break;
        }
    }
    else
    {
        switch (direction)
        {
            case 0:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28642), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 1:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28648), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 2:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28641), { 0, 6, height }, { 32, 20, 3 });
                break;
            case 3:
                PaintAddImageAsParentRotated(
                    session, direction, session.TrackColours.WithIndex(28647), { 0, 6, height }, { 32, 20, 3 });
                break;
        }
    }
    MetalASupportsPaintSetupRotated(
        session, supportType.metal, MetalSupportPlace::centre, direction, direction <= 1 ? 6 : 5, height,
        session.SupportColours);
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::flatTo25Deg);
    }
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 40);
}

/** rct2: 0x008A59E8 */
static void SteeplechaseTrack25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrack25DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A59F8 */
static void SteeplechaseTrackFlatTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrack25DegUpToFlat(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A5A08 */
static void SteeplechaseTrack25DegDownToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrackFlatTo25DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A5A18 */
static void SteeplechaseTrackLeftQuarterTurn5(
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
                        session, direction, session.TrackColours.WithIndex(28698), { 0, 6, height }, { 32, 20, 3 });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 1, height, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28703), { 0, 6, height }, { 32, 20, 3 });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::centre, direction, 1, height, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28708), { 0, 6, height }, { 32, 20, 3 });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height - 3, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28693), { 0, 6, height }, { 32, 20, 3 });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::centre, direction, 0, height - 1,
                        session.SupportColours);
                    break;
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
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
                        session, direction, session.TrackColours.WithIndex(28697), { 0, 0, height }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28702), { 0, 0, height }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28707), { 0, 16, height }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28692), { 0, 16, height }, { 32, 16, 3 });
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
                        session, direction, session.TrackColours.WithIndex(28696), { 0, 16, height }, { 16, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28701), { 16, 16, height }, { 16, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28706), { 16, 0, height }, { 16, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28691), { 0, 0, height }, { 16, 16, 3 });
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
                        session, direction, session.TrackColours.WithIndex(28695), { 16, 0, height }, { 16, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28700), { 0, 0, height }, { 16, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28705), { 0, 0, height }, { 16, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28690), { 16, 0, height }, { 16, 32, 3 });
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
                        session, direction, session.TrackColours.WithIndex(28694), { 6, 0, height }, { 20, 32, 3 });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::centre, DirectionPrev(direction), 0, height - 3,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28699), { 6, 0, height }, { 20, 32, 3 });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28704), { 6, 0, height }, { 20, 32, 3 });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::centre, DirectionPrev(direction), 1, height,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28689), { 6, 0, height }, { 20, 32, 3 });
                    MetalASupportsPaintSetup(
                        session, supportType.metal, MetalSupportPlace::centre, 0, height - 2, session.SupportColours);
                    break;
            }
            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x008A5A28 */
static void SteeplechaseTrackRightQuarterTurn5(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    SteeplechaseTrackLeftQuarterTurn5(session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A5A38 */
static void SteeplechaseTrackSBendLeft(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
        {
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28665), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28672), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28668), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28669), { 0, 6, height }, { 33, 20, 3 });
                    break;
            }
            auto heightOffset = (direction == 3) ? 2 : 0;
            DrawSBendLeftSupports(session, supportType.metal, trackSequence, direction, height - heightOffset, 0, 0);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        }
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28666), { 0, 0, height }, { 33, 26, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28671), { 0, 0, height }, { 33, 26, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28667), { 0, 6, height }, { 33, 26, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28670), { 0, 6, height }, { 33, 26, 3 });
                    break;
            }
            DrawSBendLeftSupports(session, supportType.metal, trackSequence, direction, height, 0, 0);
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
                        session, direction, session.TrackColours.WithIndex(28667), { 0, 6, height }, { 33, 26, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28670), { 0, 6, height }, { 33, 26, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28666), { 0, 0, height }, { 33, 26, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28671), { 0, 0, height }, { 33, 26, 3 });
                    break;
            }
            DrawSBendLeftSupports(session, supportType.metal, trackSequence, direction, height, 0, 0);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28668), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28669), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28665), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28672), { 0, 6, height }, { 33, 20, 3 });
                    break;
            }
            int8_t heightOffset = direction == 1 ? 2 : 0;
            DrawSBendLeftSupports(session, supportType.metal, trackSequence, direction, height - heightOffset, 0, 0);
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
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x008A5A48 */
static void SteeplechaseTrackSBendRight(
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
                        session, direction, session.TrackColours.WithIndex(28661), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28676), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28664), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28673), { 0, 6, height }, { 33, 20, 3 });
                    break;
            }
            DrawSBendRightSupports(session, supportType.metal, trackSequence, direction, height, 0, 0);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28662), { 0, 6, height }, { 33, 26, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28675), { 0, 6, height }, { 33, 26, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28663), { 0, 0, height }, { 33, 26, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28674), { 0, 0, height }, { 33, 26, 3 });
                    break;
            }
            DrawSBendRightSupports(
                session, supportType.metal, trackSequence, direction, direction == 0 ? height - 2 : height, 0, 0);
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
                        session, direction, session.TrackColours.WithIndex(28663), { 0, 0, height }, { 33, 26, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28674), { 0, 0, height }, { 33, 26, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28662), { 0, 6, height }, { 33, 26, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28675), { 0, 6, height }, { 33, 26, 3 });
                    break;
            }
            DrawSBendRightSupports(
                session, supportType.metal, trackSequence, direction, direction == 2 ? height - 2 : height, 0, 0);
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
                        session, direction, session.TrackColours.WithIndex(28664), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28673), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28661), { 0, 6, height }, { 33, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28676), { 0, 6, height }, { 33, 20, 3 });
                    break;
            }
            DrawSBendRightSupports(session, supportType.metal, trackSequence, direction, height, 0, 0);
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
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x008A5A88 */
static void SteeplechaseTrackLeftQuarterTurn3(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (trackSequence)
    {
        case 0:
        {
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28682), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28685), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28688), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28679), { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            constexpr uint8_t _specialValues[] = { 3, 1, 0, 0 };
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, _specialValues[direction], height,
                session.SupportColours);

            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        }
        case 1:
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28681), { 16, 0, height }, { 16, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28684), { 0, 0, height }, { 16, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28687), { 0, 16, height }, { 16, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28678), { 16, 16, height }, { 16, 16, 3 });
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
        {
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28680), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28683), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28686), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28677), { 6, 0, height }, { 20, 32, 3 });
                    break;
            }
            constexpr uint8_t _specialValues[] = { 0, 1, 3, 0 };
            constexpr int8_t _heightOffsets[] = { 0, 0, 0, -3 };
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, DirectionPrev(direction), _specialValues[direction],
                height + _heightOffsets[direction], session.SupportColours);

            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        }
    }
}

/** rct2: 0x008A5A98 */
static void SteeplechaseTrackRightQuarterTurn3(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    SteeplechaseTrackLeftQuarterTurn3(session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A5AA8 */
static void SteeplechaseTrackBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(28635), { 0, 6, height }, { 32, 20, 3 });
            break;
        case 1:
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(28636), { 0, 6, height }, { 32, 20, 3 });
            break;
    }
    MetalASupportsPaintSetupRotated(
        session, supportType.metal, MetalSupportPlace::centre, direction, 0, height, session.SupportColours);

    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x008A5AD8 */
static void SteeplechaseTrackLeftEighthToDiag(
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
                        session, direction, session.TrackColours.WithIndex(28725), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28729), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28733), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28737), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 0, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28726), { 0, 0, height },
                        { { 0, 0, height }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28730), { 0, 0, height },
                        { { 0, 0, height }, { 34, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28734), { 0, 0, height },
                        { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28738), { 0, 0, height },
                        { { 0, 16, height }, { 32, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(28727), { 0, 0, height },
                        { { 0, 16, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28731), { 0, 0, height },
                        { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28735), { 0, 0, height },
                        { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28739), { 0, 0, height },
                        { { 0, 0, height }, { 16, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(28728), { 0, 0, height },
                        { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28732), { 0, 0, height },
                        { { 0, 16, height }, { 16, 18, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28736), { 0, 0, height },
                        { { 0, 0, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28740), { 0, 0, height },
                        { { 16, 0, height }, { 16, 16, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::bottomCorner, direction, 0, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x008A5AE8 */
static void SteeplechaseTrackRightEighthToDiag(
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
                        session, direction, session.TrackColours.WithIndex(28709), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28713), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28717), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28721), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 0, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28710), { 0, 0, height },
                        { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28714), { 0, 0, height },
                        { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28718), { 0, 0, height },
                        { { 0, 0, height }, { 34, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28722), { 0, 0, height },
                        { { 0, 0, height }, { 32, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(28711), { 0, 0, height },
                        { { 0, 0, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28715), { 0, 0, height },
                        { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28719), { 0, 0, height },
                        { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28723), { 0, 0, height },
                        { { 0, 16, height }, { 16, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(28712), { 0, 0, height },
                        { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28716), { 0, 0, height },
                        { { 0, 0, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28720), { 0, 0, height },
                        { { 0, 16, height }, { 16, 18, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(28724), { 0, 0, height },
                        { { 16, 16, height }, { 16, 16, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
            break;
    }
}

/** rct2: 0x008A5AF8 */
static void SteeplechaseTrackLeftEighthToOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    SteeplechaseTrackRightEighthToDiag(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A5B08 */
static void SteeplechaseTrackRightEighthToOrthogonal(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    SteeplechaseTrackLeftEighthToDiag(session, ride, trackSequence, (direction + 3) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A5AC8 */
static void SteeplechaseTrackDiagFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    constexpr ImageIndex images[2][kNumOrthogonalDirections] = {
        { 28741, 28742, 28743, 28744 },
        { 28757, 28758, 28759, 28760 },
    };
    TrackPaintUtilDiagTilesPaintExtra(
        session, 3, height, direction, trackSequence, images[trackElement.hasChain()], supportType.metal);
}

static void SteeplechaseTrackDiagBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    TrackPaintUtilDiagTilesPaint(
        session, 3, height, direction, trackSequence, SteeplechaseRCDiagBrakeImages, defaultDiagTileOffsets,
        defaultDiagBoundLengths, nullptr);

    if (trackSequence == 3)
    {
        MetalASupportsPaintSetup(
            session, supportType.metal, kDiagSupportPlacement[direction], 0, height, session.SupportColours);
    }

    PaintSegments blockedSegments = BlockedSegments::kDiagStraightFlat[trackSequence];
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(blockedSegments, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x008A5B38 */
static void SteeplechaseTrackDiag25DegUp(
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
                            session, direction, session.TrackColours.WithIndex(28772), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28756), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28769), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28753), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28771), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28755), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28770), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28754), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 6, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

/** rct2: 0x008A5B18 */
static void SteeplechaseTrackDiagFlatTo25DegUp(
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
                            session, direction, session.TrackColours.WithIndex(28764), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28748), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28761), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28745), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28763), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28747), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28762), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28746), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x008A5B28 */
static void SteeplechaseTrackDiag25DegUpToFlat(
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
                            session, direction, session.TrackColours.WithIndex(28768), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28752), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28765), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28749), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28767), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28751), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28766), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28750), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 4, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

/** rct2: 0x008A5B68 */
static void SteeplechaseTrackDiag25DegDown(
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
                            session, direction, session.TrackColours.WithIndex(28770), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28754), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28771), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28755), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28769), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28753), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28772), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28756), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 6, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
    }
}

/** rct2: 0x008A5B48 */
static void SteeplechaseTrackDiagFlatTo25DegDown(
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
                            session, direction, session.TrackColours.WithIndex(28766), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28750), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            break;
        case 1:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28767), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28751), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            break;
        case 2:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28765), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28749), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            break;
        case 3:
            if (trackElement.hasChain())
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28768), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28752), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 4, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            break;
    }

    PaintUtilSetGeneralSupportHeight(session, height + 56);
}

/** rct2: 0x008A5B58 */
static void SteeplechaseTrackDiag25DegDownToFlat(
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
                            session, direction, session.TrackColours.WithIndex(28762), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 3:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28746), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28763), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 0:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28747), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28761), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 2:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28745), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
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
                            session, direction, session.TrackColours.WithIndex(28764), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            else
            {
                switch (direction)
                {
                    case 1:
                        PaintAddImageAsParentRotated(
                            session, direction, session.TrackColours.WithIndex(28748), { -16, -16, height },
                            { { -16, -16, height }, { 32, 32, 3 } });
                        break;
                }
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 0, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
    }
}

/** rct2: 0x008A5AB8 */
static void SteeplechaseTrackBlockBrakes(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(28635), { 0, 6, height }, { 32, 20, 3 });
            break;
        case 1:
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(28636), { 0, 6, height }, { 32, 20, 3 });
            break;
    }
    MetalASupportsPaintSetupRotated(
        session, supportType.metal, MetalSupportPlace::centre, direction, 0, height, session.SupportColours);
    PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    PaintUtilSetSegmentSupportHeight(session, PaintUtilRotateSegments(BlockedSegments::kStraightFlat, direction), 0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

// added by openrct2

// tiny turns
/** rct2: 0x0078B394 */
static void SteeplechaseTrackLeftQuarterTurn1(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    static constexpr uint32_t imageIds[4] = {
        SPR_TRACKS_STEEPLECHASE_RC_VERY_SMALL_TURNS,
        SPR_TRACKS_STEEPLECHASE_RC_VERY_SMALL_TURNS + 1,
        SPR_TRACKS_STEEPLECHASE_RC_VERY_SMALL_TURNS + 2,
        SPR_TRACKS_STEEPLECHASE_RC_VERY_SMALL_TURNS + 3,
    };

    auto imageId = session.TrackColours.WithIndex(imageIds[direction]);
    switch (direction)
    {
        case 0:
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 2, height }, { 26, 24, 2 } });
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::topLeftSide, 8, height, session.SupportColours);
            break;
        case 1:
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { 26, 26, 2 });
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::topRightSide, 8, height, session.SupportColours);
            break;
        case 2:
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 2, 6, height }, { 24, 26, 2 } });
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::bottomRightSide, 8, height, session.SupportColours);
            break;
        case 3:
            PaintAddImageAsParent(session, imageId, { 0, 0, height }, { { 6, 6, height }, { 24, 24, 2 } });
            MetalASupportsPaintSetup(
                session, supportType.metal, MetalSupportPlace::bottomLeftSide, 8, height, session.SupportColours);
            break;
    }

    TrackPaintUtilLeftQuarterTurn1TileTunnel(
        session, kTunnelGroup, direction, height, 0, TunnelSubType::flat, 0, TunnelSubType::flat);
    PaintUtilSetSegmentSupportHeight(
        session,
        PaintUtilRotateSegments(
            { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + kDefaultGeneralSupportHeight);
}

/** rct2: 0x0078B3A4 */
static void SteeplechaseTrackRightQuarterTurn1(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrackLeftQuarterTurn1(session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}

static void SteeplechaseTrackDiagFlatTo60DegUpLongBase(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 9)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 0)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 6)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 3)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 10)),
                        { -16, -16, height }, { { -20, -20, height + 8 }, { 24, 24, 1 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 11, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 1)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 5:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 7)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 6:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 4)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 11)),
                        { -16, -16, height }, { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 23, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 96);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 2)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 120);
            break;
        case 8:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 8)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 120);
            break;
        case 9:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 5)),
                        { -16, -16, height }, { { -16, -16, height + 80 }, { 32, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 31, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 136);
            break;
    }
}

static void SteeplechaseTrackDiag60DegUpToFlatLongBase(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 21)),
                        { -16, -16, height }, { { -8, -8, height + 0 }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 96);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 12)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 18)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 15)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 22)),
                        { -16, -16, height }, { { -8, -8, height + 56 }, { 16, 16, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 40, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 112);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 13)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 5:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 19)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 6:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 16)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 23)),
                        { -16, -16, height }, { { -16, -16, height + 24 }, { 24, 24, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 22, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 14)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
        case 8:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 20)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
        case 9:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 17)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 14, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
    }
}

static void SteeplechaseTrackDiagFlatTo60DegDownLongBase(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 17)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 20)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 14)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 23)),
                        { -16, -16, height }, { { -16, -16, height + 24 }, { 24, 24, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 16)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 36, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 19)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 5:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 13)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 6:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 22)),
                        { -16, -16, height }, { { -8, -8, height + 56 }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 15)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 70, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 112);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 18)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 8:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 12)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
        case 9:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 21)),
                        { -16, -16, height }, { { -8, -8, height + 0 }, { 16, 16, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 26, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 96);
            break;
    }
}

static void SteeplechaseTrackDiag60DegDownToFlatLongBase(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 5)),
                        { -16, -16, height }, { { -16, -16, height + 80 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 136);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 8)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 120);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 2)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 120);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 11)),
                        { -16, -16, height }, { { -16, -16, height + 32 }, { 32, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 4)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 50, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 96);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 7)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 5:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 1)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 6:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 10)),
                        { -16, -16, height }, { { -8, -8, height + 8 }, { 24, 24, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 3)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 24, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre,
                      PaintSegment::topRight, PaintSegment::bottomRight, PaintSegment::right },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 7:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 6)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::topLeft, PaintSegment::top, PaintSegment::centre, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 8:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 0)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottomLeft, PaintSegment::centre, PaintSegment::bottom, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 9:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS_DIAGONAL + 9)),
                        { -16, -16, height }, { { -16, -16, height + 0 }, { 32, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 9, height + 0, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::topLeft, PaintSegment::bottomLeft, PaintSegment::centre }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 32);
            break;
    }
}

static void SteeplechaseTrackFlatTo60DegUp(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 0)),
                        { 0, 0, height }, { { 0, 2, height }, { 32, 27, 4 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::centre, direction, 10, height, session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 2)),
                        { 0, 0, height }, { { 29, 4, height + 2 }, { 1, 24, 43 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 1)),
                        { 0, 0, height }, { { 0, 4, height }, { 32, 2, 43 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::centre, direction, 10, height, session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 4)),
                        { 0, 0, height }, { { 29, 4, height + 2 }, { 1, 24, 43 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 3)),
                        { 0, 0, height }, { { 0, 4, height }, { 32, 2, 43 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::centre, direction, 10, height, session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 5)),
                        { 0, 0, height }, { { 0, 2, height }, { 32, 27, 4 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::centre, direction, 10, height, session.SupportColours);
                    break;
            }
        case 1:
            break;
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 24, kTunnelGroup, TunnelSubType::slopeEnd);
    }
    PaintUtilSetSegmentSupportHeight(
        session, PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 64);
}

static void SteeplechaseTrack60DegUpToFlat(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 6)),
                        { 0, 0, height }, { { 0, 2, height }, { 32, 27, 4 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 7)),
                        { 0, 0, height }, { { 0, 4, height }, { 32, 2, 43 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 8)),
                        { 0, 0, height }, { { 29, 4, height + 2 }, { 1, 24, 43 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 10)),
                        { 0, 0, height }, { { 29, 4, height + 2 }, { 1, 24, 43 } });
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 9)),
                        { 0, 0, height }, { { 0, 4, height }, { 32, 2, 43 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS + 11)),
                        { 0, 0, height }, { { 0, 2, height }, { 32, 27, 4 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 23, height, session.SupportColours);

        case 1:
            break;
    }
    if (direction == 0 || direction == 3)
    {
        PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
    }
    else
    {
        PaintUtilPushTunnelRotated(session, direction, height + 24, kTunnelGroup, TunnelSubType::flat);
    }
    PaintUtilSetSegmentSupportHeight(
        session, PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
        0xFFFF, 0);
    PaintUtilSetGeneralSupportHeight(session, height + 72);
}

static void SteeplechaseTrackFlatTo60DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrack60DegUpToFlat(
        session, ride, trackSequence, DirectionReverse(direction), height, trackElement, supportType);
}

static void SteeplechaseTrack60DegDownToFlat(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrackFlatTo60DegUp(
        session, ride, trackSequence, DirectionReverse(direction), height, trackElement, supportType);
}

static void SteeplechaseTrackDiagFlatTo60DegUp(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 3)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
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
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 0)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 2)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 1)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 11, height, session.SupportColours);

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
    }
}

static void SteeplechaseTrackDiag60DegUpToFlat(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 7)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 4)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 6)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 5)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 24, height, session.SupportColours);

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void SteeplechaseTrackDiagFlatTo60DegDown(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 5)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 6)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 4)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 7)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 20, height, session.SupportColours);

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void SteeplechaseTrackDiag60DegDownToFlat(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 1)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
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
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 2)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
                    break;
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 2:
            switch (direction)
            {
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 0)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 3:
            switch (direction)
            {
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_SMALL_SLOPE_TRANSITIONS_DIAGONAL + 3)),
                        { -16, -16, height }, { { -16, -16, height }, { 32, 32, 4 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 9, height, session.SupportColours);

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
    }
}

static void SteeplechaseTrackFlatTo60DegUpLongBase(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 0)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 4)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 8)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 12)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
            {
                MetalASupportsPaintSetupRotated(
                    session, supportType.metal, MetalSupportPlace::centre, direction, 11, height, session.SupportColours);
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::flat);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 1)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 5)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 9)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 13)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
            {
                MetalASupportsPaintSetupRotated(
                    session, supportType.metal, MetalSupportPlace::centre, direction, 17, height, session.SupportColours);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 48);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 2)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 6)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 10)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 14)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
            {
                MetalASupportsPaintSetupRotated(
                    session, supportType.metal, MetalSupportPlace::centre, direction, 18, height, session.SupportColours);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 64);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 3)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 7)),
                        { 0, 0, height }, { { 0, 27, height }, { 32, 1, 98 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 11)),
                        { 0, 0, height }, { { 0, 27, height }, { 32, 1, 98 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 15)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
            {
                MetalASupportsPaintSetupRotated(
                    session, supportType.metal, MetalSupportPlace::centre, direction, 27, height, session.SupportColours);
            }
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height + 24, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height + 24, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
    }
}

static void SteeplechaseTrack60DegUpToFlatLongBase(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 16)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 20)),
                        { 0, 0, height }, { { 0, 27, height }, { 32, 1, 98 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 24)),
                        { 0, 0, height }, { { 0, 27, height }, { 32, 1, 98 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 28)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
            {
                MetalASupportsPaintSetupRotated(
                    session, supportType.metal, MetalSupportPlace::centre, direction, 32, height, session.SupportColours);
            }
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 17)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 21)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 25)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 29)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
            {
                MetalASupportsPaintSetupRotated(
                    session, supportType.metal, MetalSupportPlace::centre, direction, 28, height, session.SupportColours);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 80);
            break;
        case 2:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 18)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 22)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 26)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 30)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
            {
                MetalASupportsPaintSetupRotated(
                    session, supportType.metal, MetalSupportPlace::centre, direction, 21, height, session.SupportColours);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 56);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 19)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 23)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 27)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPE_TRANSITIONS + 31)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
            {
                MetalASupportsPaintSetupRotated(
                    session, supportType.metal, MetalSupportPlace::centre, direction, 13, height, session.SupportColours);
            }
            switch (direction)
            {
                case 1:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::flat);
                    break;
                case 2:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::flat);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 40);
            break;
    }
}

static void SteeplechaseTrackFlatTo60DegDownLongBase(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrack60DegUpToFlatLongBase(
        session, ride, 3 - trackSequence, DirectionReverse(direction), height, trackElement, supportType);
}

static void SteeplechaseTrack60DegDownToFlatLongBase(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrackFlatTo60DegUpLongBase(
        session, ride, 3 - trackSequence, DirectionReverse(direction), height, trackElement, supportType);
}

static void SteeplechaseTrackLeftEighthToDiagUp25(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 0)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 4)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 8)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 12)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 13, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 1)),
                        { 0, 0, height }, { { 0, 0, height }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 5)),
                        { 0, 0, height }, { { -16, 0, height }, { 48, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 9)),
                        { 0, 0, height }, { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 13)),
                        { 0, 0, height }, { { 0, 16, height }, { 32, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 2)),
                        { 0, 0, height }, { { 0, 16, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 6)),
                        { 0, 0, height }, { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 10)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 14)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::topRight,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 3)),
                        { 0, 0, height }, { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 7)),
                        { 0, 0, height }, { { 0, 16, height }, { 16, 18, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 11)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 15)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 16, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::bottomCorner, direction, 14, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void SteeplechaseTrackRightEighthToDiagUp25(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 16)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 20)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 24)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 28)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 13, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 17)),
                        { 0, 0, height }, { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 21)),
                        { 0, 0, height }, { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 25)),
                        { 0, 0, height }, { { -16, 0, height }, { 48, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 29)),
                        { 0, 0, height }, { { 0, 0, height }, { 32, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 18)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 22)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 26)),
                        { 0, 0, height }, { { 4, 4, height }, { 28, 28, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 30)),
                        { 0, 0, height }, { { 0, 16, height }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 19)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 23)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 27)),
                        { 0, 0, height }, { { 0, 16, height }, { 16, 18, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 31)),
                        { 0, 0, height }, { { 16, 16, height }, { 16, 16, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 14, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void SteeplechaseTrackLeftEighthToOrthogonalUp25(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 32)),
                        { 0, 0, height }, { { 0, 16, height }, { 16, 16, 1 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::rightCorner, direction, 14, height,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 36)),
                        { 0, 0, height }, { { 16, 16, height }, { 16, 18, 1 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::rightCorner, direction, 14, height,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 40)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 16, 1 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::rightCorner, direction, 14, height,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 44)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 16, 1 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::rightCorner, direction, 11, height,
                        session.SupportColours);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 33)),
                        { 0, 0, height }, { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 37)),
                        { 0, 0, height }, { { 0, 16, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 41)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 45)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::bottom, PaintSegment::centre, PaintSegment::bottomLeft,
                      PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 3:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 34)),
                        { 0, 0, height }, { { 0, 0, height }, { 32, 16, 1 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 38)),
                        { 0, 0, height }, { { 0, 0, height }, { 34, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 42)),
                        { 0, 0, height }, { { 0, 16, height }, { 32, 16, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 46)),
                        { 0, 0, height }, { { 0, 16, height }, { 32, 16, 1 } });
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
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 35)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 39)),
                        { 0, 0, height }, { { -6, 6, height }, { 32, 20, 1 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 43)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 47)),
                        { 0, 0, height }, { { 0, 6, height }, { 32, 20, 1 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 13, height, session.SupportColours);

            if (direction == 1 || direction == 2)
            {
                PaintUtilPushTunnelRotated(session, direction, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
            }

            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void SteeplechaseTrackRightEighthToOrthogonalUp25(
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
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 48)),
                        { 0, 0, height }, { { 0, 16, height }, { 16, 16, 1 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::topCorner, DirectionNext(direction), 14, height,
                        session.SupportColours);
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 52)),
                        { 0, 0, height }, { { 16, 16, height }, { 16, 16, 1 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::topCorner, DirectionNext(direction), 14, height,
                        session.SupportColours);
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 56)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 18, 1 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::topCorner, DirectionNext(direction), 14, height,
                        session.SupportColours);
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 60)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 16, 1 } });
                    MetalASupportsPaintSetupRotated(
                        session, supportType.metal, MetalSupportPlace::topCorner, DirectionNext(direction), 11, height,
                        session.SupportColours);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::topRight,
                      PaintSegment::bottomLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 1:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 49)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 53)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 57)),
                        { 0, 0, height }, { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 61)),
                        { 0, 0, height }, { { 0, 16, height }, { 16, 16, 3 } });
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::right, PaintSegment::centre, PaintSegment::topLeft,
                      PaintSegment::topRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
        case 2:
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
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 50)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 32, 1 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 54)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 58)),
                        { 0, 0, height }, { { 0, 0, height }, { 16, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 62)),
                        { 0, 0, height }, { { 16, 0, height }, { 16, 32, 1 } });
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
        case 4:
            switch (direction)
            {
                case 0:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 51)),
                        { 0, 0, height }, { { 6, -6, height }, { 20, 32, 1 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 55)),
                        { 0, 0, height }, { { 6, 0, height }, { 20, 32, 1 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 59)),
                        { 0, 0, height }, { { 6, 0, height }, { 20, 32, 1 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex((SPR_TRACKS_STEEPLECHASE_RC_LARGE_SLOPED_TURNS + 63)),
                        { 0, 0, height }, { { 6, 0, height }, { 20, 32, 1 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, DirectionNext(direction), 13, height,
                session.SupportColours);
            if (direction == 0 || direction == 1)
            {
                PaintUtilPushTunnelRotated(session, direction + 1, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments({ PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

static void SteeplechaseTrackLeftEighthToDiagDown25(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    uint8_t map[5] = { 4, 3, 1, 2, 0 };
    trackSequence = map[trackSequence];
    SteeplechaseTrackRightEighthToOrthogonalUp25(
        session, ride, trackSequence, DirectionNext(direction), height, trackElement, supportType);
}

static void SteeplechaseTrackRightEighthToDiagDown25(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    uint8_t map[5] = { 4, 3, 1, 2, 0 };
    trackSequence = map[trackSequence];
    SteeplechaseTrackLeftEighthToOrthogonalUp25(
        session, ride, trackSequence, DirectionReverse(direction), height, trackElement, supportType);
}

static void SteeplechaseTrackLeftEighthToOrthogonalDown25(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    SteeplechaseTrackRightEighthToDiagUp25(
        session, ride, trackSequence, DirectionReverse(direction), height, trackElement, supportType);
}

static void SteeplechaseTrackRightEighthToOrthogonalDown25(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = mapLeftEighthTurnToOrthogonal[trackSequence];
    SteeplechaseTrackLeftEighthToDiagUp25(
        session, ride, trackSequence, DirectionPrev(direction), height, trackElement, supportType);
}
/** rct2: 0x008A4CAC */
static void SteeplechaseTrackLeftQuarterTurn525DegUp(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 16), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 21), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 26), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 31), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 14, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 17), { 0, 0, height }, { 32, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 22), { 0, 0, height }, { 32, 16, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 27), { 0, 0, height },
                        { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 32), { 0, 0, height },
                        { { 0, 16, height }, { 32, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 18), { 0, 0, height },
                        { { 0, 16, height }, { 16, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 23), { 0, 0, height },
                        { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 28), { 0, 0, height },
                        { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 33), { 0, 0, height }, { 16, 16, 3 });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 19), { 0, 0, height },
                        { { 16, 0, height }, { 16, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 24), { 0, 0, height }, { 16, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 29), { 0, 0, height }, { 16, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 34), { 0, 0, height },
                        { { 16, 0, height }, { 16, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 20), { 0, 0, height },
                        { { 6, 0, height }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 25), { 0, 0, height },
                        { { 6, 0, height }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 30), { 0, 0, height },
                        { { 6, 0, height }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 35), { 0, 0, height },
                        { { 6, 0, height }, { 20, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, DirectionPrev(direction), 14, height,
                session.SupportColours);
            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x008A4CBC */
static void SteeplechaseTrackRightQuarterTurn525DegUp(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 36), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 41), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 46), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 51), { 0, 0, height },
                        { { 0, 6, height }, { 32, 20, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 14, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 37), { 0, 0, height },
                        { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 42), { 0, 0, height },
                        { { 0, 16, height }, { 32, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 47), { 0, 0, height }, { 32, 16, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 52), { 0, 0, height }, { 32, 16, 3 });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 38), { 0, 0, height }, { 16, 16, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 43), { 0, 0, height },
                        { { 16, 0, height }, { 16, 16, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 48), { 0, 0, height },
                        { { 16, 16, height }, { 16, 16, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 53), { 0, 0, height },
                        { { 0, 16, height }, { 16, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 39), { 0, 0, height },
                        { { 16, 0, height }, { 16, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 44), { 0, 0, height }, { 16, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 49), { 0, 0, height }, { 16, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 54), { 0, 0, height },
                        { { 16, 0, height }, { 16, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 40), { 0, 0, height },
                        { { 6, 0, height }, { 20, 32, 3 } });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 45), { 0, 0, height },
                        { { 6, 0, height }, { 20, 32, 3 } });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 50), { 0, 0, height },
                        { { 6, 0, height }, { 20, 32, 3 } });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 55), { 0, 0, height },
                        { { 6, 0, height }, { 20, 32, 3 } });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, DirectionNext(direction), 14, height,
                session.SupportColours);
            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x008A4CCC */
static void SteeplechaseTrackLeftQuarterTurn525DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    SteeplechaseTrackRightQuarterTurn525DegUp(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A4CDC */
static void SteeplechaseTrackRightQuarterTurn525DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn5TilesToRightQuarterTurn5Tiles[trackSequence];
    SteeplechaseTrackLeftQuarterTurn525DegUp(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}
/** rct2: 0x008A4D7C */
static void SteeplechaseTrackLeftQuarterTurn325DegUp(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 0), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 2), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 4), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 6), { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 14, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::top, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 1), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 3), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 5), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 7), { 6, 0, height }, { 20, 32, 3 });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, DirectionPrev(direction), 14, height,
                session.SupportColours);
            switch (direction)
            {
                case 2:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 3:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::bottom, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomRight },
                    direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x008A4D8C */
static void SteeplechaseTrackRightQuarterTurn325DegUp(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 8), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 10), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 12), { 0, 6, height }, { 32, 20, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 14), { 0, 6, height }, { 32, 20, 3 });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, direction, 14, height, session.SupportColours);
            if (direction == 0 || direction == 3)
            {
                PaintUtilPushTunnelRotated(session, direction, height - 8, kTunnelGroup, TunnelSubType::slopeStart);
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::right, PaintSegment::centre, PaintSegment::topRight, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 9), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 1:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 11), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 2:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 13), { 6, 0, height }, { 20, 32, 3 });
                    break;
                case 3:
                    PaintAddImageAsParentRotated(
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_GENTLE_SLOPED_TURNS + 15), { 6, 0, height }, { 20, 32, 3 });
                    break;
            }
            MetalASupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::centre, DirectionNext(direction), 14, height,
                session.SupportColours);
            switch (direction)
            {
                case 0:
                    PaintUtilPushTunnelRight(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
                case 1:
                    PaintUtilPushTunnelLeft(session, height + 8, kTunnelGroup, TunnelSubType::slopeEnd);
                    break;
            }
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomRight }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x008A4D9C */
static void SteeplechaseTrackLeftQuarterTurn325DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    SteeplechaseTrackRightQuarterTurn325DegUp(
        session, ride, trackSequence, (direction + 1) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A4DAC */
static void SteeplechaseTrackRightQuarterTurn325DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    trackSequence = kMapLeftQuarterTurn3TilesToRightQuarterTurn3Tiles[trackSequence];
    SteeplechaseTrackLeftQuarterTurn325DegUp(
        session, ride, trackSequence, (direction - 1) & 3, height, trackElement, supportType);
}
/** rct2: 0x008A4FAC */
static void SteeplechaseTrackDiag60DegUp(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 11), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 8), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 10), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 9), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, (direction & 1) ? 42 : 38, height,
                session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
    }
}
/** rct2: 0x008A4F8C */
static void SteeplechaseTrackDiag25DegUpTo60DegUp(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 3), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 0), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 2), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 1), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 22, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x008A4F9C */
static void SteeplechaseTrackDiag60DegUpTo25DegUp(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 7), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 4), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 6), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 5), { -16, -16, height },
                        { { 0, 0, height }, { 16, 16, 3 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 27, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}
/** rct2: 0x008A4FDC */
static void SteeplechaseTrackDiag60DegDown(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 9), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 10), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 8), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 11), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, (direction & 1) ? 34 : 30, height,
                session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 104);
            break;
    }
}
/** rct2: 0x008A4FBC */
static void SteeplechaseTrackDiag25DegDownTo60DegDown(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 5), { -16, -16, height },
                        { { 0, 0, height }, { 16, 16, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 6), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 4), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 7), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 23, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}

/** rct2: 0x008A4FCC */
static void SteeplechaseTrackDiag60DegDownTo25DegDown(
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 1), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 2), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 0), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
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
                        session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_DIAGONALS + 3), { -16, -16, height },
                        { { -16, -16, height }, { 32, 32, 3 } });
                    break;
            }
            MetalBSupportsPaintSetupRotated(
                session, supportType.metal, MetalSupportPlace::leftCorner, direction, 14, height, session.SupportColours);
            PaintUtilSetSegmentSupportHeight(
                session,
                PaintUtilRotateSegments(
                    { PaintSegment::left, PaintSegment::centre, PaintSegment::topLeft, PaintSegment::bottomLeft }, direction),
                0xFFFF, 0);
            PaintUtilSetGeneralSupportHeight(session, height + 72);
            break;
    }
}
/** rct2: 0x008A4ADC */
static void SteeplechaseTrack60DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 12), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 13), { 0, 0, height },
                { { 0, 27, height }, { 32, 1, 98 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 14), { 0, 0, height },
                { { 0, 27, height }, { 32, 1, 98 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 15), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
    }
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::centre, direction, 38, height, session.SupportColours);
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
/** rct2: 0x008A4AFC */
static void SteeplechaseTrack25DegUpTo60DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 0), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 1), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 2), { 0, 0, height },
                { { 0, 27, height }, { 32, 1, 66 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 3), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 4), { 0, 0, height },
                { { 0, 27, height }, { 32, 1, 66 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 5), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
    }
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::centre, direction, 18, height, session.SupportColours);
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

/** rct2: 0x008A4B0C */
static void SteeplechaseTrack60DegUpTo25DegUp(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    switch (direction)
    {
        case 0:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 6), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
        case 1:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 7), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 8), { 0, 0, height },
                { { 0, 27, height }, { 32, 1, 66 } });
            break;
        case 2:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 9), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 10), { 0, 0, height },
                { { 0, 27, height }, { 32, 1, 66 } });
            break;
        case 3:
            PaintAddImageAsParentRotated(
                session, direction, session.TrackColours.WithIndex(SPR_TRACKS_STEEPLECHASE_RC_STEEP_SLOPES + 11), { 0, 0, height },
                { { 0, 6, height }, { 32, 20, 3 } });
            break;
    }
    if (TrackPaintUtilShouldPaintSupports(session.MapPosition))
    {
        MetalASupportsPaintSetupRotated(
            session, supportType.metal, MetalSupportPlace::centre, direction, 26, height, session.SupportColours);
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
/** rct2: 0x008A4B3C */
static void SteeplechaseTrack60DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrack60DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}
/** rct2: 0x008A4B5C */
static void SteeplechaseTrack25DegDownTo60DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrack60DegUpTo25DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

/** rct2: 0x008A4B6C */
static void SteeplechaseTrack60DegDownTo25DegDown(
    PaintSession& session, const Ride& ride, uint8_t trackSequence, uint8_t direction, int32_t height,
    const TrackElement& trackElement, SupportType supportType)
{
    SteeplechaseTrack25DegUpTo60DegUp(session, ride, trackSequence, (direction + 2) & 3, height, trackElement, supportType);
}

TrackPaintFunction GetTrackPaintFunctionSteeplechase(TrackElemType trackType)
{
    switch (trackType)
    {
        case TrackElemType::flat:
            return SteeplechaseTrackFlat;
        case TrackElemType::endStation:
        case TrackElemType::beginStation:
        case TrackElemType::middleStation:
            return SteeplechaseTrackStation;
        case TrackElemType::up25:
            return SteeplechaseTrack25DegUp;
        case TrackElemType::flatToUp25:
            return SteeplechaseTrackFlatTo25DegUp;
        case TrackElemType::up25ToFlat:
            return SteeplechaseTrack25DegUpToFlat;
        case TrackElemType::down25:
            return SteeplechaseTrack25DegDown;
        case TrackElemType::flatToDown25:
            return SteeplechaseTrackFlatTo25DegDown;
        case TrackElemType::down25ToFlat:
            return SteeplechaseTrack25DegDownToFlat;
        case TrackElemType::leftQuarterTurn5Tiles:
            return SteeplechaseTrackLeftQuarterTurn5;
        case TrackElemType::rightQuarterTurn5Tiles:
            return SteeplechaseTrackRightQuarterTurn5;
        case TrackElemType::sBendLeft:
            return SteeplechaseTrackSBendLeft;
        case TrackElemType::sBendRight:
            return SteeplechaseTrackSBendRight;
        case TrackElemType::leftQuarterTurn3Tiles:
            return SteeplechaseTrackLeftQuarterTurn3;
        case TrackElemType::rightQuarterTurn3Tiles:
            return SteeplechaseTrackRightQuarterTurn3;
        case TrackElemType::brakes:
            return SteeplechaseTrackBrakes;
        case TrackElemType::leftEighthToDiag:
            return SteeplechaseTrackLeftEighthToDiag;
        case TrackElemType::rightEighthToDiag:
            return SteeplechaseTrackRightEighthToDiag;
        case TrackElemType::leftEighthToOrthogonal:
            return SteeplechaseTrackLeftEighthToOrthogonal;
        case TrackElemType::rightEighthToOrthogonal:
            return SteeplechaseTrackRightEighthToOrthogonal;
        case TrackElemType::diagFlat:
            return SteeplechaseTrackDiagFlat;
        case TrackElemType::diagUp25:
            return SteeplechaseTrackDiag25DegUp;
        case TrackElemType::diagFlatToUp25:
            return SteeplechaseTrackDiagFlatTo25DegUp;
        case TrackElemType::diagUp25ToFlat:
            return SteeplechaseTrackDiag25DegUpToFlat;
        case TrackElemType::diagDown25:
            return SteeplechaseTrackDiag25DegDown;
        case TrackElemType::diagFlatToDown25:
            return SteeplechaseTrackDiagFlatTo25DegDown;
        case TrackElemType::diagDown25ToFlat:
            return SteeplechaseTrackDiag25DegDownToFlat;
        case TrackElemType::blockBrakes:
            return SteeplechaseTrackBlockBrakes;
        case TrackElemType::diagBrakes:
        case TrackElemType::diagBlockBrakes:
            return SteeplechaseTrackDiagBrakes;
        case TrackElemType::leftQuarterHelixLargeUp:
            return OpenRCT2::trackPaintLeftQuarterHelixLargeUp<
                SPR_TRACKS_STEEPLECHASE_TRACK_QUARTER_HELIX_LEFT, OpenRCT2::kLeftQuarterHelixLargeUpSpriteMap, false,
                kLeftQuarterHelixSupportHeights, OpenRCT2::BlockedSegmentsType::narrow, kTunnelGroup, false>;
        case TrackElemType::rightQuarterHelixLargeUp:
            return OpenRCT2::trackPaintRightQuarterHelixLargeUp<
                SPR_TRACKS_STEEPLECHASE_TRACK_QUARTER_HELIX_RIGHT, OpenRCT2::kRightQuarterHelixLargeUpSpriteMap, false,
                kRightQuarterHelixSupportHeights, OpenRCT2::BlockedSegmentsType::narrow, kTunnelGroup, false>;
        case TrackElemType::leftQuarterHelixLargeDown:
            return OpenRCT2::trackPaintLeftQuarterHelixLargeDown<
                SPR_TRACKS_STEEPLECHASE_TRACK_QUARTER_HELIX_RIGHT, OpenRCT2::kRightQuarterHelixLargeUpSpriteMap, false,
                kRightQuarterHelixSupportHeights, OpenRCT2::BlockedSegmentsType::narrow, kTunnelGroup, false>;
        case TrackElemType::rightQuarterHelixLargeDown:
            return OpenRCT2::trackPaintRightQuarterHelixLargeDown<
                SPR_TRACKS_STEEPLECHASE_TRACK_QUARTER_HELIX_LEFT, OpenRCT2::kLeftQuarterHelixLargeUpSpriteMap, false,
                kLeftQuarterHelixSupportHeights, OpenRCT2::BlockedSegmentsType::narrow, kTunnelGroup, false>;
        case TrackElemType::up60:
            return SteeplechaseTrack60DegUp;
        case TrackElemType::up25ToUp60:
            return SteeplechaseTrack25DegUpTo60DegUp;
        case TrackElemType::up60ToUp25:
            return SteeplechaseTrack60DegUpTo25DegUp;
        case TrackElemType::down60:
            return SteeplechaseTrack60DegDown;
        case TrackElemType::down25ToDown60:
            return SteeplechaseTrack25DegDownTo60DegDown;
        case TrackElemType::down60ToDown25:
            return SteeplechaseTrack60DegDownTo25DegDown;
        case TrackElemType::flatToUp60:
            return SteeplechaseTrackFlatTo60DegUp;
        case TrackElemType::up60ToFlat:
            return SteeplechaseTrack60DegUpToFlat;
        case TrackElemType::flatToDown60:
            return SteeplechaseTrackFlatTo60DegDown;
        case TrackElemType::down60ToFlat:
            return SteeplechaseTrack60DegDownToFlat;
        case TrackElemType::flatToUp60LongBase:
            return SteeplechaseTrackFlatTo60DegUpLongBase;
        case TrackElemType::up60ToFlatLongBase:
            return SteeplechaseTrack60DegUpToFlatLongBase;
        case TrackElemType::flatToDown60LongBase:
            return SteeplechaseTrackFlatTo60DegDownLongBase;
        case TrackElemType::down60ToFlatLongBase:
            return SteeplechaseTrack60DegDownToFlatLongBase;
        case TrackElemType::diagUp60:
            return SteeplechaseTrackDiag60DegUp;
        case TrackElemType::diagUp25ToUp60:
            return SteeplechaseTrackDiag25DegUpTo60DegUp;
        case TrackElemType::diagUp60ToUp25:
            return SteeplechaseTrackDiag60DegUpTo25DegUp;
        case TrackElemType::diagDown60:
            return SteeplechaseTrackDiag60DegDown;
        case TrackElemType::diagDown25ToDown60:
            return SteeplechaseTrackDiag25DegDownTo60DegDown;
        case TrackElemType::diagDown60ToDown25:
            return SteeplechaseTrackDiag60DegDownTo25DegDown;
        case TrackElemType::diagFlatToUp60:
            return SteeplechaseTrackDiagFlatTo60DegUp;
        case TrackElemType::diagUp60ToFlat:
            return SteeplechaseTrackDiag60DegUpToFlat;
        case TrackElemType::diagFlatToDown60:
            return SteeplechaseTrackDiagFlatTo60DegDown;
        case TrackElemType::diagDown60ToFlat:
            return SteeplechaseTrackDiag60DegDownToFlat;
        case TrackElemType::diagFlatToUp60LongBase:
            return SteeplechaseTrackDiagFlatTo60DegUpLongBase;
        case TrackElemType::diagUp60ToFlatLongBase:
            return SteeplechaseTrackDiag60DegUpToFlatLongBase;
        case TrackElemType::diagFlatToDown60LongBase:
            return SteeplechaseTrackDiagFlatTo60DegDownLongBase;
        case TrackElemType::diagDown60ToFlatLongBase:
            return SteeplechaseTrackDiag60DegDownToFlatLongBase;
        case TrackElemType::leftQuarterTurn1Tile:
            return SteeplechaseTrackLeftQuarterTurn1;
        case TrackElemType::rightQuarterTurn1Tile:
            return SteeplechaseTrackRightQuarterTurn1;
        case TrackElemType::leftQuarterTurn5TilesUp25:
            return SteeplechaseTrackLeftQuarterTurn525DegUp;
        case TrackElemType::rightQuarterTurn5TilesUp25:
            return SteeplechaseTrackRightQuarterTurn525DegUp;
        case TrackElemType::leftQuarterTurn5TilesDown25:
            return SteeplechaseTrackLeftQuarterTurn525DegDown;
        case TrackElemType::rightQuarterTurn5TilesDown25:
            return SteeplechaseTrackRightQuarterTurn525DegDown;
        case TrackElemType::leftQuarterTurn3TilesUp25:
            return SteeplechaseTrackLeftQuarterTurn325DegUp;
        case TrackElemType::rightQuarterTurn3TilesUp25:
            return SteeplechaseTrackRightQuarterTurn325DegUp;
        case TrackElemType::leftQuarterTurn3TilesDown25:
            return SteeplechaseTrackLeftQuarterTurn325DegDown;
        case TrackElemType::rightQuarterTurn3TilesDown25:
            return SteeplechaseTrackRightQuarterTurn325DegDown;
        case TrackElemType::leftEighthToDiagUp25:
            return SteeplechaseTrackLeftEighthToDiagUp25;
        case TrackElemType::rightEighthToDiagUp25:
            return SteeplechaseTrackRightEighthToDiagUp25;
        case TrackElemType::leftEighthToDiagDown25:
            return SteeplechaseTrackLeftEighthToDiagDown25;
        case TrackElemType::rightEighthToDiagDown25:
            return SteeplechaseTrackRightEighthToDiagDown25;
        case TrackElemType::leftEighthToOrthogonalUp25:
            return SteeplechaseTrackLeftEighthToOrthogonalUp25;
        case TrackElemType::rightEighthToOrthogonalUp25:
            return SteeplechaseTrackRightEighthToOrthogonalUp25;
        case TrackElemType::leftEighthToOrthogonalDown25:
            return SteeplechaseTrackLeftEighthToOrthogonalDown25;
        case TrackElemType::rightEighthToOrthogonalDown25:
            return SteeplechaseTrackRightEighthToOrthogonalDown25;
        default:
            return TrackPaintFunctionDummy;
    }
}
