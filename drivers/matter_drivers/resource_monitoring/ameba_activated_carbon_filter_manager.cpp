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
#include <resource_monitoring/ameba_activated_carbon_filter_manager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::ResourceMonitoring;
using namespace chip::app::Clusters::ActivatedCarbonFilterMonitoring;
using chip::Protocols::InteractionModel::Status;

namespace {

static ActivatedCarbonFilterMonitoringDelegate * gActivatedCarbonFilterDelegate = nullptr;
static ResourceMonitoring::Instance * gActivatedCarbonFilterInstance            = nullptr;

} // anonymous namespace

// Activated Carbon Filter Monitoring
Instance * ActivatedCarbonFilterMonitoring::GetInstance()
{
    return gActivatedCarbonFilterInstance;
}

void ActivatedCarbonFilterMonitoring::SetInstance(Instance * instance)
{
    gActivatedCarbonFilterInstance = instance;
}

ActivatedCarbonFilterMonitoring::ActivatedCarbonFilterMonitoringDelegate * ActivatedCarbonFilterMonitoring::GetDelegate()
{
    return gActivatedCarbonFilterDelegate;
}

void ActivatedCarbonFilterMonitoring::SetDelegate(ActivatedCarbonFilterMonitoringDelegate * delegate)
{
    VerifyOrDie(gActivatedCarbonFilterDelegate == nullptr);
    gActivatedCarbonFilterDelegate = delegate;
}

void ActivatedCarbonFilterMonitoring::SetCondition(uint8_t value)
{
    Status status;
    if (GetInstance() != nullptr) {
        status = GetInstance()->UpdateCondition(value);
        if (status != Status::Success) {
            ChipLogProgress(DeviceLayer, "Update Condition Failed");
        } else {
            ChipLogProgress(DeviceLayer, "Update Condition to %d%", value);
        }
    }
}

void ActivatedCarbonFilterMonitoring::SetChangeIndication(ResourceMonitoring::ChangeIndicationEnum aNewChangeIndication)
{
    Status status;
    if (GetInstance() != nullptr) {
        status = GetInstance()->UpdateChangeIndication(aNewChangeIndication);
        if (status != Status::Success) {
            ChipLogProgress(DeviceLayer, "Change Indication Failed");
        } else {
            ChipLogProgress(DeviceLayer, "Change Indication to %d%", aNewChangeIndication);
        }
    }
}

void ActivatedCarbonFilterMonitoring::Shutdown()
{
    if (gActivatedCarbonFilterInstance != nullptr)
    {
        delete gActivatedCarbonFilterInstance;
        gActivatedCarbonFilterInstance = nullptr;
    }
    if (gActivatedCarbonFilterDelegate != nullptr)
    {
        delete gActivatedCarbonFilterDelegate;
        gActivatedCarbonFilterDelegate = nullptr;
    }
}

CHIP_ERROR ActivatedCarbonFilterMonitoringDelegate::Init()
{
    return CHIP_NO_ERROR;
}

Status ActivatedCarbonFilterMonitoringDelegate::PreResetCondition()
{
    return Status::Success;
}

Status ActivatedCarbonFilterMonitoringDelegate::PostResetCondition()
{
    return Status::Success;
}
