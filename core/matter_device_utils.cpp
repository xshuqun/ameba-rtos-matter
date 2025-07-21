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

#include <platform_stdlib.h>
#include <reset_reason_api.h>

#include <app/server/Server.h>
#include <credentials/DeviceAttestationCredsProvider.h>
#include <platform/Ameba/DiagnosticDataProviderImpl.h>
#include <platform/CHIPDeviceLayer.h>
#include <platform/CommissionableDataProvider.h>
#include <platform/DeviceInstanceInfoProvider.h>
#include <setup_payload/OnboardingCodesUtil.h>
#include <setup_payload/QRCodeSetupPayloadGenerator.h>

#include <matter_api.h>
#include <matter_ota.h>

#ifdef __cplusplus
extern "C" {
#endif

#if defined(CONFIG_ENABLE_AMEBA_OPHOURS) && (CONFIG_ENABLE_AMEBA_OPHOURS == 1)
#define HOUR_PER_MILLISECOND       ( 3600 * 1000 )
#endif

using namespace ::chip;
using namespace ::chip::Credentials;
using namespace ::chip::DeviceLayer;
using namespace ::chip::app::Clusters;

using BootReasonType = GeneralDiagnostics::BootReasonEnum;

uint8_t matter_get_total_operational_hour(uint32_t *totalOperationalHours)
{
    if (totalOperationalHours == nullptr)
    {
        ChipLogError(DeviceLayer,"%s: nullptr\n", __FUNCTION__);
        return -1;
    }

    CHIP_ERROR err;
    DiagnosticDataProvider &diagProvider = chip::DeviceLayer::GetDiagnosticDataProviderImpl();

    if (&diagProvider != nullptr)
    {
        err = diagProvider.GetTotalOperationalHours(*totalOperationalHours);
        if (err != CHIP_NO_ERROR)
        {
            ChipLogError(DeviceLayer,"%s: get failed err=%d\n", __FUNCTION__, err);
            return -1;
        }
    }
    else
    {
        printf("%s: DiagnosticDataProvider is invalid\n", __FUNCTION__);
        return -1;
    }
    return 0;
}

uint8_t matter_set_total_operational_hour(uint32_t time)
{
    CHIP_ERROR err = ConfigurationMgr().StoreTotalOperationalHours(time);

    return (err == CHIP_NO_ERROR) ? 0 : -1;
}

void matter_store_boot_reason(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    uint32_t reason = hal_reset_reason_get();
    uint8_t is_ota = matter_get_ota_completed_value();

    BootReasonType bootReason;
    /* BootReasonEnum
     * 0: kUnspecified               > RESET_REASON_UNKNOWN
     * 1: kPowerOnReboot             > RESET_REASON_POWER_ON
     * 2: kBrownOutReset             > RESET_REASON_BROWN_OUT
     * 3: kSoftwareWatchdogReset     > RESET_REASON_WATCHDOG
     * 4: kHardwareWatchdogReset     > Not supported
     * 5: kSoftwareUpdateCompleted   > RESET_REASON_SOFTWARE + is_ota(1)
     * 6: kSoftwareReset             > RESET_REASON_SOFTWARE
     * */
    switch (reason)
    {
    case RESET_REASON_POWER_ON:
        bootReason = BootReasonType::kPowerOnReboot;
        break;
    case RESET_REASON_BROWN_OUT:
        bootReason = BootReasonType::kBrownOutReset;
        break;
    case RESET_REASON_WATCHDOG:
        bootReason = BootReasonType::kHardwareWatchdogReset;
        break;
    case RESET_REASON_SOFTWARE:
        if (!is_ota)
        {
            bootReason = BootReasonType::kSoftwareReset;
        }
        else
        {
            bootReason = BootReasonType::kSoftwareUpdateCompleted;
        }
        break;
    case RESET_REASON_UNKNOWN:
    default:
        bootReason = BootReasonType::kUnspecified;
        break;
    }

    ChipLogDetail(DeviceLayer, "store boot reason 0x%x", to_underlying(bootReason));

    err = ConfigurationManagerImpl().StoreBootReason(to_underlying(bootReason));
    if (err != CHIP_NO_ERROR)
    {
        ChipLogError(DeviceLayer, "store boot reason (0x%x) failed 0x%X", to_underlying(bootReason), err);
    }
    return;
}

#if defined(CONFIG_ENABLE_AMEBA_OPHOURS) && (CONFIG_ENABLE_AMEBA_OPHOURS == 1)
static void matter_op_hours_task(void *pvParameters)
{
    uint32_t cur_hour = 0, prev_hour = 0;
    uint8_t ret = 0;
    char key[] = "temp_hour";

    // 1. Check if "temp_hour" exist in NVS
    if (checkExist(key, key) != true)
    {
        // 2. If "temp_hour" exist, get "temp_hour" and set as "total_hour" into NVS
        if (getPref_u32_new(key, key, &prev_hour) == DCT_SUCCESS)
        {
            ret = matter_set_total_operational_hour(prev_hour);
            if (ret != 0)
            {
                ChipLogError(DeviceLayer,"matter_store_total_operational_hour failed, ret=%d\n", ret);
                goto loop;
            }
            // 3. Delete "temp_hour" from NVS
            deleteKey(key, key);
        }
        else
        {
            goto loop;
        }
    }

loop:
    while (1)
    {
        // 4. Every hour get Total operational hour
        ret = matter_get_total_operational_hour(&cur_hour);
        if (ret == 0)
        {
            // 5. If "prev_hour" and "cur_hour" differs, enter and store new value into NVS using "temp_hour"
            if (prev_hour != cur_hour)
            {
                prev_hour = cur_hour;
                if (setPref_new(key, key, (uint8_t *) &cur_hour, sizeof(cur_hour)) != DCT_SUCCESS)
                {
                    ChipLogError(DeviceLayer,"setPref_new: temp_hour failed\n");
                }
            }
        }
        vTaskDelay(HOUR_PER_MILLISECOND);
    }

    vTaskDelete(NULL);
}

void matter_op_hours(void)
{
    if (xTaskCreate(matter_op_hours_task, ((const char *)"matter_op_hours_task"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
    {
        printf("\n\r%s xTaskCreate(matter_op_hours) failed", __FUNCTION__);
    }
}
#endif

#ifdef __cplusplus
}
#endif
