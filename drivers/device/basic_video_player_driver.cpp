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

#include <basic_video_player_driver.h>
#include <support/logging/CHIPLogging.h>

static const key_pwm_map_t key_pwm_table[] = {
    {0x00, 0.00f}, {0x01, 0.01f}, {0x02, 0.02f}, {0x03, 0.03f},
    {0x04, 0.04f}, {0x05, 0.05f}, {0x06, 0.06f}, {0x07, 0.07f},
    {0x08, 0.08f}, {0x09, 0.09f}, {0x0A, 0.10f}, {0x0B, 0.11f},
    {0x0C, 0.12f}, {0x0D, 0.13f}, {0x10, 0.14f}, {0x11, 0.15f},
    {0x1D, 0.16f}, {0x1E, 0.17f}, {0x1F, 0.18f}, {0x20, 0.19f},
    {0x21, 0.20f}, {0x22, 0.21f}, {0x23, 0.22f}, {0x24, 0.23f},
    {0x25, 0.24f}, {0x26, 0.25f}, {0x27, 0.26f}, {0x28, 0.27f},
    {0x29, 0.28f}, {0x2A, 0.29f}, {0x2B, 0.30f}, {0x2C, 0.31f},
    {0x2F, 0.32f}, {0x30, 0.33f}, {0x31, 0.34f}, {0x32, 0.35f},
    {0x33, 0.36f}, {0x34, 0.37f}, {0x35, 0.38f}, {0x36, 0.39f},
    {0x37, 0.40f}, {0x38, 0.41f}, {0x40, 0.42f}, {0x41, 0.43f},
    {0x42, 0.44f}, {0x43, 0.45f}, {0x44, 0.46f}, {0x45, 0.47f},
    {0x46, 0.48f}, {0x47, 0.49f}, {0x48, 0.50f}, {0x49, 0.51f},
    {0x4A, 0.52f}, {0x4B, 0.53f}, {0x4C, 0.54f}, {0x4D, 0.55f},
    {0x4E, 0.56f}, {0x4F, 0.57f}, {0x50, 0.58f}, {0x51, 0.59f},
    {0x52, 0.60f}, {0x53, 0.61f}, {0x54, 0.62f}, {0x55, 0.63f},
    {0x56, 0.64f}, {0x57, 0.65f}, {0x60, 0.66f}, {0x61, 0.67f},
    {0x62, 0.68f}, {0x63, 0.69f}, {0x64, 0.70f}, {0x65, 0.71f},
    {0x66, 0.72f}, {0x67, 0.73f}, {0x68, 0.74f}, {0x69, 0.75f},
    {0x6A, 0.76f}, {0x6B, 0.77f}, {0x6C, 0.78f}, {0x6D, 0.79f},
    {0x71, 0.80f}, {0x72, 0.81f}, {0x73, 0.82f}, {0x74, 0.83f},
    {0x75, 0.84f}, {0x76, 0.85f},
};

static float get_pwm_duty_from_key(uint8_t keycode)
{
    for (size_t i = 0; i < sizeof(key_pwm_table)/sizeof(key_pwm_table[0]); ++i) {
        if (key_pwm_table[i].keycode == keycode) {
            return key_pwm_table[i].duty;
        }
    }
    return 0.0f;
}

void MatterBasicVideoPlayer::MediaPlayBackInit(PinName pin)
{
    mPlayBack_obj = (pwmout_t*) pvPortMalloc(sizeof(pwmout_t));
    pwmout_init(mPlayBack_obj, pin);
#if defined(CONFIG_PLATFORM_8710C)
    pwmout_period_us(mPlayBack_obj, 20000); //pwm period = 20ms
    pwmout_start(mPlayBack_obj);
#endif
}

void MatterBasicVideoPlayer::KeyPadInPutInit(PinName pin)
{
    mKeyPad_obj = (pwmout_t*) pvPortMalloc(sizeof(pwmout_t));
    pwmout_init(mKeyPad_obj, pin);
#if defined(CONFIG_PLATFORM_8710C)
    pwmout_period_us(mKeyPad_obj, 20000); //pwm period = 20ms
    pwmout_start(mKeyPad_obj);
#endif
}

void MatterBasicVideoPlayer::deInit(void)
{
    pwmout_free(mPlayBack_obj);
    pwmout_free(mKeyPad_obj);

    vPortFree(mPlayBack_obj);
    vPortFree(mKeyPad_obj);
}

int MatterBasicVideoPlayer::HandleMediaPlayBackCommand(const char *cmd)
{
    if (mPlayBack_obj == NULL || cmd == NULL) {
        return -1;
    }

    printf("[MatterBasicVideoPlayer] Received command: %s\r\n", cmd);

    if (strcmp(cmd, "play") == 0) {
        pwmout_write(mPlayBack_obj, 1.0f);
        mPlayBackState = 0;
        printf("[MatterBasicVideoPlayer] State: PLAY\r\n");
    } 
    else if (strcmp(cmd, "pause") == 0) {
        pwmout_write(mPlayBack_obj, 0.5f);
        mPlayBackState = 1;
        printf("[MatterBasicVideoPlayer] State: PAUSE\r\n");
    } 
    else if (strcmp(cmd, "stop") == 0) {
        pwmout_write(mPlayBack_obj, 0.0f);
        mPlayBackState = 2;
        printf("[MatterBasicVideoPlayer] State: STOP\r\n");
    } 
    else {
        printf("[MatterBasicVideoPlayer] Unknown command!\r\n");
        return -1;
    }

    return 0;
}

int MatterBasicVideoPlayer::HandleKeyPadInputCommand(uint8_t keycode)
{
    if (mKeyPad_obj == NULL) {
        return -1;
    }

    float duty = get_pwm_duty_from_key(keycode);
    pwmout_write(mKeyPad_obj, duty);
    printf("[MatterBasicVideoPlayer] Keypad 0x%02X -> Duty %.2f\r\n", keycode, duty);
    return 0;
}
