#include <FreeRTOS.h>
#include <task.h>
#include <platform_stdlib.h>
#include <platform_opts.h>

#include <example_matter_airquality_sensor.h>
#include <matter_core.h>
#include <matter_drivers.h>

#if defined(CONFIG_EXAMPLE_MATTER_AIRQUALITY_SENSOR) && (CONFIG_EXAMPLE_MATTER_AIRQUALITY_SENSOR == 1)

static void example_matter_airquality_sensor_task(void *pvParameters)
{
    while (!(wifi_is_up(RTW_STA_INTERFACE) || wifi_is_up(RTW_AP_INTERFACE))) {
        vTaskDelay(500);
    }

    ChipLogProgress(DeviceLayer, "Matter Air Quality Sensor Example!");

    CHIP_ERROR err = CHIP_NO_ERROR;

    initPref();

    err = matter_core_start();
    if (err != CHIP_NO_ERROR) {
        ChipLogProgress(DeviceLayer, "matter_core_start failed!");
    }

    err = matter_driver_airquality_sensor_init();
    if (matter_driver_airquality_sensor_init() != CHIP_NO_ERROR) {
        ChipLogProgress(DeviceLayer, "init airquality sensor value failed!");
    }

    err = matter_interaction_start_downlink();
    if (err != CHIP_NO_ERROR) {
        ChipLogProgress(DeviceLayer, "start downlink failed!\n");
    }

    err = matter_interaction_start_uplink();
    if (err != CHIP_NO_ERROR) {
        ChipLogProgress(DeviceLayer, "start uplink failed!\n");
    }

    vTaskDelete(NULL);
}

extern "C" void example_matter_airquality_sensor(void)
{
    if (xTaskCreate(example_matter_airquality_sensor_task, ((const char*)"example_matter_airquality_sensor_task"), 2048, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        ChipLogProgress(DeviceLayer, "%s xTaskCreate(example_matter_airquality_sensor_task) failed", __FUNCTION__);
    }
}

#endif /* CONFIG_EXAMPLE_MATTER_AIRQUALITY_SENSOR */
