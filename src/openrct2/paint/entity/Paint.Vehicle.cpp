/*****************************************************************************
 * Copyright (c) 2014-2026 OpenRCT2 developers
 *
 * For a complete list of all authors, please refer to contributors.md
 * Interested in contributing? Visit https://github.com/OpenRCT2/OpenRCT2
 *
 * OpenRCT2 is licensed under the GNU General Public License version 3.
 *****************************************************************************/

#include "Paint.Vehicle.h"

#include "../../SpriteIds.h"
#include "../../entity/Yaw.hpp"
#include "../../paint/vehicle/VehiclePaint.h"
#include "../../ride/RideData.h"
#include "../Paint.h"

#include <optional>

using namespace OpenRCT2;

void PaintVehicle(PaintSession& session, const Vehicle& vehicle, int32_t imageDirection)
{
    const CarEntry* carEntry;

    if (vehicle.flags.has(VehicleFlag::crashed))
    {
        PaintAddImageAsParent(
            session, ImageId(SPR_WATER_PARTICLES_DENSE_0 + vehicle.animation_frame), { 0, 0, vehicle.z },
            { { 0, 0, vehicle.z + 2 }, { 1, 1, 0 } });
        return;
    }

    int32_t zOffset = 0;
    const Vehicle* drawnVehicle = &vehicle;
    std::optional<Vehicle> posedVehicle;
    if (vehicle.IsCableLift())
    {
        carEntry = &kCableLiftVehicle;
    }
    else
    {
        auto rideEntry = vehicle.GetRideEntry();
        if (rideEntry == nullptr)
        {
            return;
        }

        auto carEntryIndex = vehicle.vehicle_type;
        const auto pose = GetVehiclePaintPose(vehicle);
        zOffset += pose.zOffset;
        if (pose.usesInvertedCarSet)
        {
            carEntryIndex++;
        }

        // Draw a copy in the drawn pose; the vehicle's own pose is game state
        if (pose.yaw != vehicle.orientation || pose.pitch != vehicle.pitch || pose.roll != vehicle.roll)
        {
            posedVehicle.emplace(vehicle);
            posedVehicle->orientation = pose.yaw;
            posedVehicle->pitch = pose.pitch;
            posedVehicle->roll = pose.roll;
            drawnVehicle = &*posedVehicle;
            imageDirection = (imageDirection - vehicle.orientation + pose.yaw) & (Entity::Yaw::kBaseRotation - 1);
        }

        if (carEntryIndex >= std::size(rideEntry->Cars))
        {
            return;
        }
        carEntry = &rideEntry->Cars[carEntryIndex];
    }

    switch (carEntry->paintStyle)
    {
        case VehiclePaintStyle::standard:
            VehicleVisualDefault(session, imageDirection, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::launchedFreefall:
            VehicleVisualLaunchedFreefall(
                session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::observationTower:
            VehicleVisualObservationTower(
                session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::riverRapids:
            VehicleVisualRiverRapids(
                session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::miniGolfPlayer:
            VehicleVisualMiniGolfPlayer(session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle);
            break;
        case VehiclePaintStyle::miniGolfBall:
            VehicleVisualMiniGolfBall(session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle);
            break;
        case VehiclePaintStyle::reverser:
            VehicleVisualReverser(session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::splashBoatsOrWaterCoaster:
            VehicleVisualSplashBoatsOrWaterCoaster(
                session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::rotoDrop:
            VehicleVisualRotoDrop(session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::virginiaReel:
            VehicleVisualVirginiaReel(
                session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::submarine:
            VehicleVisualSubmarine(session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        case VehiclePaintStyle::spinningCars:
            VehicleVisualClassicMiniSpinning(
                session, vehicle.x, imageDirection, vehicle.y, vehicle.z + zOffset, drawnVehicle, carEntry);
            break;
        default:
            break;
    }
}
