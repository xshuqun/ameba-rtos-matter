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

// Air Quality Cluster
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

// Dishwasher Alarm Cluster
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

// Dishwasher Mode Cluster
void emberAfDishwasherModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(DishwasherMode::GetInstance() == nullptr);
    VerifyOrDie(DishwasherMode::GetDelegate() == nullptr);

    auto * delegate = new DishwasherMode::AmebaDishwasherModeDelegate;
    DishwasherMode::SetDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, DishwasherMode::Id, 0x0);
    DishwasherMode::SetInstance(instance);
    instance->Init();
}

void emberAfDishwasherModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (DishwasherMode::GetInstance())
    {
        DishwasherMode::GetInstance()->Shutdown();
    }
    DishwasherMode::Shutdown();
}

// Fan Control Cluster
void emberAfFanControlClusterInitCallback(EndpointId endpoint)
{
    auto * delegate = new FanControl::AmebaFanControlDelegate(endpoint);
    AttributeAccessInterfaceRegistry::Instance().Register(delegate);
    FanControl::SetDefaultDelegate(endpoint, delegate);
}

// Laundry Dryer Controls Cluster
void emberAfLaundryDryerControlsClusterInitCallback(EndpointId endpoint)
{
    auto * delegate = new LaundryDryerControls::AmebaLaundryDryerControlsDelegate();
    LaundryDryerControls::SetDelegate(delegate);
    LaundryDryerControls::LaundryDryerControlsServer::SetDefaultDelegate(endpoint, delegate);
}

void emberAfLaundryDryerControlsClusterShutdownCallback(EndpointId endpoint)
{
    LaundryDryerControls::Shutdown();
}

// Laundry Washer Controls Cluster
void emberAfLaundryWasherControlsClusterInitCallback(EndpointId endpoint)
{
    auto * delegate = new LaundryWasherControls::AmebaLaundryWasherControlsDelegate();
    LaundryWasherControls::SetDelegate(delegate);
    LaundryWasherControls::LaundryWasherControlsServer::SetDefaultDelegate(endpoint, delegate);
}

void emberAfLaundryWasherControlsClusterShutdownCallback(EndpointId endpoint)
{
    LaundryWasherControls::Shutdown();
}

// Laundry Washer Mode Cluster
void emberAfLaundryWasherModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(LaundryWasherMode::GetInstance() == nullptr);
    VerifyOrDie(LaundryWasherMode::GetDelegate() == nullptr);

    auto * delegate = new LaundryWasherMode::AmebaLaundryWasherModeDelegate;
    LaundryWasherMode::SetDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, LaundryWasherMode::Id, 0x0);
    LaundryWasherMode::SetInstance(instance);
    instance->Init();
}

void emberAfLaundryWasherModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (LaundryWasherMode::GetInstance())
    {
        LaundryWasherMode::GetInstance()->Shutdown();
    }
    LaundryWasherMode::Shutdown();
}

// Microwave Oven Control Cluster
void emberAfMicrowaveOvenControlClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(MicrowaveOvenControl::GetInstance() == nullptr);
    VerifyOrDie(MicrowaveOvenControl::GetDelegate() == nullptr);

    if (OperationalState::GetOperationalStateInstance() == nullptr ||
        OperationalState::GetOperationalStateDelegate() == nullptr)
    {
        auto * opstateDelegate = new OperationalState::OperationalStateDelegate;
        OperationalState::SetOperationalStateDelegate(opstateDelegate);
        auto * opstateInstance = new OperationalState::Instance(opstateDelegate, endpointId);
        opstateInstance->Init();
        OperationalState::SetOperationalStateInstance(opstateInstance);
    }

    if (MicrowaveOvenMode::GetInstance() == nullptr || MicrowaveOvenMode::GetDelegate() == nullptr)
    {
        auto * modeDelegate = new MicrowaveOvenMode::AmebaMicrowaveOvenModeDelegate;
        MicrowaveOvenMode::SetDelegate(modeDelegate);
        auto * modeInstance = new ModeBase::Instance(modeDelegate, endpointId, MicrowaveOvenMode::Id, 0x0);
        MicrowaveOvenMode::SetInstance(modeInstance);
        modeInstance->Init();
    }

    // Microwave Oven Control Delegate and Instance
    auto * ctrlDelegate = new MicrowaveOvenControl::AmebaMicrowaveOvenControlDelegate;
    MicrowaveOvenControl::SetDelegate(ctrlDelegate);

    auto * ctrlInstance = new MicrowaveOvenControl::Instance(
        ctrlDelegate,
        endpointId,
        MicrowaveOvenControl::Id,
        chip::BitMask<MicrowaveOvenControl::Feature>(
            MicrowaveOvenControl::Feature::kPowerAsNumber,
            MicrowaveOvenControl::Feature::kPowerNumberLimits),
        *OperationalState::GetOperationalStateInstance(),
        *MicrowaveOvenMode::GetInstance());

    MicrowaveOvenControl::SetInstance(ctrlInstance);

    ctrlInstance->Init();
}

void emberAfMicrowaveOvenControlClusterShutdownCallback(chip::EndpointId endpointId)
{
}

// Microwave Oven Mode Cluster
void emberAfMicrowaveOvenModeClusterInitCallback(chip::EndpointId endpointId)
{
    if (MicrowaveOvenMode::GetInstance() == nullptr || MicrowaveOvenMode::GetDelegate() == nullptr)
    {
        auto * delegate = new MicrowaveOvenMode::AmebaMicrowaveOvenModeDelegate;
        MicrowaveOvenMode::SetDelegate(delegate);
        auto * instance = new ModeBase::Instance(delegate, endpointId, MicrowaveOvenMode::Id, 0x0);
        MicrowaveOvenMode::SetInstance(instance);
        instance->Init();
    }
}

void emberAfMicrowaveOvenModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (MicrowaveOvenMode::GetInstance())
    {
        MicrowaveOvenMode::GetInstance()->Shutdown();
    }
    MicrowaveOvenMode::Shutdown();
}

// Operational State Cluster
void emberAfOperationalStateClusterInitCallback(chip::EndpointId endpointId)
{
    if (OperationalState::GetOperationalStateInstance() == nullptr ||
        OperationalState::GetOperationalStateDelegate() == nullptr)
    {
        auto * delegate = new OperationalState::OperationalStateDelegate;
        OperationalState::SetOperationalStateDelegate(delegate);
        auto * instance = new OperationalState::Instance(delegate, endpointId);

        OperationalState::SetOperationalStateInstance(instance);

        OperationalState::GetOperationalStateInstance()->SetOperationalState(to_underlying(OperationalState::OperationalStateEnum::kStopped));

        instance->Init();
    }
}


// Oven Mode Cluster
void emberAfOvenModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(OvenMode::GetInstance() == nullptr);
    VerifyOrDie(OvenMode::GetDelegate() == nullptr);

    auto * delegate = new OvenMode::AmebaOvenModeDelegate;
    OvenMode::SetDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, OvenMode::Id, 0x0);
    OvenMode::SetInstance(instance);
    instance->Init();
}

void emberAfOvenModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (OvenMode::GetInstance())
    {
        OvenMode::GetInstance()->Shutdown();
    }
    OvenMode::Shutdown();
}

// Refrigerator And Temperature Controlled Cabinet (TCC) Mode Cluster
void emberAfRefrigeratorAndTemperatureControlledCabinetModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(RefrigeratorAndTemperatureControlledCabinetMode::GetInstance() == nullptr);
    VerifyOrDie(RefrigeratorAndTemperatureControlledCabinetMode::GetDelegate() == nullptr);

    auto * delegate = new RefrigeratorAndTemperatureControlledCabinetMode::AmebaTccModeDelegate;
    RefrigeratorAndTemperatureControlledCabinetMode::SetDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId,
                            RefrigeratorAndTemperatureControlledCabinetMode::Id, 0x0);
    RefrigeratorAndTemperatureControlledCabinetMode::SetInstance(instance);
    instance->Init();
}

void emberAfRefrigeratorAndTemperatureControlledCabinetModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (RefrigeratorAndTemperatureControlledCabinetMode::GetInstance())
    {
        RefrigeratorAndTemperatureControlledCabinetMode::GetInstance()->Shutdown();
    }
    RefrigeratorAndTemperatureControlledCabinetMode::Shutdown();
}

// RVC Clean Mode Cluster
void emberAfRvcCleanModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(RvcCleanMode::GetInstance() == nullptr);
    VerifyOrDie(RvcCleanMode::GetDelegate() == nullptr);

    auto * delegate = new RvcCleanMode::AmebaRvcCleanModeDelegate;
    RvcCleanMode::SetDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, RvcCleanMode::Id, 0x0);
    RvcCleanMode::SetInstance(instance);
    instance->Init();
}

void emberAfRvcCleanModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (RvcCleanMode::GetInstance())
    {
        RvcCleanMode::GetInstance()->Shutdown();
    }
    RvcCleanMode::Shutdown();
}

// RVC Run Mode Cluster
void emberAfRvcRunModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(RvcRunMode::GetInstance() == nullptr);
    VerifyOrDie(RvcRunMode::GetDelegate() == nullptr);

    auto * delegate = new RvcRunMode::AmebaRvcRunModeDelegate;
    RvcRunMode::SetDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, RvcRunMode::Id, 0x0);
    RvcRunMode::SetInstance(instance);
    instance->Init();
}

void emberAfRvcRunModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (RvcRunMode::GetInstance())
    {
        RvcRunMode::GetInstance()->Shutdown();
    }
    RvcRunMode::Shutdown();
}

// Resource Monitoring - Activated Carbon Filter Cluster
void emberAfActivatedCarbonFilterMonitoringClusterInitCallback(chip::EndpointId endpoint)
{
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

void emberAfWaterHeaterModeClusterInitCallback(chip::EndpointId endpointId)
{
    VerifyOrDie(WaterHeaterMode::GetInstance() == nullptr);
    VerifyOrDie(WaterHeaterMode::GetDelegate() == nullptr);

    auto * delegate = new WaterHeaterMode::AmebaWaterHeaterModeDelegate;
    WaterHeaterMode::SetDelegate(delegate);
    auto * instance = new ModeBase::Instance(delegate, endpointId, WaterHeaterMode::Id, 0x0);
    WaterHeaterMode::SetInstance(instance);
    instance->Init();
}

void emberAfWaterHeaterModeClusterShutdownCallback(chip::EndpointId endpointId)
{
    if (WaterHeaterMode::GetInstance())
    {
        WaterHeaterMode::GetInstance()->Shutdown();
    }
    WaterHeaterMode::Shutdown();
}
