/*
 *    This module is a confidential and proprietary property of RealTek and
 *    possession or use of this module requires written permission of RealTek.
 *
 *    Copyright(c) 2024, Realtek Semiconductor Corporation. All rights reserved.
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
#include <air_quality/ameba_air_quality_manager.h>

using namespace chip::app::Clusters;
using namespace chip::app::Clusters::AirQuality;

namespace {

static Instance * gAirQualityInstance = nullptr;

} // anonymous namespace

Instance * AirQuality::GetInstance()
{
    return gAirQualityInstance;
}

void AirQuality::SetInstance(Instance * instance)
{
    gAirQualityInstance = instance;
}

void AirQuality::SetAirQuality(AirQualityEnum aNewAirQuality)
{
    if (gAirQualityInstance != nullptr) {
        ChipLogProgress(DeviceLayer, "Update AirQuality to 0x%x", aNewAirQuality);
        gAirQualityInstance->UpdateAirQuality(aNewAirQuality);
    }
}

AirQualityEnum AirQuality::CurrentAirQuality(void)
{
    if (gAirQualityInstance != nullptr) {
        return gAirQualityInstance->GetAirQuality();
    }
    return AirQualityEnum::kUnknown;
}

void AirQuality::Shutdown(void)
{
    if (gAirQualityInstance != nullptr) {
        delete gAirQualityInstance;
        gAirQualityInstance = nullptr;
    }
}
