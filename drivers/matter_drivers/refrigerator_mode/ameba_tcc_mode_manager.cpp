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

#include <app-common/zap-generated/attributes/Accessors.h>
#include <refrigerator_mode/ameba_tcc_mode_manager.h>

using namespace chip::app::Clusters;
using namespace chip::app::Clusters::RefrigeratorAndTemperatureControlledCabinetMode;
using chip::Protocols::InteractionModel::Status;

static AmebaTccModeDelegate * gAmebaTccModeDelegate = nullptr;
static ModeBase::Instance * gAmebaTccModeInstance     = nullptr;

RefrigeratorAndTemperatureControlledCabinetMode::AmebaTccModeDelegate * RefrigeratorAndTemperatureControlledCabinetMode::GetDelegate()
{
    return gAmebaTccModeDelegate;
}

void RefrigeratorAndTemperatureControlledCabinetMode::SetDelegate(AmebaTccModeDelegate * delegate)
{
    VerifyOrDie(gAmebaTccModeDelegate == nullptr);
    gAmebaTccModeDelegate = delegate;
}

ModeBase::Instance * RefrigeratorAndTemperatureControlledCabinetMode::GetInstance(void)
{
    return gAmebaTccModeInstance;
}

void RefrigeratorAndTemperatureControlledCabinetMode::SetInstance(ModeBase::Instance * instance)
{
    gAmebaTccModeInstance = instance;
}

void RefrigeratorAndTemperatureControlledCabinetMode::Shutdown(void)
{
    if (gAmebaTccModeInstance != nullptr)
    {
        delete gAmebaTccModeInstance;
        gAmebaTccModeInstance = nullptr;
    }
    if (gAmebaTccModeDelegate != nullptr)
    {
        delete gAmebaTccModeDelegate;
        gAmebaTccModeDelegate = nullptr;
    }
}
