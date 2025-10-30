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

#include <FreeRTOS.h>
#include <task.h>
#include <platform/platform_stdlib.h>
#include <basic_types.h>
#include <platform_opts.h>
#include <section_config.h>
#include <wifi_constants.h>
#include <wifi/wifi_conf.h>
#include <chip_porting.h>
#include <matter_core.h>
#include <matter_drivers.h>
#include <matter_interaction.h>

#if defined(CONFIG_EXAMPLE_MATTER_BASIC_VIDEO_PLAYER) && CONFIG_EXAMPLE_MATTER_BASIC_VIDEO_PLAYER

static void example_matter_basic_video_player_task(void *pvParameters)
{
    while (!(wifi_is_up(RTW_STA_INTERFACE) || wifi_is_up(RTW_AP_INTERFACE)))
    {
        vTaskDelay(500);
    }

    ChipLogProgress(DeviceLayer, "Matter Basic Video Player Example!");

    CHIP_ERROR err = CHIP_NO_ERROR;

    initPref();

    err = matter_core_start();
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "matter_core_start failed!");
    }

    err = matter_driver_basic_video_player_init();
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "matter_driver_basic_video_player_init failed!");
    }

    err = matter_driver_basic_video_player_startup_cfg();
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "matter_driver_basic_video_player_startup_cfg failed!");
    }


    err = matter_interaction_start_downlink();
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "matter_interaction_start_downlink failed!\n");
    }

    err = matter_interaction_start_uplink();
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "matter_interaction_start_uplink failed!\n");
    }

    vTaskDelete(NULL);
}

extern "C" void example_matter_basic_video_player(void)
{
    if (xTaskCreate(example_matter_basic_video_player_task, ((const char*)"example_matter_basic_video_player_task"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
    {
        ChipLogProgress(DeviceLayer, "%s xTaskCreate(example_matter_basic_video_player_task) failed", __FUNCTION__);
    }
}

#endif /* CONFIG_EXAMPLE_MATTER_BASIC_VIDEO_PLAYER */
