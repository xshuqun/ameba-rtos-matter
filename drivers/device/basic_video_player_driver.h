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

#include <platform_stdlib.h>
#include <pwmout_api.h>

#include <app/util/attribute-table.h>

typedef struct {
    uint8_t keycode;
    float duty;
} key_pwm_map_t;

class MatterBasicVideoPlayer
{
public:
    void MediaPlayBackInit(PinName pin);
    void KeyPadInPutInit(PinName pin);
    void deInit(void);
    int HandleMediaPlayBackCommand(const char *cmd);
    int HandleKeyPadInputCommand(uint8_t keycode);

private:
    pwmout_t *mPlayBack_obj = NULL;
    pwmout_t *mKeyPad_obj = NULL;
    int mPlayBackState = 0;
};
