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

#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/clusters/resource-monitoring-server/resource-monitoring-cluster-objects.h>
#include <app/clusters/resource-monitoring-server/resource-monitoring-server.h>
#include <resource_monitoring/ameba_resource_monitoring_delegate.h>
#include <resource_monitoring/ameba_resource_monitoring_manager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::ResourceMonitoring;
using namespace chip::app::Clusters::ActivatedCarbonFilterMonitoring;
using namespace chip::app::Clusters::HepaFilterMonitoring;
using chip::Protocols::InteractionModel::Status;

AmebaActivatedCarbonFilterMonitoringDelegate * gActivatedCarbonFilterDelegate = nullptr;
ResourceMonitoring::Instance * gActivatedCarbonFilterInstance = nullptr;
AmebaHepaFilterMonitoringDelegate * gHepaFilterDelegate = nullptr;
ResourceMonitoring::Instance * gHepaFilterInstance = nullptr;

//-- Activated Carbon Filter Monitoring delegate methods
Instance * ActivatedCarbonFilterMonitoring::GetInstance()
{
    return gActivatedCarbonFilterInstance;
}

void ActivatedCarbonFilterMonitoring::SetInstance(Instance * instance)
{
    gActivatedCarbonFilterInstance = instance;
}

ActivatedCarbonFilterMonitoring::AmebaActivatedCarbonFilterMonitoringDelegate * ActivatedCarbonFilterMonitoring::GetDelegate()
{
    return gActivatedCarbonFilterDelegate;
}

void ActivatedCarbonFilterMonitoring::SetDelegate(AmebaActivatedCarbonFilterMonitoringDelegate * delegate)
{
    VerifyOrDie(gActivatedCarbonFilterDelegate == nullptr);
    gActivatedCarbonFilterDelegate = delegate;
}

void ActivatedCarbonFilterMonitoring::SetCondition(uint8_t value)
{
    Status status;
    if (GetInstance() != nullptr)
    {
        status = GetInstance()->UpdateCondition(value);
        if (status != Status::Success)
        {
            ChipLogProgress(DeviceLayer, "Update Condition Failed");
        }
        else
        {
            ChipLogProgress(DeviceLayer, "Update Condition to %d", value);
        }
    }
}

void ActivatedCarbonFilterMonitoring::SetChangeIndication(ResourceMonitoring::ChangeIndicationEnum aNewChangeIndication)
{
    Status status;
    if (GetInstance() != nullptr)
    {
        status = GetInstance()->UpdateChangeIndication(aNewChangeIndication);
        if (status != Status::Success)
        {
            ChipLogProgress(DeviceLayer, "Change Indication Failed");
        }
        else
        {
            ChipLogProgress(DeviceLayer, "Change Indication to %d", aNewChangeIndication);
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

// HEPA Filter Monitoring methods
Instance * HepaFilterMonitoring::GetInstance()
{
    return gHepaFilterInstance;
}

void HepaFilterMonitoring::SetInstance(Instance * instance)
{
    gHepaFilterInstance = instance;
}

HepaFilterMonitoring::AmebaHepaFilterMonitoringDelegate * HepaFilterMonitoring::GetDelegate()
{
    return gHepaFilterDelegate;
}

void HepaFilterMonitoring::SetDelegate(AmebaHepaFilterMonitoringDelegate * delegate)
{
    VerifyOrDie(gHepaFilterDelegate == nullptr);
    gHepaFilterDelegate = delegate;
}

void HepaFilterMonitoring::SetCondition(uint8_t value)
{
    Status status;
    if (GetInstance() != nullptr)
    {
        status = GetInstance()->UpdateCondition(value);
        if (status != Status::Success)
        {
            ChipLogProgress(DeviceLayer, "Update Condition Failed");
        }
        else
        {
            ChipLogProgress(DeviceLayer, "Update Condition to %d", value);
        }
    }
}

void HepaFilterMonitoring::SetChangeIndication(ResourceMonitoring::ChangeIndicationEnum aNewChangeIndication)
{
    Status status;
    if (GetInstance() != nullptr)
    {
        status = GetInstance()->UpdateChangeIndication(aNewChangeIndication);
        if (status != Status::Success)
        {
            ChipLogProgress(DeviceLayer, "Change Indication Failed");
        }
        else
        {
            ChipLogProgress(DeviceLayer, "Change Indication to %d", aNewChangeIndication);
        }
    }
}

void HepaFilterMonitoring::Shutdown()
{
    if (gHepaFilterInstance != nullptr)
    {
        delete gHepaFilterInstance;
        gHepaFilterInstance = nullptr;
    }
    if (gHepaFilterDelegate != nullptr)
    {
        delete gHepaFilterDelegate;
        gHepaFilterDelegate = nullptr;
    }
}
