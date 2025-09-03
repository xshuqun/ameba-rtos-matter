#include <matter_drivers.h>
#include <matter_interaction.h>
#include <led_driver.h>
#include <gpio_irq_api.h>

#include <app-common/zap-generated/attribute-type.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <protocols/interaction_model/StatusCode.h>

using namespace ::chip::app;
using chip::Protocols::InteractionModel::Status;

#if defined(CONFIG_PLATFORM_8710C)
#define PWM_LED1         PA_23
#define GPIO_IRQ_PIN1    PA_17
#if CONFIG_MULTIPLE_LIGHT_DEVICE
#define PWM_LED2         PA_22
#define GPIO_IRQ_PIN2    PA_18
#endif // CONFIG_MULTIPLE_LIGHT_DEVICE
#elif defined(CONFIG_PLATFORM_8721D)
#define PWM_LED         PB_5
#define GPIO_IRQ_PIN    PA_12
#endif

MatterLED led1;
gpio_irq_t gpio_btn1;
#if CONFIG_MULTIPLE_LIGHT_DEVICE
MatterLED led2;
gpio_irq_t gpio_btn2;
#endif // CONFIG_MULTIPLE_LIGHT_DEVICE

// Set identify cluster and its callback on ep1
static Identify gIdentify1 = {
    chip::EndpointId{ 1 }, matter_driver_on_identify_start, matter_driver_on_identify_stop, Clusters::Identify::IdentifyTypeEnum::kVisibleIndicator, matter_driver_on_trigger_effect,
};

// Set identify cluster and its callback on ep2
#if CONFIG_MULTIPLE_LIGHT_DEVICE
static Identify gIdentify2 = {
    chip::EndpointId{ 2 }, matter_driver_on_identify_start, matter_driver_on_identify_stop, Clusters::Identify::IdentifyTypeEnum::kVisibleIndicator, matter_driver_on_trigger_effect,
};
#endif // CONFIG_MULTIPLE_LIGHT_DEVICE

void matter_driver_ep1_button_cb(uint32_t id, gpio_irq_event event)
{
    AppEvent downlink_event;
    downlink_event.Type = AppEvent::kEventType_Downlink_OnOff;
    downlink_event.path.mEndpointId = 1;
    downlink_event.value._u8 = (uint8_t) !led1.IsTurnedOn(); // toggle
    downlink_event.mHandler = matter_driver_downlink_update_handler;
    PostDownlinkEvent(&downlink_event);
}

CHIP_ERROR matter_driver_ep1_button_init(void)
{
    gpio_irq_init(&gpio_btn1, GPIO_IRQ_PIN1, matter_driver_ep1_button_cb, 1);
    gpio_irq_set(&gpio_btn1, IRQ_FALL, 1);   // Falling Edge Trigger
    gpio_irq_enable(&gpio_btn1);
    return CHIP_NO_ERROR;
}

#if CONFIG_MULTIPLE_LIGHT_DEVICE
void matter_driver_ep2_button_cb(uint32_t id, gpio_irq_event event)
{
    AppEvent downlink_event;
    downlink_event.Type = AppEvent::kEventType_Downlink_OnOff;
    downlink_event.path.mEndpointId = 2;
    downlink_event.value._u8 = (uint8_t) !led2.IsTurnedOn(); // toggle
    downlink_event.mHandler = matter_driver_downlink_update_handler;
    PostDownlinkEvent(&downlink_event);
}

CHIP_ERROR matter_driver_ep2_button_init(void)
{
    gpio_irq_init(&gpio_btn2, GPIO_IRQ_PIN2, matter_driver_ep2_button_cb, 1);
    gpio_irq_set(&gpio_btn2, IRQ_FALL, 1);   // Falling Edge Trigger
    gpio_irq_enable(&gpio_btn2);
    return CHIP_NO_ERROR;
}
#endif // CONFIG_MULTIPLE_LIGHT_DEVICE

CHIP_ERROR matter_driver_led_init(void)
{
    led1.Init(PWM_LED1);
#if CONFIG_MULTIPLE_LIGHT_DEVICE
    led2.Init(PWM_LED2);
#endif // CONFIG_MULTIPLE_LIGHT_DEVICE
    return CHIP_NO_ERROR;
}

CHIP_ERROR matter_driver_led_set_startup_value(void)
{
    CHIP_ERROR err = CHIP_NO_ERROR;

    chip::DeviceLayer::PlatformMgr().LockChipStack();

    bool LEDOnOffValue1 = 0;
    Status OnOffStatus1 = Clusters::OnOff::Attributes::OnOff::Get(1, &LEDOnOffValue1);
    VerifyOrExit(OnOffStatus1 == Status::Success, err = CHIP_ERROR_INTERNAL);
    led1.Set(LEDOnOffValue1);

#if USE_LEVEL_CONTROL
    {
        DataModel::Nullable<uint8_t> LEDCurrentLevelValue1;
        Status CurrentLevelStatus1 = Clusters::LevelControl::Attributes::CurrentLevel::Get(1, LEDCurrentLevelValue1);
        VerifyOrExit(CurrentLevelStatus1 == Status::Success, err = CHIP_ERROR_INTERNAL);
        led1.SetBrightness(LEDCurrentLevelValue1.Value());
    }
#endif

#if CONFIG_MULTIPLE_LIGHT_DEVICE
    {
        bool LEDOnOffValue2 = 0;
        Status OnOffStatus2 = Clusters::OnOff::Attributes::OnOff::Get(2, &LEDOnOffValue2);
        VerifyOrExit(OnOffStatus2 == Status::Success, err = CHIP_ERROR_INTERNAL);
        led2.Set(LEDOnOffValue2);

#if USE_LEVEL_CONTROL
        DataModel::Nullable<uint8_t> LEDCurrentLevelValue2;
        Status CurrentLevelStatus2 = Clusters::LevelControl::Attributes::CurrentLevel::Get(2, LEDCurrentLevelValue2);
        VerifyOrExit(CurrentLevelStatus2 == Status::Success, err = CHIP_ERROR_INTERNAL);
        led2.SetBrightness(LEDCurrentLevelValue2.Value());
#endif // USE_LEVEL_CONTROL
    }
#endif //CONFIG_MULTIPLE_LIGHT_DEVICE

exit:
    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
    return err;
}

void matter_driver_on_identify_start(Identify *identify)
{
    ChipLogProgress(Zcl, "OnIdentifyStart");
}

void matter_driver_on_identify_stop(Identify *identify)
{
    ChipLogProgress(Zcl, "OnIdentifyStop");
}

void matter_driver_on_trigger_effect(Identify *identify)
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

void matter_driver_uplink_update_handler(AppEvent *aEvent)
{
    chip::app::ConcreteAttributePath path = aEvent->path;

    if (aEvent->path.mEndpointId == 0) {
        return;
    }

    switch (path.mClusterId)
    {
    case Clusters::OnOff::Id:
        if (path.mAttributeId == Clusters::OnOff::Attributes::OnOff::Id)
        {
            if (aEvent->path.mEndpointId == 1) {
                led1.Set(aEvent->value._u8);
            }
#if CONFIG_MULTIPLE_LIGHT_DEVICE
            else if (aEvent->path.mEndpointId == 2) {
                led2.Set(aEvent->value._u8);
            }
#endif // CONFIG_MULTIPLE_LIGHT_DEVICE
        }
        break;
    case Clusters::LevelControl::Id:
        if (path.mAttributeId == Clusters::LevelControl::Attributes::CurrentLevel::Id)
        {
#if USE_LEVEL_CONTROL
            if (aEvent->path.mEndpointId == 1) {
                led1.SetBrightness(aEvent->value._u8);
            }
#if CONFIG_MULTIPLE_LIGHT_DEVICE
            else if (aEvent->path.mEndpointId == 2) {
                led2.SetBrightness(aEvent->value._u8);
            }
#endif // CONFIG_MULTIPLE_LIGHT_DEVICE
#endif // USE_LEVEL_CONTROL
        }
        break;
    case Clusters::Identify::Id:
        break;
    }

exit:
    return;
}

void matter_driver_downlink_update_handler(AppEvent *event)
{
    Status status;
    chip::app::ConcreteAttributePath path = event->path;

    chip::DeviceLayer::PlatformMgr().LockChipStack();

    switch (event->Type)
    {
    case AppEvent::kEventType_Downlink_OnOff:
        {
            if (path.mEndpointId == 1) {
                led1.Toggle();
                ChipLogProgress(DeviceLayer, "Writing to ep1 OnOff cluster");
                status = Clusters::OnOff::Attributes::OnOff::Set(1, led1.IsTurnedOn());
                if (status != Status::Success) {
                    ChipLogError(DeviceLayer, "Updating ep1 on/off cluster failed: %x", status);
                }
#if USE_LEVEL_CONTROL
                ChipLogProgress(DeviceLayer, "Writing to ep1 LevelControl cluster");
                status = Clusters::LevelControl::Attributes::CurrentLevel::Set(1, led2.GetLevel());
                if (status != Status::Success) {
                    ChipLogError(DeviceLayer, "Updating ep1 level cluster failed: %x", status);
                }
#endif // USE_LEVEL_CONTROL
            }
#if CONFIG_MULTIPLE_LIGHT_DEVICE
            else {

                led2.Toggle();
                ChipLogProgress(DeviceLayer, "Writing to ep2 OnOff cluster");
                status = Clusters::OnOff::Attributes::OnOff::Set(2, led2.IsTurnedOn());
                if (status != Status::Success) {
                    ChipLogError(DeviceLayer, "Updating ep2 on/off cluster failed: %x", status);
                }
            }
#if USE_LEVEL_CONTROL
            ChipLogProgress(DeviceLayer, "Writing to ep2 LevelControl cluster");
            status = Clusters::LevelControl::Attributes::CurrentLevel::Set(1, led2.GetLevel());
            if (status != Status::Success) {
                ChipLogError(DeviceLayer, "Updating ep2 level cluster failed: %x", status);
            }
#endif // USE_LEVEL_CONTROL
#endif // CONFIG_MULTIPLE_LIGHT_DEVICE
        }
        break;
    }

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}
