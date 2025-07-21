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

#include <app/clusters/laundry-washer-controls-server/laundry-washer-controls-delegate.h>
#include <app/clusters/laundry-washer-controls-server/laundry-washer-controls-server.h>

namespace chip {
namespace app {
namespace Clusters {

namespace LaundryWasherControls {

class AmebaLaundryWasherControlsDelegate;

AmebaLaundryWasherControlsDelegate * GetLaundryWasherControlsDelegate(void);
void SetLaundryWasherControlsDelegate(AmebaLaundryWasherControlsDelegate * delegate);
void Shutdown(void);

} // namespace LaundryWasherControls

} // namespace Clusters
} // namespace app
} // namespace chip
