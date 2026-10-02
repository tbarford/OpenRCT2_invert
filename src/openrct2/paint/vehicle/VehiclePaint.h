/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#pragma once

#include "../../ride/Angles.h"
#include "../../ride/ted/TrackElemType.h"

#include <cstdint>

struct PaintSession;
struct CarEntry;

namespace OpenRCT2
{
    struct Vehicle;
    struct VehicleInfo;
} // namespace OpenRCT2

struct VehicleBoundBox
{
    int8_t offset_x;
    int8_t offset_y;
    int8_t offset_z;
    uint8_t length_x;
    uint8_t length_y;
    uint8_t length_z;
};

extern const VehicleBoundBox VehicleBoundboxes[16][224];

/**
 * Inverted cars are drawn with their car entry's inverted sprite set, except at the poses below, which have always
 * been drawn with the upright set. The pitch and roll are the drawn ones, after reversed cars have been mirrored.
 * - Flat, banked 67 degrees or more, or at an uninverting roll.
 * - Pitched down 75 or 90 degrees, other than on vertical drop track.
 * - Pitched down past vertical, at an uninverting pitch, or at a corkscrew frame.
 */
bool InvertedCarDrawsWithUprightSet(OpenRCT2::TrackElemType trackType, VehiclePitch pitch, VehicleRoll roll);

/** Whether a car is drawn with its car entry's inverted sprite set at its current pose. */
bool VehicleUsesInvertedCarSet(const OpenRCT2::Vehicle& vehicle);

/** The pose, car set and height offset a car is drawn with. */
struct VehiclePaintPose
{
    uint8_t yaw;
    VehiclePitch pitch;
    VehicleRoll roll;
    bool usesInvertedCarSet;
    int32_t zOffset;
};

/**
 * The same pose rolled half a turn about the rail; the inverted car set draws each pose this way. A banked pose keeps
 * its yaw and pitch and banks to the other side. An unbanked pose turns round and pitches over the top.
 */
VehiclePaintPose HalfRoll(const VehiclePaintPose& pose);

/**
 * A flyer car on a standard inversion moves along the sit-down coaster's subposition samples, so physics matches the
 * sit-down coaster on the same track. It is drawn from the same samples:
 * - With the set it entered with until the sample has turned over (rolled past a quarter turn, or pitched past
 *   vertical) relative to the element's first sample, then with the other set. Corkscrew frames keep the entry set.
 * - In the sample's pose with the inverted set, and that pose rolled half a turn with the upright set: in the
 *   default direction the car is inverted where the sit-down car is upright.
 * - 16 units up in either state, as on the legacy flyer-only elements.
 * Matches the legacy elements that copy a standard inversion in its default direction, sample for sample.
 */
VehiclePaintPose GetFlyerPoseOnStandardSample(
    const OpenRCT2::VehicleInfo& sample, const OpenRCT2::VehicleInfo& firstSample, bool enteredInverted);

/**
 * The pose a car is drawn with: its own pose and car set, raised for inverted cars, except for flyer cars on standard
 * inversions (see GetFlyerPoseOnStandardSample). Paint only: the vehicle's own pose is game state.
 */
VehiclePaintPose GetVehiclePaintPose(const OpenRCT2::Vehicle& vehicle);

void VehicleVisualDefault(
    PaintSession& session, int32_t imageDirection, int32_t z, const OpenRCT2::Vehicle* vehicle, const CarEntry* carEntry);
void VehicleVisualSplashEffect(PaintSession& session, int32_t z, const OpenRCT2::Vehicle* vehicle, const CarEntry* carEntry);

namespace OpenRCT2
{
    void VehicleVisualRotoDrop(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
    void VehicleVisualObservationTower(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
    void VehicleVisualRiverRapids(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
    void VehicleVisualReverser(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
    void VehicleVisualSplashBoatsOrWaterCoaster(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
    void VehicleVisualLaunchedFreefall(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
    void VehicleVisualVirginiaReel(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
    void VehicleVisualSubmarine(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
    void VehicleVisualMiniGolfPlayer(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle);
    void VehicleVisualMiniGolfBall(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle);
    void VehicleVisualClassicMiniSpinning(
        PaintSession& session, int32_t x, int32_t imageDirection, int32_t y, int32_t z, const OpenRCT2::Vehicle* vehicle,
        const CarEntry* carEntry);
} // namespace OpenRCT2
