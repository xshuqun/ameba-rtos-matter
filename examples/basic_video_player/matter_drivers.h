/********************************************************************************
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
  *
********************************************************************************/
#pragma once

#include <matter_events.h>
#include <platform/CHIPDeviceLayer.h>

/**
 * @brief  Initialize the Basic Video Player driver.
 * @return  CHIP_NO_ERROR set successfully, CHIP_ERROR_INTERNAL otherwise (if necessary).
 */
CHIP_ERROR matter_driver_basic_video_player_init(void);

/**
 * @brief  Set the startup values for the Basic Video Player.
 * @return  CHIP_NO_ERROR set successfully, CHIP_ERROR_INTERNAL otherwise.
 */
CHIP_ERROR matter_driver_basic_video_player_startup_cfg(void);

/**
 * @brief  Handler to set device hardware upon receiving commands from controller.
 * @param cmd Command string: "play", "pause", "stop"
 */
void matter_driver_media_playback_handler(const char *cmd);

/**
 * @brief Handler to set PWM based on key code
 * @param keycode Media key code
 */
void matter_driver_keypad_input_handler(uint8_t keycode);

/**
 * @brief  Update uplink handler when receiving commands from Matter Controller.
 * @param[in]  event: Pointer to the AppEvent structure containing event details.
 */
void matter_driver_uplink_update_handler(AppEvent *aEvent);

/**
 * @brief  Update downlink handler when receiving commands from external (e.g., GPIO, PWM).
 * @param[in]  event: Pointer to the AppEvent structure containing event details.
 */
void matter_driver_downlink_update_handler(AppEvent *aEvent);
