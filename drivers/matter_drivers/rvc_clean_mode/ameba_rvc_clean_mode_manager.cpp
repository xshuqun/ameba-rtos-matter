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
#include <rvc_clean_mode/ameba_rvc_clean_mode_manager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::RvcCleanMode;
using chip::Protocols::InteractionModel::Status;

static AmebaRvcCleanModeDelegate * gAmebaRvcCleanModeDelegate = nullptr;
static ModeBase::Instance * gAmebaRvcCleanModeInstance     = nullptr;

RvcCleanMode::AmebaRvcCleanModeDelegate * RvcCleanMode::GetRvcCleanModeDelegate(void)
{
    return gAmebaRvcCleanModeDelegate;
}

void RvcCleanMode::SetRvcCleanModeDelegate(AmebaRvcCleanModeDelegate * delegate)
{
    VerifyOrDie(gAmebaRvcCleanModeDelegate == nullptr);
    gAmebaRvcCleanModeDelegate = delegate;
}

ModeBase::Instance * RvcCleanMode::GetRvcCleanModeInstance(void)
{
    return gAmebaRvcCleanModeInstance;
}

void RvcCleanMode::SetRvcCleanModeInstance(ModeBase::Instance * instance)
{
    gAmebaRvcCleanModeInstance = instance;
}

void RvcCleanMode::Shutdown(void)
{
    if (gAmebaRvcCleanModeInstance != nullptr)
    {
        delete gAmebaRvcCleanModeInstance;
        gAmebaRvcCleanModeInstance = nullptr;
    }
    if (gAmebaRvcCleanModeDelegate != nullptr)
    {
        delete gAmebaRvcCleanModeDelegate;
        gAmebaRvcCleanModeDelegate = nullptr;
    }
}
