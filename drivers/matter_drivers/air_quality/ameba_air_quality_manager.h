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
#pragma once

#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/clusters/air-quality-server/air-quality-server.h>

namespace chip {
namespace app {
namespace Clusters {
namespace AirQuality {

// Returns a pointer to the current AirQuality cluster instance
Instance * GetAirQualityInstance(void);

// Sets the AirQuality cluster instance to the provided pointer
void SetAirQualityInstance(Instance * instance);

// Updates the current air quality state to the new value specified by aNewAirQuality
void SetAirQuality(AirQualityEnum aNewAirQuality);

// Retrieves the current air quality state as an enum value
AirQualityEnum CurrentAirQuality(void);

// Performs shutdown or cleanup operations related to the AirQuality cluster
void Shutdown(void);

} // namespace AirQuality
} // namespace Clusters
} // namespace app
} // namespace chip

