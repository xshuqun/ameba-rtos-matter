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
#include <dishwasher_mode/ameba_dishwasher_mode_manager.h>

using namespace chip::app::Clusters;
using namespace chip::app::Clusters::DishwasherMode;
using chip::Protocols::InteractionModel::Status;

static AmebaDishwasherModeDelegate * gAmebaDishwasherModeDelegate = nullptr;
static ModeBase::Instance * gAmebaDishwasherModeInstance     = nullptr;

DishwasherMode::AmebaDishwasherModeDelegate * DishwasherMode::GetDishwasherModeDelegate()
{
    return gAmebaDishwasherModeDelegate;
}

void DishwasherMode::SetDishwasherModeDelegate(AmebaDishwasherModeDelegate * delegate)
{
    VerifyOrDie(gAmebaDishwasherModeDelegate == nullptr);
    gAmebaDishwasherModeDelegate = delegate;
}

ModeBase::Instance * DishwasherMode::GetDishwasherModeInstance(void)
{
    return gAmebaDishwasherModeInstance;
}

void DishwasherMode::SetDishwasherModeInstance(ModeBase::Instance * instance)
{
    gAmebaDishwasherModeInstance = instance;
}

void DishwasherMode::Shutdown(void)
{
    if (gAmebaDishwasherModeInstance != nullptr)
    {
        delete gAmebaDishwasherModeInstance;
        gAmebaDishwasherModeInstance = nullptr;
    }
    if (gAmebaDishwasherModeDelegate != nullptr)
    {
        delete gAmebaDishwasherModeDelegate;
        gAmebaDishwasherModeDelegate = nullptr;
    }
}
