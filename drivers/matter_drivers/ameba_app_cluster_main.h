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

#include <app/AttributeAccessInterfaceRegistry.h>

/* Actions Cluster */
#include <actions/ameba_actions_delegate.h>
#include <actions/ameba_actions_manager.h>

/* Air Quality Cluster */
#include <app/clusters/air-quality-server/air-quality-server.h>
#include <air_quality/ameba_air_quality_manager.h>

/* Dishwasher Alarm Cluster */
#include <dishwasher_alarm/ameba_dishwasher_alarm_delegate.h>
#include <dishwasher_alarm/ameba_dishwasher_alarm_manager.h>

/* Dishwasher Mode Cluster */
#include <dishwasher_mode/ameba_dishwasher_mode_delegate.h>
#include <dishwasher_mode/ameba_dishwasher_mode_manager.h>

/* Fan Control Cluster */
#include <fan_control/ameba_fan_control_delegate.h>

/* Laundry Dryer Controls Cluster */
#include <app/clusters/laundry-dryer-controls-server/laundry-dryer-controls-delegate.h>
#include <app/clusters/laundry-dryer-controls-server/laundry-dryer-controls-server.h>
#include <laundry_dryer_controls/ameba_laundry_dryer_controls_delegate.h>
#include <laundry_dryer_controls/ameba_laundry_dryer_controls_manager.h>

/* Laundry Washer Controls Cluster */
#include <app/clusters/laundry-washer-controls-server/laundry-washer-controls-delegate.h>
#include <app/clusters/laundry-washer-controls-server/laundry-washer-controls-server.h>
#include <laundry_washer_controls/ameba_laundry_washer_controls_delegate.h>
#include <laundry_washer_controls/ameba_laundry_washer_controls_manager.h>

/* Laundry Washer Mode Cluster */
#include <laundry_washer_mode/ameba_laundry_washer_mode_delegate.h>
#include <laundry_washer_mode/ameba_laundry_washer_mode_manager.h>

/* Microwave Oven Control Cluster */
#include <app/clusters/microwave-oven-control-server/microwave-oven-control-server.h>
#include <microwave_oven_control/ameba_microwave_oven_control_delegate.h>
#include <microwave_oven_control/ameba_microwave_oven_control_manager.h>

/* Microwave Oven Mode Cluster */
#include <microwave_oven_mode/ameba_microwave_oven_mode_delegate.h>
#include <microwave_oven_mode/ameba_microwave_oven_mode_manager.h>

/* Operational State */
#include <app/clusters/operational-state-server/operational-state-server.h>
#include <operational_state/ameba_operational_state_delegate_impl.h>

/* Oven Mode Cluster */
#include <oven_mode/ameba_oven_mode_delegate.h>
#include <oven_mode/ameba_oven_mode_manager.h>

/* Refrigerator and Temperature Controlled Cabinet Mode Cluster */
#include <refrigerator_mode/ameba_tcc_mode_delegate.h>
#include <refrigerator_mode/ameba_tcc_mode_manager.h>

/* RVC Clean Mode Cluster */
#include <rvc_clean_mode/ameba_rvc_clean_mode_delegate.h>
#include <rvc_clean_mode/ameba_rvc_clean_mode_manager.h>

/* RVC Run Mode Cluster */
#include <rvc_run_mode/ameba_rvc_run_mode_delegate.h>
#include <rvc_run_mode/ameba_rvc_run_mode_manager.h>

/* Water Heater Mode Cluster */
#include <water_heater_mode/ameba_water_heater_mode_delegate.h>
#include <water_heater_mode/ameba_water_heater_mode_manager.h>

/* Resource Monitoring Cluster */
#include <resource_monitoring/ameba_resource_monitoring_delegate.h>
#include <resource_monitoring/ameba_resource_monitoring_manager.h>
