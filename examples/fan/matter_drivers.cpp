#include <matter_drivers.h>
#include <matter_interaction.h>
#include <fan_driver.h>

#include <app-common/zap-generated/attribute-type.h>
#include <app-common/zap-generated/attributes/Accessors.h>
#include <app-common/zap-generated/ids/Attributes.h>
#include <app-common/zap-generated/ids/Clusters.h>
#include <protocols/interaction_model/StatusCode.h>

using namespace ::chip::app;
using chip::Protocols::InteractionModel::Status;

#if defined(CONFIG_PLATFORM_8710C)
#define PWM_PIN         PA_23
#elif defined(CONFIG_PLATFORM_8721D)
#define PWM_PIN         PB_5
#endif

CHIP_ERROR matter_driver_fan_init(void)
{
    return CHIP_NO_ERROR;
}

CHIP_ERROR matter_driver_fan_set_startup_value(void)
{

    return CHIP_NO_ERROR;
}

void matter_driver_uplink_update_handler(AppEvent *aEvent)
{
    chip::app::ConcreteAttributePath path = aEvent->path;
    // this example only considers endpoint 1
    VerifyOrExit(aEvent->path.mEndpointId == 1,
                 ChipLogError(DeviceLayer, "Unexpected EndPoint ID: `0x%02x'", path.mEndpointId));

    switch (path.mClusterId)
    {
    case Clusters::Identify::Id:
        break;
    }

exit:
    return;
}

void matter_driver_downlink_update_handler(AppEvent *event)
{
    chip::DeviceLayer::PlatformMgr().LockChipStack();

    switch (event->Type)
    {
    default:
        break;
    }

    chip::DeviceLayer::PlatformMgr().UnlockChipStack();
}
