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
#include <rvc_run_mode/ameba_rvc_run_mode_manager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::RvcRunMode;
using chip::Protocols::InteractionModel::Status;

static AmebaRvcRunModeDelegate * gAmebaRvcRunModeDelegate = nullptr;
static ModeBase::Instance * gAmebaRvcRunModeInstance     = nullptr;

RvcRunMode::AmebaRvcRunModeDelegate * RvcRunMode::GetDelegate()
{
    return gAmebaRvcRunModeDelegate;
}

void RvcRunMode::SetDelegate(AmebaRvcRunModeDelegate * delegate)
{
    VerifyOrDie(gAmebaRvcRunModeDelegate == nullptr);
    gAmebaRvcRunModeDelegate = delegate;
}

ModeBase::Instance * RvcRunMode::GetInstance(void)
{
    return gAmebaRvcRunModeInstance;
}

void RvcRunMode::SetInstance(ModeBase::Instance * instance)
{
    gAmebaRvcRunModeInstance = instance;
}

void RvcRunMode::Shutdown(void)
{
    if (gAmebaRvcRunModeInstance != nullptr)
    {
        delete gAmebaRvcRunModeInstance;
        gAmebaRvcRunModeInstance = nullptr;
    }
    if (gAmebaRvcRunModeDelegate != nullptr)
    {
        delete gAmebaRvcRunModeDelegate;
        gAmebaRvcRunModeDelegate = nullptr;
    }
}
