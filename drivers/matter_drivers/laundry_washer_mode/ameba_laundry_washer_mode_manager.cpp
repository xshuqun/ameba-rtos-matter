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
#include <laundry_washer_mode/ameba_laundry_washer_mode_manager.h>

using namespace chip::app::Clusters;
using namespace chip::app::Clusters::LaundryWasherMode;
using chip::Protocols::InteractionModel::Status;

static AmebaLaundryWasherModeDelegate * gAmebaLaundryWasherModeDelegate = nullptr;
static ModeBase::Instance * gAmebaLaundryWasherModeInstance     = nullptr;

LaundryWasherMode::AmebaLaundryWasherModeDelegate * LaundryWasherMode::GetLaundryWasherModeDelegate(void)
{
    return gAmebaLaundryWasherModeDelegate;
}

void LaundryWasherMode::SetLaundryWasherModeDelegate(AmebaLaundryWasherModeDelegate * delegate)
{
    VerifyOrDie(gAmebaLaundryWasherModeDelegate == nullptr);
    gAmebaLaundryWasherModeDelegate = delegate;
}

ModeBase::Instance * LaundryWasherMode::GetLaundryWasherModeInstance(void)
{
    return gAmebaLaundryWasherModeInstance;
}

void LaundryWasherMode::SetLaundryWasherModeInstance(ModeBase::Instance * instance)
{
    gAmebaLaundryWasherModeInstance = instance;
}

void LaundryWasherMode::Shutdown(void)
{
    if (gAmebaLaundryWasherModeInstance != nullptr)
    {
        delete gAmebaLaundryWasherModeInstance;
        gAmebaLaundryWasherModeInstance = nullptr;
    }
    if (gAmebaLaundryWasherModeDelegate != nullptr)
    {
        delete gAmebaLaundryWasherModeDelegate;
        gAmebaLaundryWasherModeDelegate = nullptr;
    }
}
