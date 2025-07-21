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

#pragma once

#include <microwave_oven_mode/ameba_microwave_oven_mode_delegate.h>
#include <app/clusters/mode-base-server/mode-base-server.h>

namespace chip {
namespace app {
namespace Clusters {

namespace MicrowaveOvenMode {

class AmebaMicrowaveOvenModeDelegate;

AmebaMicrowaveOvenModeDelegate * GetMicrowaveOvenModeDelegate(void);
void SetMicrowaveOvenModeDelegate(AmebaMicrowaveOvenModeDelegate * delegate);
ModeBase::Instance * GetMicrowaveOvenModeInstance(void);
void SetMicrowaveOvenModeInstance(ModeBase::Instance * instance);

void Shutdown(void);

} // namespace MicrowaveOvenMode

} // namespace Clusters
} // namespace app
} // namespace chip
