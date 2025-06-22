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
#include <oven_mode/ameba_oven_mode_manager.h>

using namespace chip::app::Clusters;
using namespace chip::app::Clusters::OvenMode;
using chip::Protocols::InteractionModel::Status;

static AmebaOvenModeDelegate * gAmebaOvenModeDelegate = nullptr;
static ModeBase::Instance * gAmebaOvenModeInstance     = nullptr;

OvenMode::AmebaOvenModeDelegate * OvenMode::GetDelegate()
{
    return gAmebaOvenModeDelegate;
}

void OvenMode::SetDelegate(AmebaOvenModeDelegate * delegate)
{
    VerifyOrDie(gAmebaOvenModeDelegate == nullptr);
    gAmebaOvenModeDelegate = delegate;
}

ModeBase::Instance * OvenMode::GetInstance(void)
{
    return gAmebaOvenModeInstance;
}

void OvenMode::SetInstance(ModeBase::Instance * instance)
{
    gAmebaOvenModeInstance = instance;
}

void OvenMode::Shutdown(void)
{
    if (gAmebaOvenModeInstance != nullptr)
    {
        delete gAmebaOvenModeInstance;
        gAmebaOvenModeInstance = nullptr;
    }
    if (gAmebaOvenModeDelegate != nullptr)
    {
        delete gAmebaOvenModeDelegate;
        gAmebaOvenModeDelegate = nullptr;
    }
}
