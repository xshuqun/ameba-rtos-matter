/*
 *    This module is a confidential and proprietary property of RealTek and
 *    possession or use of this module requires written permission of RealTek.
 *
 *    Copyright(c) 2025, Realtek Semiconductor Corporation. All rights reserved.
 *
 *    Licensed under the Apache License, Version 2.0 (the "License");
 *    you may not use this file except in compliance with the License.
 *    You may obtain a copy of the License at
 *
 *        http://www.apache.org/licenses/LICENSE-2.0
 *
 *    Unless required by applicable law or agreed to in writing, software
 *    distributed under the License is distributed on an "AS IS" BASIS,
 *    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *    See the License for the specific language governing permissions and
 *    limitations under the License.
 */

#include <app/CommandHandler.h>
#include <app/clusters/occupancy-sensor-server/occupancy-hal.h>
#include <app/clusters/occupancy-sensor-server/occupancy-sensor-server.h>
#include <app/util/attribute-storage.h>
#include <occupancy_sensing/ameba_occupancy_sensing_manager.h>
#include <platform/CHIPDeviceLayer.h>

using namespace chip;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::OccupancySensing;
using namespace chip::app::Clusters::OccupancySensing::Structs;
using namespace chip::DeviceLayer;

using chip::Protocols::InteractionModel::Status;

namespace {
static OccupancySensing::Instance * gAmebaOccupancySensingInstances = nullptr;
} // namespace

Instance * OccupancySensing::GetOccupancySensingInstance(void)
{
    return gAmebaOccupancySensingInstances;
}

void OccupancySensing::SetOccupancySensingInstance(Instance * instance)
{
    gAmebaOccupancySensingInstances = instance;
}

void OccupancySensing::Shutdown(void)
{
    if (gAmebaOccupancySensingInstances != nullptr) {
        delete gAmebaOccupancySensingInstances;
        gAmebaOccupancySensingInstances = nullptr;
    }
}

CHIP_ERROR OccupancySensing::AmebaOccupancySensingInit(EndpointId endpointId)
{
    VerifyOrDie(gAmebaOccupancySensingInstances != nullptr);

    OccupancySensing::Structs::HoldTimeLimitsStruct::Type holdTimeLimits = {
        .holdTimeMin     = 1,
        .holdTimeMax     = 300,
        .holdTimeDefault = 10,
    };

    uint16_t holdTime = 10;
    CHIP_ERROR ret;

    ret = SetHoldTimeLimits(endpointId, holdTimeLimits);
    VerifyOrReturnError(ret != CHIP_NO_ERROR, ret);
    ret = SetHoldTime(endpointId, holdTime);
    VerifyOrReturnError(ret != CHIP_NO_ERROR, ret);
}
