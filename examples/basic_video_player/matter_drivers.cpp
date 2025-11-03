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
#include <gpio_irq_api.h>
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
#define GPIO_IRQ_PIN         PA_17
#define PLAYBACK_PIN         PA_19
#define KEYPAD_PIN           PA_20
#endif

static bool btn_ctrl = 0;
MatterBasicVideoPlayer player;

static void matter_driver_button_callback(uint32_t id, gpio_irq_event event)
{
    AppEvent downlink_event;
    downlink_event.Type = AppEvent::kEventType_Downlink_OnOff;
    btn_ctrl = !btn_ctrl;
    downlink_event.value._u8 = (uint8_t) btn_ctrl; // toggle
    downlink_event.mHandler = matter_driver_downlink_update_handler;
    PostDownlinkEvent(&downlink_event);
}

static void matter_driver_button_init(void)
{
    gpio_irq_t gpio_btn;
    gpio_irq_init(&gpio_btn, GPIO_IRQ_PIN, matter_driver_button_callback, 1);
    gpio_irq_set(&gpio_btn, IRQ_FALL, 1);   // Falling Edge Trigger
    gpio_irq_enable(&gpio_btn);
}

CHIP_ERROR matter_driver_basic_video_player_init(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    uint8_t playerEndpoint = 1;

    // Initialize gpio for button to on/off video player
    matter_driver_button_init();

    // Initialize Media Playback delegate and PWM PIN
    AmebaMediaPlaybackManagerInit(playerEndpoint);
    player.MediaPlayBackInit(PLAYBACK_PIN);

    // Initialize Keypad Input delegate and PWM PIN
    AmebaKeypadInputManagerInit(playerEndpoint);
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
    case Clusters::OnOff::Id:
        if (path.mAttributeId == Clusters::OnOff::Attributes::OnOff::Id) {
            // Turn on the video player
        }
        break;
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
    case AppEvent::kEventType_Downlink_OnOff:
        {
            Status status = Clusters::OnOff::Attributes::OnOff::Set(1, btn_ctrl);
            if (status != Status::Success)
            {
                ChipLogError(DeviceLayer, "Updating on/off cluster failed: %x", status);
            }
        }
        break;
    default:
        break;
    }

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}
