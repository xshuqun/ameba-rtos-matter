# Matter Room Air Conditioner Example

This example demonstrates an implementation of the **Matter Room Air Conditioner** device type  
(**Device Type ID:** `0x0072`).

It uses the **`aircon-app.zap`** configuration file to define clusters and endpoints for a Matter-compliant air conditioner device.  
This example can serve as a reference for developers implementing thermostat and fan control functionalities.

## 📘 ZAP Configuration

- **ZAP File:** `aircon-app.zap`  
- **Device Type ID:** `0x0072` (Room Air Conditioner)

> **Note:**  
> Before implementation, review the Matter Specification to ensure compliance with required device types and cluster configurations.

## 🧩 Endpoint Configuration

The example defines **three endpoints**:

| **Endpoint ID** | **Device Name**        | **Description** |
|-----------------|------------------------|-----------------|
| **1** | Room Air Conditioner | Main functional endpoint controlling HVAC features |
| **2** | Humidity Sensor | Optional endpoint for humidity measurement |
| **3** | Temperature Sensor | Optional endpoint for temperature measurement |

> **Note:**  
> The Humidity and Temperature Sensor endpoints are included for demonstration purposes.  
> You may exclude or modify them according to your device requirements.

## 🔧 Supported Clusters

The following clusters are included in this example:

| **Cluster Name** | **Function** | **Role** |
|------------------|--------------|-----------|
| **On/Off** | Powers the device on or off | Server |
| **Thermostat** | Controls and reports temperature settings | Server |
| **Fan Control** | Adjusts fan mode and speed | Server |

> These clusters collectively allow control of power state, temperature, and fan behavior for a Room Air Conditioner.

## Example Implementation

### 🌀 Cluster Control

This example demonstrates how to integrate a PWM-based **Fan** and a **Temperature/Humidity Sensor** within a Matter device.

---

### 🔁 Attribute Change Handling

The **Attribute Change Handling** layer manages synchronization between the Matter data model and the hardware drivers.  
It ensures that updates from the Matter controller or from external inputs remain consistent across the entire system.

There are two modes of control:

1. **Matter Controller** – Controlled through a connected Matter controller (e.g., mobile app, hub, or test tool).  
2. **External Control** – Managed through a physical input, such as a button press, with real-time state synchronization to Matter.


#### 🧭 Matter Controller–Driven Updates

When the Matter controller updates an attribute (e.g., **FanMode**, **FanSpeed**, or **OnOff**), two callbacks are invoked:

1. **`MatterPreAttributeChangeCallback`** – Triggered *before* the attribute is updated.  
   Use this for validation, filtering, or pre-update logic.

2. **`MatterPostAttributeChangeCallback`** – Triggered *after* the attribute has been written to the Matter data model.

`MatterPostAttributeChangeCallback` is defined in **`core/matter_interaction.cpp`**.  
They post events to the **uplink queue**, which are then handled by **`matter_driver_uplink_update_handler`** in **`matter_drivers.cpp`**.

The handler interprets the **Cluster ID** and **Attribute ID**, then performs the corresponding driver action.

> **Note:**  
> Modify the action to be taken in `matter_driver_uplink_update_handler` for application-specific logic.

#### 🔘 External or Physical Control

External hardware inputs (e.g., buttons or sensors) can also modify attributes within the Matter stack.

When a button is pressed, the **GPIO interrupt handler** posts an event to the **downlink queue**, which is processed by **`matter_driver_downlink_update_handler`**.

**Implementation Steps:**

1. In **`matter_drivers.cpp`**, configure the GPIO pin.
2. In the GPIO interrupt callback , create and post an event to the downlink queue.
3. In **`matter_driver_downlink_update_handler`**, define how the event modifies Matter attributes.

> **Example Use Case:**  
> A button press toggles the **On/Off** cluster state locally, and the change is propagated to all connected Matter controllers.

This ensures full synchronization between **physical inputs** and **digital Matter control**, maintaining consistent device state across all interfaces.

---

### ⚙️ Peripheral Initialization

Initialization for the fan and temperature/humidity sensor is handled in **`matter_drivers.cpp`**.  
This file contains low-level hardware setup routines and driver initialization code executed during system startup.

---

### 🧠 Implemented Driver APIs

The following APIs are implemented in **`matter_drivers.cpp`**.  
They provide the main interfaces for peripheral initialization, event handling, and attribute synchronization between the Matter stack and device hardware.

| **API / Task** | **Purpose** | **Function / Description** |
|----------------|------------|---------------------------|
| `matter_driver_room_aircon_init()` | Device initialization | Initializes the Room Air Conditioner device and calls sub-component initializations: `matter_driver_fan_init()`, `matter_driver_humidity_sensor_init()`, and `matter_driver_temperature_sensor_init()` |
| `matter_driver_fan_init()` | Fan initialization | Configures Fan Control cluster and synchronizes Matter attributes with fan hardware |
| `matter_driver_humidity_sensor_init()` | Humidity sensor initialization | Configures Relative Humidity Measurement cluster and synchronizes Matter attributes with sensor hardware |
| `matter_driver_temperature_sensor_init()` | Temperature sensor initialization | Configures Temperature Measurement cluster and synchronizes Matter attributes with sensor hardware |
| `matter_driver_set_measured_temp_cb()` | Temperature callback | Registers a callback function to handle temperature readings |
| `matter_driver_set_measured_humidity_cb()` | Humidity callback | Registers a callback function to handle humidity readings |
| `matter_driver_take_measurement` | Sensor measurement task | Periodically reads temperature and humidity values and triggers registered callbacks |
| `matter_driver_uplink_update_handler()` | Matter → Driver event handler | Processes cluster/attribute changes from the Matter stack (uplink) and updates hardware peripherals |
| `matter_driver_downlink_update_handler()` | Driver → Matter event handler | Processes hardware or external input events (downlink) and updates Matter attributes |
| `matter_driver_on_identify_start()` | Identify start | Notifies that the identify operation has started |
| `matter_driver_on_identify_stop()` | Identify stop | Notifies that the identify operation has stopped |
| `matter_driver_on_trigger_effect()` | Identify device | Triggers a visual or functional effect to identify the device |

---

### 🧩 Summary

| **Component** | **Description** |
|----------------|-----------------|
| **ZAP File** | `aircon-app.zap` |
| **Main Driver File** | `matter_drivers.cpp` |
| **Callback Definitions** | `core/matter_interaction.cpp` |
| **Control Methods** | Matter Controller (uplink) and External Input (downlink) |
| **Optional Extension** | Add support for additional clusters, sensors, or application-specific logic |

---

### 💡 Notes

- Modify the configuration based on your implementation requirements.  
- Ensure that corresponding actions are defined for each attribute callback or external control input to keep the Matter data model and hardware in sync.


## How to build

### Configurations
Enable `CONFIG_EXAMPLE_MATTER` and `CONFIG_EXAMPLE_MATTER_AIRCON` in `platform_opts_matter.h`.
Ensure that `CONFIG_EXAMPLE_MATTER_CHIPTEST` is disabled.

### Setup the Build Environment
  
    cd connectedhomeip
    source scripts/activate.sh

<details>
  <summary>Building with AmebaZ2</summary>

### AmebaZ2 (RTL8710C)

#### GPIO Pin Configuration

| Peripheral | Pin   |
| ---------- | ----- |
| Fan        | PA_23 |
| Sensor     | Depends on type of sensor |

#### Build Matter Libraries

    cd amebaz2_sdk/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make aircon_port
    
#### Build the Final Firmware

    cd amebaz2_sdk/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make is_matter
    
#### Flash the Image
Refer to this [guide](https://github.com/Ameba-AIoT/ameba-rtos-matter/tree/release/v1.4/tools/Image_Tool_Linux/AmebaZ2/README.md) to flash the image with the Linux Image Tool

#### Clean Matter Libraries

    cd amebaz2_sdk/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make clean_matter_libs

#### Clean Ameba Matter application

    cd amebaz2_sdk/project/realtek_amebaz2_v0_example/GCC-RELEASE/
    make clean_matter

</details>

<details>
  <summary>Building with AmebaD</summary>

### AmebaD (RTL8721D)

#### GPIO Pin Configuration

| Peripheral | Pin   |
| ---------- | ----- |
| Fan        | PB_5  |
| Sensor     | Depends on type of sensor |
  
#### Build Matter Libraries

    cd amebad_sdk/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp
    make -C asdk aircon_port
    
#### Build the Final Firmware

    cd amebad_sdk/project/realtek_amebaD_va0_example/GCC-RELEASE/project_lp
    make all
    cd amebad_sdk/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp
    make all
    
#### Flash the Image
Refer to this [guide](https://github.com/Ameba-AIoT/ameba-rtos-matter/tree/release/v1.4/tools/Image_Tool_Linux/AmebaD/README.md) to flash the image with the Linux Image Tool

#### Clean Matter Libraries and Firmware

    cd amebad_sdk/project/realtek_amebaD_va0_example/GCC-RELEASE/project_hp
    make clean
</details>