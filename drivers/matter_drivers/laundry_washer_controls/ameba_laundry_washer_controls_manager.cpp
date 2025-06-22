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

#include <laundry_washer_controls/ameba_laundry_washer_controls_delegate.h>
#include <laundry_washer_controls/ameba_laundry_washer_controls_manager.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::LaundryWasherControls;

static AmebaLaundryWasherControlsDelegate * gAmebaLaundryWasherControlsDelegate = nullptr;

LaundryWasherControls::AmebaLaundryWasherControlsDelegate * LaundryWasherControls::GetDelegate(void)
{
    return gAmebaLaundryWasherControlsDelegate;
}

void LaundryWasherControls::SetDelegate(AmebaLaundryWasherControlsDelegate * delegate)
{
    gAmebaLaundryWasherControlsDelegate = delegate;
}

void LaundryWasherControls::Shutdown(void)
{
    delete gAmebaLaundryWasherControlsDelegate;
    gAmebaLaundryWasherControlsDelegate = nullptr;
}
