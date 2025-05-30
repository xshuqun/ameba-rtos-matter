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
#include <ameba_app_cluster_init.h>
#include <app/clusters/air-quality-server/air-quality-server.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;

// AirQuality
void emberAfAirQualityClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(endpointId == 1);
    VerifyOrDie(AirQuality::GetInstance() == nullptr);

    chip::BitMask<AirQuality::Feature, uint32_t> airQualityFeatures(
        AirQuality::Feature::kModerate,
        AirQuality::Feature::kFair,
        AirQuality::Feature::kVeryPoor,
        AirQuality::Feature::kExtremelyPoor);

    auto * instance = new AirQuality::Instance(endpointId, airQualityFeatures);

    AirQuality::SetInstance(instance);

    instance->Init();
}

// Resource Monitoring - Activated Carbon Filter

void emberAfActivatedCarbonFilterMonitoringClusterInitCallback(chip::EndpointId endpoint)
{
    VerifyOrDie(ActivatedCarbonFilterMonitoring::GetInstance() == nullptr);
    VerifyOrDie(ActivatedCarbonFilterMonitoring::GetDelegate() == nullptr);

    constexpr std::bitset<4> ActivatedCarbonFeature{ 
        static_cast<uint32_t>(ResourceMonitoring::Feature::kCondition)
    };

    auto * delegate = new ActivatedCarbonFilterMonitoring::ActivatedCarbonFilterMonitoringDelegate;

    ActivatedCarbonFilterMonitoring::SetDelegate(delegate);

    auto * instance = new ResourceMonitoring::Instance(
        delegate,
        endpoint,
        ActivatedCarbonFilterMonitoring::Id,
        static_cast<uint32_t>(ActivatedCarbonFeature.to_ulong()),
        ResourceMonitoring::DegradationDirectionEnum::kDown,
        true);

    ActivatedCarbonFilterMonitoring::SetInstance(instance);

    instance->Init();
}
#if 0
// Resource Monitoring - HEPA Filter Monitoring

constexpr std::bitset<4> gHepaFilterFeatureMap{ static_cast<uint32_t>(ResourceMonitoring::Feature::kCondition)};

void emberAfHepaFilterMonitoringClusterInitCallback(chip::EndpointId endpoint)
{
    VerifyOrDie(gHepaFilterInstance == nullptr && gHepaFilterDelegate == nullptr);

    gHepaFilterDelegate = new HepaFilterMonitoringDelegate;
    gHepaFilterInstance = new ResourceMonitoring::Instance(gHepaFilterDelegate, endpoint, HepaFilterMonitoring::Id,
                                                           static_cast<uint32_t>(gHepaFilterFeatureMap.to_ulong()),
                                                           ResourceMonitoring::DegradationDirectionEnum::kDown, true);
    gHepaFilterInstance->Init();
}
#endif
