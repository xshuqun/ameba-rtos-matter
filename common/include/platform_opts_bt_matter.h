/******************************************************************************
  *
  * This module is a confidential and proprietary property of RealTek and
  * possession or use of this module requires written permission of RealTek.
  *
  * Copyright(c) 2016, Realtek Semiconductor Corporation. All rights reserved.
  *
******************************************************************************/

#ifndef __PLATFORM_OPTS_BT_MATTER_H__
#define __PLATFORM_OPTS_BT_MATTER_H__

/*
 * For AmebaZ2/AmebaZ2plus, bt configuration will set in this header file (platform_opts_bt_matter.h).
 * For AmebaD, bt configuration will be set from the menuconfig.
 */

#if CONFIG_BT

#if defined(CONFIG_PLATFORM_8710C)
#undef CONFIG_BT_MESH_DEVICE_MATTER

/*
 * BLE/BT-related Matter Support Configuration Options:
 *
 * CONFIG_BLE_MATTER_ADAPTER
 *   - Enables Matter BLE (Peripheral mode).
 *
 * CONFIG_BLE_MATTER_MULTI_ADV_ON
 *   - Allows multiple BLE advertisements to support both Matter BLE and custom BLE applications.
 *   - [Requirement] CONFIG_BLE_MATTER_ADAPTER must be enabled.
 *
 * CONFIG_BT_MESH_DEVICE_MATTER
 *   - Enables support for both Matter BLE and non-Matter Mesh.
 *   - [Requirement] CONFIG_BLE_MATTER_ADAPTER & CONFIG_BLE_MATTER_MULTI_ADV_ON must be disabled.
 */

#define CONFIG_BLE_MATTER_ADAPTER                1  /* Matter BLE Peripheral Adapter must be enabled for Matter advertising */
#define CONFIG_BLE_MATTER_MULTI_ADV_ON           0  /* Matter BLE + Customer BLE */
#define CONFIG_BT_MESH_DEVICE_MATTER             0  /* Matter BLE Peripheral + Mesh */

#if ((defined(CONFIG_BLE_MATTER_MULTI_ADV_ON) && CONFIG_BLE_MATTER_MULTI_ADV_ON) && \
     !(defined(CONFIG_BLE_MATTER_ADAPTER) && CONFIG_BLE_MATTER_ADAPTER))
    error "Please enable CONFIG_BLE_MATTER_ADAPTER"
#endif

#if defined(CONFIG_BT_MESH_DEVICE_MATTER) && CONFIG_BT_MESH_DEVICE_MATTER
    #undef CONFIG_BLE_MATTER_ADAPTER
    #undef CONFIG_BLE_MATTER_MULTI_ADV_ON
    #undef CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE
    #define CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE   1
#endif

#if (CONFIG_BT_MESH_DEVICE_MATTER && !CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE) || \
    (!CONFIG_BT_MESH_DEVICE_MATTER && CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE)
    #error "Please enable both CONFIG_BT_MESH_DEVICE_MATTER & CONFIG_BT_MESH_DEVICE_MULTIPLE_PROFILE"
#endif

#endif /* CONFIG_PLATFORM_8710C */

#endif /* CONFIG_BT */

#endif /* __PLATFORM_OPTS_BT_MATTER_H__ */

