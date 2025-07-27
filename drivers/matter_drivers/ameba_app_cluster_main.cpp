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
    CHIP_ERROR ret = CHIP_NO_ERROR;

    ret = Actions::AmebaActionsDelegateInit(endpoint);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaActionsDelegateInit Failed");
        return;
    }

    ret = Actions::AmebaActionsServerInit(endpoint);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaActionsServerInit Failed");
        return;
    }
}

void emberAfActionsClusterShutdownCallback(EndpointId endpoint)
{
    Actions::AmebaActionsServerShutdown();
    Actions::AmebaActionsDelegateShutdown();
}

// Air Quality Cluster
void emberAfAirQualityClusterInitCallback(chip::EndpointId endpointId)
{
    CHIP_ERROR ret = CHIP_NO_ERROR;

    ret = AirQuality::AmebaAirQualityInstanceInit(endpointId);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaAirQualityInstanceInit Failed");
        return;
    }
}

void emberAfAirQualityClusterShutdownCallback(EndpointId endpoint)
{
    AirQuality::AmebaAirQualityInstanceShutdown();
}

// Dishwasher Alarm Cluster
void emberAfDishwasherAlarmClusterInitCallback(chip::EndpointId endpoint)
{
    CHIP_ERROR ret = CHIP_NO_ERROR;

    ret = DishwasherAlarm::AmebaDishWasherAlarmDelegateInit(endpoint);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaDishWasherAlarmDelegateInit Failed");
        return;
    }

    ret = DishwasherAlarm::AmebaDishWasherAlarmInstanceInit(endpoint);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaDishWasherAlarmInstanceInit Failed");
        return;
    }
}

// Dishwasher Mode Cluster
void emberAfDishwasherModeClusterInitCallback(chip::EndpointId endpointId)
{
    CHIP_ERROR ret = CHIP_NO_ERROR;

    ret = DishwasherMode::AmebaDishwasherModeDelegateInit(endpointId);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaDishwasherModeDelegateInit Failed");
        return;
    }

    ret = DishwasherMode::AmebaDishwasherModeInstanceInit(endpointId);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaDishwasherModeInstanceInit Failed");
        return;
    }
}

void emberAfDishwasherModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    DishwasherMode::AmebaDishwasherModeInstanceShutdown();
    DishwasherMode::AmebaDishwasherModeDelegateShutdown();
}

// Fan Control Cluster
void emberAfFanControlClusterInitCallback(EndpointId endpoint)
{
    CHIP_ERROR ret = CHIP_NO_ERROR;

    ret = FanControl::AmebaFanControlDelegateInit(endpoint);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaFanControlDelegateInit Failed");
        return;
    }
}

// Laundry Dryer Controls Cluster
void emberAfLaundryDryerControlsClusterInitCallback(EndpointId endpoint)
{
    CHIP_ERROR ret = CHIP_NO_ERROR;

    ret = LaundryDryerControls::AmebaLaundryDryerControlsDelegateInit(endpoint);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaLaundryDryerControlsDelegateInit Failed");
        return;
    }
}

void emberAfLaundryDryerControlsClusterShutdownCallback(EndpointId endpoint)
{
    LaundryDryerControls::AmebaLaundryDryerControlsDelegateShutdown();
}

// Laundry Washer Controls Cluster
void emberAfLaundryWasherControlsClusterInitCallback(EndpointId endpoint)
{
CHIP_ERROR ret = CHIP_NO_ERROR;

    ret = LaundryWasherControls::AmebaLaundryWasherControlsDelegateInit(endpoint);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaLaundryWasherControlsDelegateInit Failed");
        return;
    }
}

void emberAfLaundryWasherControlsClusterShutdownCallback(EndpointId endpoint)
{
    LaundryWasherControls::AmebaLaundryWasherControlsDelegateShutdown();
}

// Laundry Washer Mode Cluster
void emberAfLaundryWasherModeClusterInitCallback(chip::EndpointId endpointId)
{
    CHIP_ERROR ret = CHIP_NO_ERROR;

    ret = LaundryWasherMode::AmebaLaundryWasherModeDelegateInit(endpointId);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaLaundryWasherModeDelegateInit Failed");
        return;
    }

    ret = LaundryWasherMode::AmebaLaundryWasherModeInstanceInit(endpointId);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaLaundryWasherModeInstanceInit Failed");
        return;
    }

}

void emberAfLaundryWasherModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    LaundryWasherMode::AmebaLaundryWasherModeInstanceShutdown();
    LaundryWasherMode::AmebaLaundryWasherModeDelegateShutdown();
}

// Microwave Oven Control Cluster
void emberAfMicrowaveOvenControlClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(MicrowaveOvenControl::GetMicrowaveOvenControlInstance() == nullptr);
    VerifyOrDie(MicrowaveOvenControl::GetMicrowaveOvenControlDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    if (OperationalState::GetOperationalStateInstance() == nullptr ||
        OperationalState::GetOperationalStateDelegate() == nullptr)
    {
        auto * opstateDelegate = new OperationalState::AmebaOperationalStateDelegate;
        OperationalState::SetOperationalStateDelegate(opstateDelegate);
        auto * opstateInstance = new OperationalState::Instance(opstateDelegate, endpointId);
        opstateInstance->Init();
        OperationalState::SetOperationalStateInstance(opstateInstance);
    }

    if (MicrowaveOvenMode::GetMicrowaveOvenModeInstance() == nullptr ||
        MicrowaveOvenMode::GetMicrowaveOvenModeDelegate() == nullptr)
    {
        auto * modeDelegate = new MicrowaveOvenMode::AmebaMicrowaveOvenModeDelegate;
        MicrowaveOvenMode::SetMicrowaveOvenModeDelegate(modeDelegate);
        auto * modeInstance = new ModeBase::Instance(modeDelegate, endpointId, MicrowaveOvenMode::Id, 0x0);
        MicrowaveOvenMode::SetMicrowaveOvenModeInstance(modeInstance);
        modeInstance->Init();
    }

    // Microwave Oven Control Delegate and Instance
    auto * ctrlDelegate = new MicrowaveOvenControl::AmebaMicrowaveOvenControlDelegate;
    MicrowaveOvenControl::SetMicrowaveOvenControlDelegate(ctrlDelegate);

    auto * ctrlInstance = new MicrowaveOvenControl::Instance(
        ctrlDelegate,
        endpointId,
        MicrowaveOvenControl::Id,
        chip::BitMask<MicrowaveOvenControl::Feature>(
            MicrowaveOvenControl::Feature::kPowerAsNumber,
            MicrowaveOvenControl::Feature::kPowerNumberLimits),
        *OperationalState::GetOperationalStateInstance(),
        *MicrowaveOvenMode::GetMicrowaveOvenModeInstance());

    MicrowaveOvenControl::SetMicrowaveOvenControlInstance(ctrlInstance);

    ctrlInstance->Init();
}

void emberAfMicrowaveOvenControlClusterShutdownCallback(chip::EndpointId endpointId)
{
    MicrowaveOvenMode::Shutdown();
}

// Microwave Oven Mode Cluster
void emberAfMicrowaveOvenModeClusterInitCallback(chip::EndpointId endpointId)
{
    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    if (MicrowaveOvenMode::GetMicrowaveOvenModeInstance() == nullptr ||
        MicrowaveOvenMode::GetMicrowaveOvenModeDelegate() == nullptr)
    {
        auto * delegate = new MicrowaveOvenMode::AmebaMicrowaveOvenModeDelegate;
        MicrowaveOvenMode::SetMicrowaveOvenModeDelegate(delegate);
        auto * instance = new ModeBase::Instance(delegate, endpointId, MicrowaveOvenMode::Id, 0x0);
        MicrowaveOvenMode::SetMicrowaveOvenModeInstance(instance);
        instance->Init();
    }
}

void emberAfMicrowaveOvenModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (MicrowaveOvenMode::GetMicrowaveOvenModeInstance())
    {
        MicrowaveOvenMode::GetMicrowaveOvenModeInstance()->Shutdown();
    }
    MicrowaveOvenMode::Shutdown();
}

// Occupancry Sensing Cluster
void emberAfOccupancySensingClusterInitCallback(EndpointId endpointId)
{
    VerifyOrDie(OccupancySensing::GetOccupancySensingInstance() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    BitMask<OccupancySensing::Feature, uint32_t> Features(
        OccupancySensing::Feature::kPassiveInfrared);

    auto * instance = new OccupancySensing::Instance(Features);
    OccupancySensing::SetOccupancySensingInstance(instance);

    instance->Init();

    CHIP_ERROR ret;
    ret = OccupancySensing::AmebaOccupancySensingInit(endpointId);
    if (ret != CHIP_NO_ERROR)
    {
        ChipLogProgress(Zcl, "AmebaDishWasherInit Failed");
        VerifyOrDie(ret == CHIP_NO_ERROR);
    }

}

// Operational State Cluster
void emberAfOperationalStateClusterInitCallback(chip::EndpointId endpointId)
{
    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    if (OperationalState::GetOperationalStateInstance() == nullptr ||
        OperationalState::GetOperationalStateDelegate() == nullptr)
    {
        auto * delegate = new OperationalState::AmebaOperationalStateDelegate;
        OperationalState::SetOperationalStateDelegate(delegate);
        auto * instance = new OperationalState::Instance(delegate, endpointId);

        OperationalState::SetOperationalStateInstance(instance);

        instance->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kStopped));
        instance->Init();
    }
}

// Oven Mode Cluster
void emberAfOvenModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(OvenMode::GetOvenModeInstance() == nullptr && OvenMode::GetOvenModeDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    auto * delegate = new OvenMode::AmebaOvenModeDelegate;
    OvenMode::SetOvenModeDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, OvenMode::Id, 0x0);
    OvenMode::SetOvenModeInstance(instance);
    instance->Init();
}

void emberAfOvenModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (OvenMode::GetOvenModeInstance())
    {
        OvenMode::GetOvenModeInstance()->Shutdown();
    }
    OvenMode::Shutdown();
}

// Oven Cavity Operational State Cluster
void emberAfOvenCavityOperationalStateClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(OvenCavityOperationalState::GetOvenCavityOperationalStateInstance() == nullptr &&
                OvenCavityOperationalState::GetOvenCavityOperationalStateDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    auto * delegate = new OvenCavityOperationalState::AmebaOvenCavityOperationalStateDelegate;
    OvenCavityOperationalState::SetOvenCavityOperationalStateDelegate(delegate);

    auto * instance = new OvenCavityOperationalState::Instance(delegate, endpointId);
    OvenCavityOperationalState::SetOvenCavityOperationalStateInstance(instance);

    instance->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kStopped));
    instance->Init();
}


// Refrigerator And Temperature Controlled Cabinet (TCC) Mode Cluster
void emberAfRefrigeratorAndTemperatureControlledCabinetModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(RefrigeratorAndTemperatureControlledCabinetMode::GetRefrigeratorModeInstance() == nullptr &&
                RefrigeratorAndTemperatureControlledCabinetMode::GetRefrigeratorModeDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    auto * delegate = new RefrigeratorAndTemperatureControlledCabinetMode::AmebaRefrigeratorModeDelegate;
    RefrigeratorAndTemperatureControlledCabinetMode::SetRefrigeratorModeDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId,
                            RefrigeratorAndTemperatureControlledCabinetMode::Id, 0x0);
    RefrigeratorAndTemperatureControlledCabinetMode::SetRefrigeratorModeInstance(instance);
    instance->Init();
}

void emberAfRefrigeratorAndTemperatureControlledCabinetModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (RefrigeratorAndTemperatureControlledCabinetMode::GetRefrigeratorModeInstance())
    {
        RefrigeratorAndTemperatureControlledCabinetMode::GetRefrigeratorModeInstance()->Shutdown();
    }
    RefrigeratorAndTemperatureControlledCabinetMode::Shutdown();
}

// RVC Clean Mode Cluster
void emberAfRvcCleanModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(RvcCleanMode::GetRvcCleanModeInstance() == nullptr && RvcCleanMode::GetRvcCleanModeDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    auto * delegate = new RvcCleanMode::AmebaRvcCleanModeDelegate;
    RvcCleanMode::SetRvcCleanModeDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, RvcCleanMode::Id, 0x0);
    RvcCleanMode::SetRvcCleanModeInstance(instance);
    instance->Init();
}

void emberAfRvcCleanModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (RvcCleanMode::GetRvcCleanModeInstance())
    {
        RvcCleanMode::GetRvcCleanModeInstance()->Shutdown();
    }
    RvcCleanMode::Shutdown();
}

// RVC Operational Mode Cluster
void emberAfRvcOperationalStateClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(RvcOperationalState::GetRvcOperationalStateInstance() == nullptr &&
                RvcOperationalState::GetRvcOperationalStateDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    auto * delegate = new RvcOperationalState::AmebaRvcOperationalStateDelegate;
    RvcOperationalState::SetRvcOperationalStateDelegate(delegate);

    auto * instance = new RvcOperationalState::Instance(delegate, endpointId);
    RvcOperationalState::SetRvcOperationalStateInstance(instance);

    instance->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kStopped));
    instance->Init();

}

// RVC Run Mode Cluster
void emberAfRvcRunModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(RvcRunMode::GetRvcRunModeInstance() == nullptr && RvcRunMode::GetRvcRunModeDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    auto * delegate = new RvcRunMode::AmebaRvcRunModeDelegate;
    RvcRunMode::SetRvcRunModeDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, RvcRunMode::Id, 0x0);
    RvcRunMode::SetRvcRunModeInstance(instance);
    instance->Init();
}

void emberAfRvcRunModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (RvcRunMode::GetRvcRunModeInstance())
    {
        RvcRunMode::GetRvcRunModeInstance()->Shutdown();
    }
    RvcRunMode::Shutdown();
}

// Resource Monitoring - Activated Carbon Filter Cluster
void emberAfActivatedCarbonFilterMonitoringClusterInitCallback(chip::EndpointId endpoint)
{
    VerifyOrDie(ActivatedCarbonFilterMonitoring::GetActivatedCarbonInstance() == nullptr &&
                ActivatedCarbonFilterMonitoring::GetActivatedCarbonDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpoint);

    constexpr std::bitset<4> Features{
        static_cast<uint32_t>(ResourceMonitoring::Feature::kCondition)
    };

    auto * delegate = new ActivatedCarbonFilterMonitoring::AmebaActivatedCarbonFilterMonitoringDelegate;

    ActivatedCarbonFilterMonitoring::SetActivatedCarbonDelegate(delegate);

    auto * instance = new ResourceMonitoring::Instance(
        delegate,
        endpoint,
        ActivatedCarbonFilterMonitoring::Id,
        static_cast<uint32_t>(Features.to_ulong()),
        ResourceMonitoring::DegradationDirectionEnum::kDown,
        true);

    ActivatedCarbonFilterMonitoring::SetActivatedCarbonInstance(instance);

    instance->Init();
}

// Resource Monitoring - HEPA Filter Monitoring Cluster
void emberAfHepaFilterMonitoringClusterInitCallback(chip::EndpointId endpoint)
{
    VerifyOrDie(HepaFilterMonitoring::GetHepaInstance() == nullptr &&
                HepaFilterMonitoring::GetHepaDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpoint);

    constexpr std::bitset<4> Features{
        static_cast<uint32_t>(ResourceMonitoring::Feature::kCondition)
    };

    auto * delegate = new HepaFilterMonitoring::AmebaHepaFilterMonitoringDelegate;

    HepaFilterMonitoring::SetHepaDelegate(delegate);

    auto * instance = new ResourceMonitoring::Instance(
        delegate,
        endpoint,
        HepaFilterMonitoring::Id,
        static_cast<uint32_t>(Features.to_ulong()),
        ResourceMonitoring::DegradationDirectionEnum::kDown,
        true);

    HepaFilterMonitoring::SetHepaInstance(instance);

    instance->Init();
}

void emberAfWaterHeaterModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(WaterHeaterMode::GetWaterHeaterModeInstance() == nullptr &&
                WaterHeaterMode::GetWaterHeaterModeDelegate() == nullptr);

    ChipLogDetail(DeviceLayer,"%s on ep%d", __FUNCTION__, endpointId);

    auto * delegate = new WaterHeaterMode::AmebaWaterHeaterModeDelegate;
    WaterHeaterMode::SetWaterHeaterModeDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, WaterHeaterMode::Id, 0x0);
    WaterHeaterMode::SetWaterHeaterModeInstance(instance);
    instance->Init();
}

void emberAfWaterHeaterModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (WaterHeaterMode::GetWaterHeaterModeInstance())
    {
        WaterHeaterMode::GetWaterHeaterModeInstance()->Shutdown();
    }
    WaterHeaterMode::Shutdown();
}
