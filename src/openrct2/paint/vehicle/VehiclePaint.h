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
}

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
