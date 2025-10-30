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

#include <matter_drivers.h>
#include <matter_interaction.h>
#include <basic_video_player_driver.h>

#include <media_playback/ameba_media_playback_delegate.h>
#include <keypad_input/ameba_keypad_input_delegate.h>

#include <app-common/zap-generated/attribute-type.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/util/attribute-table.h>
#include <protocols/interaction_model/StatusCode.h>

using namespace chip;
using namespace chip::app;
using namespace chip::app::Clusters;
using namespace chip::app::Clusters::MediaPlayback;
using chip::Protocols::InteractionModel::Status;

#if defined(CONFIG_PLATFORM_8710C)
#define PLAYBACK_PIN         PA_19
#define KEYPAD_PIN           PA_20
#endif

MatterBasicVideoPlayer player;

CHIP_ERROR matter_driver_basic_video_player_init(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    uint8_t playerEndpoint = 1;

    AmebaMediaPlaybackManagerInit(playerEndpoint);
    AmebaKeypadInputManagerInit(playerEndpoint);
    player.MediaPlayBackInit(PLAYBACK_PIN);
    player.KeyPadInPutInit(KEYPAD_PIN);

    return err;
}

CHIP_ERROR matter_driver_basic_video_player_startup_cfg(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;
    Status status;

    chip::DeviceLayer::PlatformMgr().LockChipStack();

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

exit:
    if (err == CHIP_ERROR_INTERNAL)
    {
        chip::DeviceLayer::PlatformMgr().UnlockChipStack();
    }
    return err;
}

void matter_driver_media_playback_handler(const char *cmd)
{
    int ret = player.HandleMediaPlayBackCommand(cmd);
    if (ret != 0) {
        ChipLogError(DeviceLayer, "[HandleMediaPlayBackCommand] Handled failed");
    }
}

void matter_driver_keypad_input_handler(uint8_t keycode)
{
    int ret =player.HandleKeyPadInputCommand(keycode);
    if (ret != 0) {
        ChipLogError(DeviceLayer, "[HandleKeyPadInputCommand] Handled failed");
    }
}

void matter_driver_uplink_update_handler(AppEvent *aEvent)
{
    chip::app::ConcreteAttributePath path = aEvent->path;

    chip::DeviceLayer::PlatformMgr().LockChipStack();

    switch (path.mClusterId)
    {
    default:
        break;
    }

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

exit:
    return;
}

void matter_driver_downlink_update_handler(AppEvent *aEvent)
{
    chip::DeviceLayer::PlatformMgr().LockChipStack();

    switch (aEvent->Type)
    {
    default:
        break;
    }

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}
