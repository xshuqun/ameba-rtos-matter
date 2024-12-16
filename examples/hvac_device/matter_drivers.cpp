#include <matter_drivers.h>
#include <matter_interaction.h>
#include <gpio_api.h>
#include <gpio_irq_api.h>

#include <room_aircon_driver.h>
#include <temp_hum_sensor_driver.h>
#include <thermostat_driver.h>
#include <thermostat_ui_driver.h>

#include <app-common/zap-generated/attribute-type.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <app/util/attribute-table.h>
#include <protocols/interaction_model/StatusCode.h>

using namespace ::chip::app;
using chip::Protocols::InteractionModel::Status;

#if defined(CONFIG_PLATFORM_8710C)
#define DHT11 11
#define DHTTYPE DHT11
#define FAN_PIN         PA_23
#define DHT_DATA_PIN    PA_19
#elif defined(CONFIG_PLATFORM_8721D)
#define PWM_PIN         PB_5
#define FAN_PIN         PB_4
#define DHT_DATA_PIN    PA_12
#endif

uint32_t identifyTimerCount;
constexpr uint32_t kIdentifyTimerDelayMS = 250;

// Set identify cluster and its callback on ep1
static Identify gIdentify1 = {
    chip::EndpointId{ 1 }, matter_driver_on_identify_start, matter_driver_on_identify_stop, Clusters::Identify::IdentifyTypeEnum::kVisibleIndicator, matter_driver_on_trigger_effect,
};

MatterRoomAirCon aircon;
MatterRoomAirCon::FanControl airconFan;
MatterRoomAirCon::Thermostat airconThermostat;

MatterFan roomFan;

MatterTemperatureHumiditySensor DHTSensor;

MatterThermostatUI thermostatUI;
MatterThermostat roomThermostat;

static uint8_t device_type = 0;

void example_matter_thermostat(void)
{
    device_type = THERMOSTAT_DEVICE;
    matter_driver_thermostat_init();
}

void example_matter_fan(void)
{
    device_type = FAN_DEVICE;
    matter_driver_fan_init();
}

void example_matter_aircon(void)
{
    device_type = AIRCON_DEVICE;
    matter_driver_room_aircon_init();
}

/* Other Functions */
int32_t expect_pulse (uint32_t expect_level, uint32_t max_cycle, gpio_t gpio_device)
{
    uint32_t cycle = 1;
    while (expect_level == gpio_read(&gpio_device)) {
        if (cycle++ >= max_cycle) {
            return 0;
        }
    }
    return cycle;
}

void matter_driver_take_measurement(void *pvParameters)
{
    // User implementation to take measurement
    uint16_t humidity = 0;
    int16_t temperature = 0;

    while (1) {
        humidity = DHTSensor.readHumidity();
        temperature = DHTSensor.readTemperature();
        //printf("Humidity: %i %%\t Temperature: %i *C \r\n", humidity, temperature);

        matter_driver_set_measured_humidity_cb(humidity * 100);
        DHTSensor.setMeasuredHumidity(humidity * 100);

        matter_driver_set_measured_temp_cb(temperature * 100);
        DHTSensor.setMeasuredTemperature(temperature * 100);

        vTaskDelay(10000);
    }
}

/* Callbacks for downlink */
void matter_driver_set_measured_temp_cb(int16_t value)
{
    AppEvent downlink_event;
    downlink_event.Type = AppEvent::kEventType_Downlink_TemperatureMeasurement_SetValue;
    downlink_event.value._i16 = (int16_t) value;
    downlink_event.mHandler = matter_driver_downlink_update_handler;
    PostDownlinkEvent(&downlink_event);
}

void matter_driver_set_measured_humidity_cb(uint16_t value)
{
    AppEvent downlink_event;
    downlink_event.Type = AppEvent::kEventType_Downlink_RelativeHumidityMeasurement_SetValue;
    downlink_event.value._u16 = (uint16_t) value;
    downlink_event.mHandler = matter_driver_downlink_update_handler;
    PostDownlinkEvent(&downlink_event);
}

/* Device Types Initialization */
CHIP_ERROR matter_driver_fan_init(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    Status status;
    DataModel::Nullable<uint8_t> FanPercentSettingValue;
    chip::app::Clusters::FanControl::FanModeEnum FanModeValue;

    chip::EndpointId ep = aircon.GetEp();
    ChipLogProgress(DeviceLayer, "Aircon Fan on Endpoint%d", ep);

    chip::DeviceLayer::PlatformMgr().LockChipStack();

    // get percent setting value
    status = Clusters::FanControl::Attributes::PercentSetting::Get(ep, FanPercentSettingValue);
    VerifyOrExit(status == Status::Success, err = CHIP_ERROR_INTERNAL);
    // get fan mode
    status = Clusters::FanControl::Attributes::FanMode::Get(ep, &FanModeValue);
    VerifyOrExit(status == Status::Success, err = CHIP_ERROR_INTERNAL);

    if (device_type == AIRCON_DEVICE) {
        airconFan.setFanSpeedPercent(FanPercentSettingValue.Value());
        airconFan.setFanMode((uint8_t) FanModeValue);
    } else if (device_type == FAN_DEVICE) {
        roomFan.Init(PWM_PIN);
        roomFan.setFanSpeedPercent(FanPercentSettingValue.Value());
        roomFan.setFanMode((uint8_t) FanModeValue);
    }

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

exit:
    if (err == CHIP_ERROR_INTERNAL) {
        chip::DeviceLayer::PlatformMgr().UnlockChipStack();
    }
    return err;
}

CHIP_ERROR matter_driver_humidity_sensor_init(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    Status status;
    uint16_t minValue = 0;
    uint16_t maxValue = 10000;

    chip::EndpointId ep = DHTSensor.GetHumSensorEp();
    ChipLogProgress(DeviceLayer, "Humidity Sensor on Endpoint%d", ep);

    chip::DeviceLayer::PlatformMgr().LockChipStack();

    status = Clusters::RelativeHumidityMeasurement::Attributes::MinMeasuredValue::Set(ep, minValue);
    VerifyOrExit(status == Status::Success, err = CHIP_ERROR_INTERNAL);

    status = Clusters::RelativeHumidityMeasurement::Attributes::MaxMeasuredValue::Set(ep, maxValue);
    VerifyOrExit(status == Status::Success, err = CHIP_ERROR_INTERNAL);

    ChipLogProgress(DeviceLayer, "Humidity range: Min = %i, Max = %i", minValue, maxValue);

    DHTSensor.setMinMeasuredHumidity(minValue);
    DHTSensor.setMaxMeasuredHumidity(maxValue);

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

exit:
    if (err == CHIP_ERROR_INTERNAL) {
        chip::DeviceLayer::PlatformMgr().UnlockChipStack();
    }
    return err;
}

CHIP_ERROR matter_driver_temperature_sensor_init(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    Status status;
    int16_t minValue = -500;
    int16_t maxValue = 6000;

    chip::EndpointId ep = DHTSensor.GetTempSensorEp();
    ChipLogProgress(DeviceLayer, "Temperature Sensor on Endpoint%d", ep);

    chip::DeviceLayer::PlatformMgr().LockChipStack();

    status = Clusters::TemperatureMeasurement::Attributes::MinMeasuredValue::Set(ep, minValue);
    VerifyOrExit(status == Status::Success, err = CHIP_ERROR_INTERNAL);

    status = Clusters::TemperatureMeasurement::Attributes::MaxMeasuredValue::Set(ep, maxValue);
    VerifyOrExit(status == Status::Success, err = CHIP_ERROR_INTERNAL);

    ChipLogProgress(DeviceLayer, "Temperature range: Min = %i, Max = %i", minValue, maxValue);

    DHTSensor.setMinMeasuredTemperature(minValue);
    DHTSensor.setMaxMeasuredTemperature(maxValue);

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

exit:
    if (err == CHIP_ERROR_INTERNAL) {
        chip::DeviceLayer::PlatformMgr().UnlockChipStack();
    }
    return err;
}

CHIP_ERROR matter_driver_room_aircon_init(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    chip::EndpointId AirConEndpoint = 1;
    chip::EndpointId HumSensorEndpoint = 2;
    chip::EndpointId TempSensorEndpoint = 3;

    aircon.SetEp(AirConEndpoint);
    DHTSensor.SetHumSensorEp(HumSensorEndpoint);
    DHTSensor.SetTempSensorEp(TempSensorEndpoint);

    airconFan.Init(FAN_PIN);
    DHTSensor.Init(DHT_DATA_PIN);

    err = matter_driver_fan_init();
    if (err != CHIP_NO_ERROR) {
        ChipLogProgress(DeviceLayer, "matter_driver_fan_init failed!");
        goto exit;
    }

    err = matter_driver_humidity_sensor_init();
    if (err != CHIP_NO_ERROR) {
        ChipLogProgress(DeviceLayer, "matter_driver_humidity_sensor_init failed!");
        goto exit;
    }

    err = matter_driver_temperature_sensor_init();
    if (err != CHIP_NO_ERROR) {
        ChipLogProgress(DeviceLayer, "matter_driver_temperature_sensor_init failed!");
        goto exit;
    }

    if (xTaskCreate(matter_driver_take_measurement, "matter_driver_take_measurement", 1024, NULL, tskIDLE_PRIORITY + 1, NULL) != pdPASS) {
        ChipLogError(DeviceLayer, "failed to create matter_driver_take_measurement");
    }

exit:
    return err;
}

CHIP_ERROR matter_driver_thermostat_init(void)
{

    CHIP_ERROR err = CHIP_NO_ERROR;
    Status getstatus;
    DataModel::Nullable<int16_t> temp;
    int16_t OccupiedCoolingSetpoint;
    int16_t OccupiedHeatingSetpoint;
    chip::app::Clusters::Thermostat::SystemModeEnum SystemMode;

    roomThermostat.Init();
    thermostatUI.Init();

    chip::DeviceLayer::PlatformMgr().LockChipStack();
    getstatus = Clusters::Thermostat::Attributes::LocalTemperature::Get(1, temp);
    VerifyOrExit(getstatus == Status::Success, err = CHIP_ERROR_INTERNAL);
    getstatus = Clusters::Thermostat::Attributes::OccupiedCoolingSetpoint::Get(1, &OccupiedCoolingSetpoint);
    VerifyOrExit(getstatus == Status::Success, err = CHIP_ERROR_INTERNAL);
    getstatus = Clusters::Thermostat::Attributes::OccupiedHeatingSetpoint::Get(1, &OccupiedHeatingSetpoint);
    VerifyOrExit(getstatus == Status::Success, err = CHIP_ERROR_INTERNAL);
    getstatus = Clusters::Thermostat::Attributes::SystemMode::Get(1, &SystemMode);
    VerifyOrExit(getstatus == Status::Success, err = CHIP_ERROR_INTERNAL);
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();

    if (temp.IsNull()) {
        thermostatUI.SetLocalTemperature(0);
    }
    else {
        thermostatUI.SetLocalTemperature(temp.Value());
    }

    thermostatUI.SetOccupiedCoolingSetpoint(OccupiedCoolingSetpoint);
    thermostatUI.SetOccupiedHeatingSetpoint(OccupiedHeatingSetpoint);
    thermostatUI.SetSystemMode((uint8_t)SystemMode);

    thermostatUI.UpdateDisplay();

exit:
    if (err == CHIP_ERROR_INTERNAL) {
        chip::DeviceLayer::PlatformMgr().UnlockChipStack();
    }

    return CHIP_NO_ERROR;
}


/* Identify Cluster Functions */
void matter_driver_on_identify_start(Identify * identify)
{
    ChipLogProgress(Zcl, "OnIdentifyStart");
}

void matter_driver_on_identify_stop(Identify * identify)
{
    ChipLogProgress(Zcl, "OnIdentifyStop");
}

void matter_driver_on_trigger_effect(Identify * identify)
{
    switch (identify->mCurrentEffectIdentifier)
    {
    case Clusters::Identify::EffectIdentifierEnum::kBlink:
        ChipLogProgress(Zcl, "Clusters::Identify::EffectIdentifierEnum::kBlink");
        break;
    case Clusters::Identify::EffectIdentifierEnum::kBreathe:
        ChipLogProgress(Zcl, "Clusters::Identify::EffectIdentifierEnum::kBreathe");
        break;
    case Clusters::Identify::EffectIdentifierEnum::kOkay:
        ChipLogProgress(Zcl, "Clusters::Identify::EffectIdentifierEnum::kOkay");
        break;
    case Clusters::Identify::EffectIdentifierEnum::kChannelChange:
        ChipLogProgress(Zcl, "Clusters::Identify::EffectIdentifierEnum::kChannelChange");
        break;
    default:
        ChipLogProgress(Zcl, "No identifier effect");
        return;
    }
}

void IdentifyTimerHandler(chip::System::Layer *systemLayer, void *appState, CHIP_ERROR error)
{
    if (identifyTimerCount)
    {
        identifyTimerCount--;
    }
}

void matter_driver_OnIdentifyPostAttributeChangeCallback(uint8_t *value)
{
    // timerCount represents the number of callback executions before we stop the timer.
    // value is expressed in seconds and the timer is fired every 250ms, so just multiply value by 4.
    // Also, we want timerCount to be odd number, so the ligth state ends in the same state it starts.
    identifyTimerCount = (*value) * 4;

exit:
    return;
}

/* Uplink and Downlink handler */
void matter_driver_uplink_update_handler(AppEvent *aEvent)
{
    chip::app::ConcreteAttributePath path = aEvent->path;
    DataModel::Nullable<uint8_t> FanPercentSettingValue;
    chip::EndpointId ep;

    chip::DeviceLayer::PlatformMgr().LockChipStack();

    switch (path.mClusterId)
    {
    case Clusters::FanControl::Id:
        if (path.mAttributeId == Clusters::FanControl::Attributes::PercentSetting::Id) {
            if (device_type == AIRCON_DEVICE) {
                airconFan.setFanSpeedPercent(aEvent->value._u8);
            } else if (device_type == FAN_DEVICE) {
                roomFan.setFanSpeedPercent(aEvent->value._u8);
            }
        }
        else if (path.mAttributeId == Clusters::FanControl::Attributes::FanMode::Id) {
            if (device_type == AIRCON_DEVICE) {
                airconFan.setFanMode(aEvent->value._u8);
            } else if (device_type == FAN_DEVICE) {
                roomFan.setFanMode(aEvent->value._u8);
            }
        }
        break;
    case Clusters::Identify::Id:
        {
            matter_driver_OnIdentifyPostAttributeChangeCallback(&(aEvent->value._u8));
        }
        break;
    case Clusters::RelativeHumidityMeasurement::Id:
        if (path.mAttributeId == Clusters::RelativeHumidityMeasurement::Attributes::MeasuredValue::Id) {
            DHTSensor.setMeasuredHumidity(aEvent->value._u16);
        }
        break;
    case Clusters::TemperatureMeasurement::Id:
        if (path.mAttributeId == Clusters::TemperatureMeasurement::Attributes::MeasuredValue::Id) {
            DHTSensor.setMeasuredTemperature(aEvent->value._i16);
        }
        break;
    case Clusters::Thermostat::Id:
        {
            if (path.mAttributeId == Clusters::Thermostat::Attributes::LocalTemperature::Id) {
                thermostatUI.SetLocalTemperature(aEvent->value._u16);
                thermostat.Do();
            }
            if (path.mAttributeId == Clusters::Thermostat::Attributes::OccupiedCoolingSetpoint::Id) {
                thermostatUI.SetOccupiedCoolingSetpoint(aEvent->value._u16);
                thermostat.Do();
            }
            if (path.mAttributeId == Clusters::Thermostat::Attributes::OccupiedHeatingSetpoint::Id) {
                thermostatUI.SetOccupiedHeatingSetpoint(aEvent->value._u16);
                thermostat.Do();
            }
            if (path.mAttributeId == Clusters::Thermostat::Attributes::SystemMode::Id) {
                thermostatUI.SetSystemMode(aEvent->value._u8);
                thermostat.Do();
            }
            thermostatUI.UpdateDisplay();
        }
        break;
    case Clusters::OnOff::Id:
        if (path.mAttributeId == Clusters::OnOff::Attributes::OnOff::Id) {
            if (device_type == AIRCON_DEVICE) {
                airconFan.setFanMode((aEvent->value._u8 == 1) ? 4 /* kOn */ : 0 /* kOff */);
                ep = aircon.GetEp();
            } else if (device_type == FAN_DEVICE) {
                roomFan.setFanMode((aEvent->value._u8 == 1) ? 4 /* kOn */ : 0 /* kOff */);
                ep = 1;
            }
            if (aEvent->value._u8 == 1) {
                Clusters::FanControl::Attributes::FanMode::Set(ep, Clusters::FanControl::FanModeEnum::kOn);
            }
            else {
                Clusters::FanControl::Attributes::FanMode::Set(ep, Clusters::FanControl::FanModeEnum::kOff);
            }
        }
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
    case AppEvent::kEventType_Downlink_RelativeHumidityMeasurement_SetValue:
        {
            chip::EndpointId ep = DHTSensor.GetHumSensorEp();
            //ChipLogProgress(DeviceLayer, "Set Humidity %i on Endpoint%d", aEvent->value._u16, ep);
            Clusters::RelativeHumidityMeasurement::Attributes::MeasuredValue::Set(ep, aEvent->value._u16);
        }
        break;
    case AppEvent::kEventType_Downlink_TemperatureMeasurement_SetValue:
        {
            chip::EndpointId ep = DHTSensor.GetTempSensorEp();
            //ChipLogProgress(DeviceLayer, "Set Temperature %i on Endpoint%d", aEvent->value._i16, ep);
            Clusters::TemperatureMeasurement::Attributes::MeasuredValue::Set(ep, aEvent->value._i16);
        }
        break;
    default:
        break;
    }

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}
