# Temperature Sensor Example
This example is an implementation of the *Temperature Sensor* device type, check the GPIO Pin Configuration below.

## ZAP
Since a specific ZAP file for the temperature sensor device type is not available, we will utilize temp-sensor-app.zap as a substitute.

##Functionality
The temperature sensor is designed to measure temperature through an external physical sensor. However, in this example, a static value is read and reported to the Matter Controller via the `downlink` task and handler.

In `matter_drivers.cpp`:

- `matter_driver_temperature_sensor_init`: Configures the endpoint based on the ZAP settings, sets initial values such as MinMeasuredValue and MaxMeasuredValue, and creates a task for reading the temperature sensor measurements.
- `matter_driver_take_measurement`: Takes temperature measurements every 10 seconds, with the timing adjustable to meet specific sensor requirements.
- `matter_driver_downlink_update_handler`: Updates the temperature value to the Matter layer (Controller).
- `matter_driver_uplink_update_handler`: Updates from Matter Controller so that DUT can update its status. This is not needed for a temperature sensor device type.

### Peripheral Initialization
Both the initializations of the temperature sensor are handled in `matter_drivers.cpp`.

## How to build

### Configurations
Enable `CONFIG_EXAMPLE_MATTER` and `CONFIG_EXAMPLE_MATTER_TEMP_SENSOR` in `platform_opts_matter.h`.
Ensure that `CONFIG_EXAMPLE_MATTER_CHIPTEST` is disabled.

### Setup the Build Environment

    cd connectedhomeip
    source scripts/activate.sh

<details>
  <summary>Building with AmebaZ2</summary>

### AmebaZ2 (RTL8710C)

#### GPIO Pin Configuration

| Peripheral         | Pin   |
| ------------------ | ----- |
| Temperature Sensor | PA_19 |

#### Build Matter Libraries

    cd ambz2_matter/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make temp_sensor_port

#### Build the Final Firmware

    cd ambz2_matter/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make is_matter

#### Flash the Image
Refer to this [guide](https://github.com/ambiot/ambz2_matter/blob/main/tools/AmebaZ2/Image_Tool_Linux/README.md) to flash the image with the Linux Image Tool

#### Clean Matter Libraries

    cd ambz2_matter/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make clean_matter_libs

#### Clean Ameba Matter application

    cd ambz2_matter/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make clean_matter

</details>

<details>
  <summary>Building with AmebaD</summary>

### AmebaD (RTL8721D)

#### GPIO Pin Configuration

| Peripheral | Pin   |
| ---------- | ----- |
| Fan        | PB_5  |

#### Build Matter Libraries

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp
    make -C asdk temp_sensor_port
    
#### Build the Final Firmware

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_lp
    make all
    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp
    make all
    
#### Flash the Image
Refer to this [guide](https://github.com/ambiot/ambd_matter/blob/main/tools/AmebaD/Image_Tool_Linux/README.txt) to flash the image with the Linux Image Tool

#### Clean Matter Libraries and Firmware

    cd ambd_matter/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp
    make clean

</details>
