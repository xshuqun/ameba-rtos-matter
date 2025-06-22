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

#include <ameba_app_cluster_main.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;

// Action Cluster
void emberAfActionsClusterInitCallback(EndpointId endpoint)
{
    VerifyOrReturn(Actions::GetActionsServer() == nullptr && Actions::GetActionsDelegate() == nullptr);

    auto delegate = std::make_unique<Actions::AmebaActionsDelegateImpl>();
    auto * server   = new Actions::ActionsServer(endpoint, *delegate.get());

    server->Init();

    // Set global instances
    Actions::SetActionsDelegate(delegate.get());
    Actions::SetActionsServer(server);
}

void emberAfActionsClusterShutdownCallback(EndpointId endpoint)
{
    auto * server = Actions::GetActionsServer();
    if (server != nullptr)
    {
        server->Shutdown();
    }

    Actions::SetActionsServer(nullptr);
    Actions::SetActionsDelegate(nullptr);
}

// AirQuality Cluster
void emberAfAirQualityClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(AirQuality::GetInstance() == nullptr);

    chip::BitMask<AirQuality::Feature, uint32_t> Features(
        AirQuality::Feature::kModerate,
        AirQuality::Feature::kFair,
        AirQuality::Feature::kVeryPoor,
        AirQuality::Feature::kExtremelyPoor);

    auto * instance = new AirQuality::Instance(endpointId, Features);

    AirQuality::SetInstance(instance);

    instance->Init();
}

// DishwasherAlarm
void emberAfDishwasherAlarmClusterInitCallback(chip::EndpointId endpoint)
{
    static DishwasherAlarm::AmebaDishwasherAlarmDelegate delegate;
    DishwasherAlarm::SetDefaultDelegate(endpoint, &delegate);

    CHIP_ERROR ret;
    ret = DishwasherAlarm::AmebaDishWasherInit(endpoint);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaDishWasherInit Failed");
    }
}

// Resource Monitoring - Activated Carbon Filter Cluster Cluster
void emberAfActivatedCarbonFilterMonitoringClusterInitCallback(chip::EndpointId endpoint)
{
    VerifyOrReturn(endpoint == 1,
                   ChipLogError(Zcl, "Activated Carbon Filter is not implemented for endpoint %d.", endpoint));

    VerifyOrDie(ActivatedCarbonFilterMonitoring::GetInstance() == nullptr);
    VerifyOrDie(ActivatedCarbonFilterMonitoring::GetDelegate() == nullptr);

    constexpr std::bitset<4> Features{
        static_cast<uint32_t>(ResourceMonitoring::Feature::kCondition)
    };

    auto * delegate = new ActivatedCarbonFilterMonitoring::AmebaActivatedCarbonFilterMonitoringDelegate;

    ActivatedCarbonFilterMonitoring::SetDelegate(delegate);

    auto * instance = new ResourceMonitoring::Instance(
        delegate,
        endpoint,
        ActivatedCarbonFilterMonitoring::Id,
        static_cast<uint32_t>(Features.to_ulong()),
        ResourceMonitoring::DegradationDirectionEnum::kDown,
        true);

    ActivatedCarbonFilterMonitoring::SetInstance(instance);

    instance->Init();
}

// Resource Monitoring - HEPA Filter Monitoring Cluster
void emberAfHepaFilterMonitoringClusterInitCallback(chip::EndpointId endpoint)
{
    VerifyOrReturn(endpoint == 1,
                   ChipLogError(Zcl, "Activated Carbon Filter is not implemented for endpoint %d.", endpoint));
    VerifyOrDie(HepaFilterMonitoring::GetInstance() == nullptr);
    VerifyOrDie(HepaFilterMonitoring::GetDelegate() == nullptr);

    constexpr std::bitset<4> Features{
        static_cast<uint32_t>(ResourceMonitoring::Feature::kCondition)
    };

    auto * delegate = new HepaFilterMonitoring::AmebaHepaFilterMonitoringDelegate;

    HepaFilterMonitoring::SetDelegate(delegate);

    auto * instance = new ResourceMonitoring::Instance(
        delegate,
        endpoint,
        HepaFilterMonitoring::Id,
        static_cast<uint32_t>(Features.to_ulong()),
        ResourceMonitoring::DegradationDirectionEnum::kDown,
        true);

    HepaFilterMonitoring::SetInstance(instance);

    instance->Init();
}
