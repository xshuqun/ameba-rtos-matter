/*
 *    This module is a confidential and proprietary property of RealTek and
 *    possession or use of this module requires written permission of RealTek.
 *
 *    Copyright(c) 2024, Realtek Semiconductor Corporation. All rights reserved.
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
#include <platform_opts.h>
#include <log_service.h>
#include <matter_consoles.h>
#include <air_quality/ameba_air_quality_manager.h>
#include <resource_monitoring/ameba_activated_carbon_filter_manager.h>

#include <platform/CHIPDeviceLayer.h>

using namespace chip::app::Clusters;
using namespace chip::app::Clusters::ActivatedCarbonFilterMonitoring;
using namespace chip::app::Clusters::AirQuality;
using namespace chip::app::Clusters::ResourceMonitoring;

#if defined(AMEBA_MATTER_SERVER_ATCMD) && (AMEBA_MATTER_SERVER_ATCMD == 1)
extern "C" void matter_console(char **argv)
{
    if (!argv[1]) {
        goto exit;
    }

    if (strcmp((const char*)argv[1], "airqual") == 0) {
        if (strcmp((const char*)argv[2], "air_quality") == 0 && argv[3]) {
            int value = atoi((const char*)argv[3]);
            matter_console_airqual_set_airquality(value);
        } else {
            matter_console_airqual_help();
        }
    } else if (strcmp((const char*)argv[1], "acfremon") == 0) {
        if (strcmp((const char*)argv[2], "condition") == 0 && argv[3]) {
            int value = atoi((const char*)argv[3]);
            matter_console_acfremon_set_condition(value);
        } else if (strcmp((const char*)argv[2], "changeindication") == 0 && argv[3]) {
            int value = atoi((const char*)argv[3]);
            matter_console_acfremon_set_changeindication(value);
        } else {
            matter_console_acfremon_help();
        }
    } else {
        goto exit;
    }

    return;
exit:
    printf("\tATMT=cluster,attribute,value\r\n");
    printf("\t     airqual,attribute,<value>\r\n");
    printf("\t     acfremon,attribute,<value>\r\n");
}

/* AirQuality Cluster */
void matter_console_airqual_help(void)
{
    printf("Usage: ATMT=airqual,air_quality,<value>\n");
    printf("    1 = kGood\n");
    printf("    2 = kFair\n");
    printf("    3 = kModerate\n");
    printf("    4 = kPoor\n");
    printf("    5 = kVeryPoor\n");
    printf("    6 = kExtremelyPoor\n");
}

void matter_console_airqual_set_airquality(int value)
{
    chip::DeviceLayer::PlatformMgr().LockChipStack();
    switch (value) {
        case 1:
            SetAirQuality(AirQualityEnum::kGood);
            break;
        case 2:
            SetAirQuality(AirQualityEnum::kFair);
            break;
        case 3:
            SetAirQuality(AirQualityEnum::kModerate);
            break;
        case 4:
            SetAirQuality(AirQualityEnum::kPoor);
            break;
        case 5:
            SetAirQuality(AirQualityEnum::kVeryPoor);
            break;
        case 6:
            SetAirQuality(AirQualityEnum::kExtremelyPoor);
            break;
        default:
            printf("Invalid air quality value. Use 1~6. Try help.\n");
            break;
    }
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}

// Resource Monitoring - Activated Carbon Filter Monitoring (ACFREMON)
void matter_console_acfremon_help(void)
{
    printf("Usage: ATMT=acfremon,condition,<percent>\n");
    printf("    percent = 0 ~ 100\n");
    printf("Usage: ATMT=acfremon,changeindication,<value>\n");
    printf("    1 = kOk\n");
    printf("    2 = kWarning\n");
    printf("    3 = kCritical\n");
    printf("    4 = kUnknownEnumValue\n");
}

void matter_console_acfremon_set_condition(int value)
{
    chip::DeviceLayer::PlatformMgr().LockChipStack();
    SetCondition(value);
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}

void matter_console_acfremon_set_changeindication(int value)
{
    chip::DeviceLayer::PlatformMgr().LockChipStack();
    switch (value) {
        case 0:
            SetChangeIndication(ResourceMonitoring::ChangeIndicationEnum::kOk);
            break;
        case 1:
            SetChangeIndication(ResourceMonitoring::ChangeIndicationEnum::kWarning);
            break;
        case 2:
            SetChangeIndication(ResourceMonitoring::ChangeIndicationEnum::kCritical);
            break;
        default:
            SetChangeIndication(ResourceMonitoring::ChangeIndicationEnum::kUnknownEnumValue);
            break;
    }
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}
#endif //AMEBA_MATTER_SERVER_ATCMD
