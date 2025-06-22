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

#include <microwave_oven_control/ameba_microwave_oven_control_delegate.h>
#include <microwave_oven_control/ameba_microwave_oven_control_manager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;

namespace {
static MicrowaveOvenControl::AmebaMicrowaveOvenControlDelegate * gAmebaMicrowaveOvenControlDelegate;
static MicrowaveOvenControl::Instance * gAmebaMicrowaveOvenControlInstance;
} // namespace

MicrowaveOvenControl::AmebaMicrowaveOvenControlDelegate * MicrowaveOvenControl::GetDelegate(void)
{
    return gAmebaMicrowaveOvenControlDelegate;
}

void MicrowaveOvenControl::SetDelegate(AmebaMicrowaveOvenControlDelegate * delegate)
{
    gAmebaMicrowaveOvenControlDelegate = delegate;
}

MicrowaveOvenControl::Instance * MicrowaveOvenControl::GetInstance(void)
{
    return gAmebaMicrowaveOvenControlInstance;
}

void MicrowaveOvenControl::SetInstance(Instance * instance)
{
    gAmebaMicrowaveOvenControlInstance = instance;
}

void MicrowaveOvenControl::Shutdown(void)
{
    if (gAmebaMicrowaveOvenControlDelegate != nullptr) {
        delete gAmebaMicrowaveOvenControlDelegate;
        gAmebaMicrowaveOvenControlDelegate = nullptr;
    }

    if (gAmebaMicrowaveOvenControlInstance != nullptr) {
        delete gAmebaMicrowaveOvenControlInstance;
        gAmebaMicrowaveOvenControlInstance = nullptr;
    }
}
