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

#if defined(CONFIG_EXAMPLE_MATTER_HVAC_DEVICE) && CONFIG_EXAMPLE_MATTER_HVAC_DEVICE

static void example_matter_task_init_thread(void *pvParameters)
{
    while (!(wifi_is_up(RTW_STA_INTERFACE) || wifi_is_up(RTW_AP_INTERFACE)))
    {
        vTaskDelay(500);
    }

    ChipLogProgress(DeviceLayer, "Matter Task Initialization....!");

    CHIP_ERROR err = CHIP_NO_ERROR;
    chip::EndpointId endpoint = 1;

    initPref();

    err = matter_core_start();
    if (err != CHIP_NO_ERROR)
    {
        ChipLogProgress(DeviceLayer, "matter_core_start failed!");
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

extern "C" void example_matter_task_init(void)
{
    if (xTaskCreate(example_matter_task_init_thread, ((const char*)"example_matter_task_init_thread"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS)
    {
        ChipLogProgress(DeviceLayer, "%s xTaskCreate(example_matter_task_init) failed", __FUNCTION__);
    }
}

#endif /* CONFIG_EXAMPLE_MATTER_HVAC_DEVICE */
