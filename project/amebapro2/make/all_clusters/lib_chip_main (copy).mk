SHELL = /bin/bash
OS := $(shell uname)

# Directory
# -------------------------------------------------------------------

SDKROOTDIR         := $(shell pwd)/../../..
CHIPDIR             = $(SDKROOTDIR)/third_party/connectedhomeip
OUTPUT_DIR          = $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip
CODEGENDIR          = $(OUTPUT_DIR)/codegen

# Initialize tool chain
# -------------------------------------------------------------------

CROSS_COMPILE = arm-none-eabi-

# Compilation tools
# -------------------------------------------------------------------

AR = $(CROSS_COMPILE)ar
CC = $(CROSS_COMPILE)gcc
CPP = $(CROSS_COMPILE)g++
AS = $(CROSS_COMPILE)as
NM = $(CROSS_COMPILE)nm
LD = $(CROSS_COMPILE)gcc
GDB = $(CROSS_COMPILE)gdb
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

# Build Definition
# -------------------------------------------------------------------

CHIP_ENABLE_OTA_REQUESTOR = $(shell grep 'chip_enable_ota_requestor' $(OUTPUT_DIR)/args.gn | cut -d' ' -f3)

# Initialize target name and target object files
# -------------------------------------------------------------------

all: lib_main

TARGET=lib_main

OBJ_DIR=$(TARGET)/Debug/obj
BIN_DIR=$(TARGET)/Debug/bin
INFO_DIR=$(TARGET)/Debug/info

# Include folder list
# -------------------------------------------------------------------

INCLUDES =
INCLUDES += -I$(SDKROOTDIR)/project/realtek_amebapro2_v0_example/inc

INCLUDES += -I$(SDKROOTDIR)/component/mbed/hal
INCLUDES += -I$(SDKROOTDIR)/component/mbed/hal_ext
INCLUDES += -I$(SDKROOTDIR)/component/mbed/targets/hal/rtl8735b
INCLUDES += -I$(SDKROOTDIR)/component/mbed/api
INCLUDES += -I$(SDKROOTDIR)/component/stdlib
INCLUDES += -I$(SDKROOTDIR)/component/at_cmd
INCLUDES += -I$(SDKROOTDIR)/component/network
INCLUDES += -I$(SDKROOTDIR)/component/network/cJSON
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/cmsis/cmsis-core/include
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/cmsis/rtl8735b/lib/include
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/cmsis/rtl8735b/include
    
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/include
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/source/ram_ns/halmac/halmac_88xx
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/host/storage/inc/quirks
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/device/class/ethernet/inc
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/source/ram_ns/halmac/halmac_88xx/halmac_8822b
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/include
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/device/class/ethernet/src
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/device/core/inc
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/source/ram_ns/halmac/halmac_88xx/halmac_8735b
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/source/ram_ns/halmac/halmac_88xx_v1
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/device/class/vendor/inc
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/host/storage/inc
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/host/storage/inc/scatterlist
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/source/ram_ns/halmac/halmac_88xx/halmac_8821c
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/host/vendor_spec
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/source/ram_ns/halmac
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/source/ram_ns/halmac/halmac_88xx_v1/halmac_8814b
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/host/storage/inc/scsi
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/inc
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/source/ram_ns/halmac/halmac_88xx/halmac_8195b
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/usb_otg/device
    
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/misc/utilities/include
    
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/app/stdio_port
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/app/xmodem/rom
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/app/shell
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/app/shell/rom_ns
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/app/rtl_printf/include
    
INCLUDES += -I$(SDKROOTDIR)/component/os/os_dep/include
INCLUDES += -I$(SDKROOTDIR)/component/os/freertos
INCLUDES += -I$(SDKROOTDIR)/component/os/freertos/freertos_v202012.00/Source/include
    
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/include
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/src/osdep
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/src/phl
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/src/hal
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/src/hal/halmac
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/src/hci
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/src/hal/phydm/rtl8735b
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/src/hal/phydm
INCLUDES += -I$(SDKROOTDIR)/component/wifi/wpa_supplicant/wpa_supplicant

INCLUDES += -I$(SDKROOTDIR)/component/os/freertos/freertos_posix/lib/include/FreeRTOS_POSIX
INCLUDES += -I$(SDKROOTDIR)/component/os/freertos/freertos_posix/lib/include
INCLUDES += -I$(SDKROOTDIR)/component/os/freertos/freertos_posix/lib/FreeRTOS-Plus-POSIX/include/portable/realtek/rtl8735b
INCLUDES += -I$(SDKROOTDIR)/component/os/freertos/freertos_posix/lib/FreeRTOS-Plus-POSIX/include
INCLUDES += -I$(SDKROOTDIR)/component/os/freertos/freertos_posix/lib/include/private
    
INCLUDES += -I$(SDKROOTDIR)/component/lwip/api
INCLUDES += -I$(SDKROOTDIR)/component/lwip/lwip_v2.1.2/src/include
INCLUDES += -I$(SDKROOTDIR)/component/lwip/lwip_v2.1.2/src/include/lwip
INCLUDES += -I$(SDKROOTDIR)/component/lwip/lwip_v2.1.2/src/include/compat/posix
INCLUDES += -I$(SDKROOTDIR)/component/lwip/lwip_v2.1.2/port/realtek
INCLUDES += -I$(SDKROOTDIR)/component/lwip/lwip_v2.1.2/port/realtek/freertos

INCLUDES += -I$(SDKROOTDIR)/component/ssl/mbedtls-2.28.1/include
INCLUDES += -I$(SDKROOTDIR)/component/ssl/ssl_ram_map/rom
    

INCLUDES += -I$(SDKROOTDIR)/component/usb/usb_class/device/class
INCLUDES += -I$(SDKROOTDIR)/component/usb/usb_class/device
INCLUDES += -I$(SDKROOTDIR)/component/usb/usb_class/host/uvc/inc
INCLUDES += -I$(SDKROOTDIR)/component/video/driver/common
INCLUDES += -I$(SDKROOTDIR)/component/video/driver/RTL8735B
INCLUDES += -I$(SDKROOTDIR)/component/media/rtp_codec
INCLUDES += -I$(SDKROOTDIR)/component/media/samples
	
INCLUDES += -I$(SDKROOTDIR)/component/media/mmfv2
    
INCLUDES += -I$(SDKROOTDIR)/component/wifi/api
INCLUDES += -I$(SDKROOTDIR)/component/wifi/wifi_config
INCLUDES += -I$(SDKROOTDIR)/component/wifi/wifi_fast_connect
	
INCLUDES += -I$(SDKROOTDIR)/component/sdio/sd_host/inc
INCLUDES += -I$(SDKROOTDIR)/component/file_system/fatfs
INCLUDES += -I$(SDKROOTDIR)/component/file_system/fatfs/r0.14
INCLUDES += -I$(SDKROOTDIR)/component/file_system/ftl_common
INCLUDES += -I$(SDKROOTDIR)/component/file_system/vfs
	
INCLUDES += -I$(SDKROOTDIR)/component/file_system/littlefs
INCLUDES += -I$(SDKROOTDIR)/component/file_system/littlefs/r2.41
	
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/faac/libfaac
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/faac/include
	
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/haac
INCLUDES += -I$(SDKROOTDIR)/component/media/muxer
	
INCLUDES += -I$(SDKROOTDIR)/component/media/3rdparty/fmp4/libmov/include
INCLUDES += -I$(SDKROOTDIR)/component/media/3rdparty/fmp4/libflv/include
	
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/cmsis/cmsis-dsp/include
	
INCLUDES += -I$(SDKROOTDIR)/component/application/qr_code_scanner/inc
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/speex/speex
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/AEC/AEC
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/opus-1.3.1/include
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/libopusenc-0.2.1/include
	
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/video
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/video/semihost
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/cmsis/voe/rom

INCLUDES += -I$(SDKROOTDIR)/component/os/freertos/freertos_v202012.00/Source/portable/GCC/ARM_CM33/non_secure
INCLUDES += -I$(SDKROOTDIR)/component/os/freertos/freertos_v202012.00/Source/portable/GCC/ARM_CM33/secure
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/video/voe_bin
INCLUDES += -I$(SDKROOTDIR)/component/video/driver/RTL8735B

INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/nn
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/nn/model_itp
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/nn/nn_api
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/nn/nn_postprocess
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/nn/nn_preprocess
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/nn/run_facerecog
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/nn/run_itp	
	
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/misc/platform

INCLUDES += -I$(SDKROOTDIR)/component/media/mmfv2
INCLUDES += -I$(SDKROOTDIR)/component/media/rtp_codec
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/AEC
INCLUDES += -I$(SDKROOTDIR)/component/mbed/hal_ext
INCLUDES += -I$(SDKROOTDIR)/component/file_system/dct
INCLUDES += -I$(SDKROOTDIR)/component/file_system/ftl
INCLUDES += -I$(SDKROOTDIR)/component/file_system/system_data
INCLUDES += -I$(SDKROOTDIR)/component/file_system/fwfs

INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/driver
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/driver/hci
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/driver/inc
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/driver/inc/hci
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/driver/platform/amebapro2/inc
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/os/osif
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/app
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/bluetooth/gap
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/bluetooth/profile
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/bluetooth/profile/client
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/bluetooth/profile/server
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/framework/bt
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/framework/remote
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/framework/sys
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/os
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/platform
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/inc/stack
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/src/ble/privacy
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/platform/amebapro2/inc
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/platform/amebapro2/lib
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/platform/amebapro2/src/vendor_cmd
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/platform/common/inc
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/ble_central
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/ble_peripheral
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/ble_scatternet
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/bt_beacon
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/bt_config
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/bt_airsync_config
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/bt_mesh/provisioner
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/bt_mesh/device
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/bt_mesh_multiple_profile/provisioner_multiple_profile
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/bt_mesh_multiple_profile/device_multiple_profile
INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/bt_mesh_test

INCLUDES += -I$(SDKROOTDIR)/component/wifi/wpa_supplicant/src
INCLUDES += -I$(SDKROOTDIR)/component/network/mqtt/MQTTClient
INCLUDES += -I$(SDKROOTDIR)/component/network/mqtt/MQTTPacket
INCLUDES += -I$(SDKROOTDIR)/component/network/tftp
INCLUDES += -I$(SDKROOTDIR)/component/network/ftp

INCLUDES += -I$(SDKROOTDIR)/component/example/media_framework/inc

INCLUDES += -I$(SDKROOTDIR)/component/wifi/wpa_supplicant/src
INCLUDES += -I$(SDKROOTDIR)/component/wifi/driver/src/core/option
INCLUDES += -I$(SDKROOTDIR)/component/ssl/ssl_ram_map/rom
INCLUDES += -I$(SDKROOTDIR)/component/audio/3rdparty/faac/libfaac

INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/fwlib/rtl8735b/lib/source/ram/video/osd
INCLUDES += -I$(SDKROOTDIR)/component/video/osd2
INCLUDES += -I$(SDKROOTDIR)/component/video/eip
INCLUDES += -I$(SDKROOTDIR)/component/video/md
INCLUDES += -I$(SDKROOTDIR)/component/wifi/wifi_config
	
INCLUDES += -I$(SDKROOTDIR)/component/media/framework
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/misc/driver
INCLUDES += -I$(SDKROOTDIR)/component/soc/8735b/misc/driver/xmodem

INCLUDES += -I$(SDKROOTDIR)/component/network/coap/include
	
INCLUDES += -I$(SDKROOTDIR)/component/usb/common_new/
INCLUDES += -I$(SDKROOTDIR)/component/usb/host_new/
INCLUDES += -I$(SDKROOTDIR)/component/usb/host_new/cdc_ecm
INCLUDES += -I$(SDKROOTDIR)/component/usb/host_new/core
INCLUDES += -I$(SDKROOTDIR)/component/usb/device_new/core
INCLUDES += -I$(SDKROOTDIR)/component/usb/

INCLUDES += -I$(SDKROOTDIR)/component/bluetooth/rtk_stack/example/ble_matter_adapter
INCLUDES += -I$(SDKROOTDIR)/component/application/matter/api
INCLUDES += -I$(SDKROOTDIR)/component/application/matter/common/include
INCLUDES += -I$(SDKROOTDIR)/component/application/matter/common/bluetooth
INCLUDES += -I$(SDKROOTDIR)/component/application/matter/common/mbedtls
INCLUDES += -I$(SDKROOTDIR)/component/application/matter/common/port

# CHIP Include folder list
# -------------------------------------------------------------------

INCLUDES += -I$(CHIPDIR)/examples/platform/ameba
INCLUDES += -I$(CHIPDIR)/examples/providers
INCLUDES += -I$(CHIPDIR)/src
INCLUDES += -I$(CHIPDIR)/src/app
INCLUDES += -I$(CHIPDIR)/src/app/util
INCLUDES += -I$(CHIPDIR)/src/app/server
INCLUDES += -I$(CHIPDIR)/src/app/clusters/bindings
INCLUDES += -I$(CHIPDIR)/src/controller/data_model
INCLUDES += -I$(CHIPDIR)/src/include
INCLUDES += -I$(CHIPDIR)/src/lib
INCLUDES += -I$(CHIPDIR)/third_party/nlassert/repo/include
INCLUDES += -I$(CHIPDIR)/third_party/nlio/repo/include
INCLUDES += -I$(CHIPDIR)/third_party/nlunit-test/repo/src
INCLUDES += -I$(CHIPDIR)/zzz_generated/app-common
INCLUDES += -I$(CHIPDIR)/zzz_generated/all-clusters-app
INCLUDES += -I$(CHIPDIR)/zzz_generated/all-clusters-app/zap-generated
INCLUDES += -I$(CHIPDIR)/examples/all-clusters-app/all-clusters-common
INCLUDES += -I$(CHIPDIR)/examples/all-clusters-app/all-clusters-common/include
INCLUDES += -I$(CHIPDIR)/examples/all-clusters-app/ameba/main/include
INCLUDES += -I$(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/gen/include
INCLUDES += -I$(CHIPDIR)/examples/microwave-oven-app/microwave-oven-common/include
INCLUDES += -I$(CODEGENDIR)

# Source file list
# -------------------------------------------------------------------

SRC_C =
SRC_C += $(CHIPDIR)/examples/platform/ameba/route_hook/ameba_route_hook.c
SRC_C += $(CHIPDIR)/examples/platform/ameba/route_hook/ameba_route_table.c

SRC_CPP = 
SRC_CPP += $(CHIPDIR)/examples/providers/DeviceInfoProviderImpl.cpp

SRC_CPP += $(CHIPDIR)/src/app/server/AclStorage.cpp
SRC_CPP += $(CHIPDIR)/src/app/server/DefaultAclStorage.cpp
SRC_CPP += $(CHIPDIR)/src/app/server/EchoHandler.cpp
SRC_CPP += $(CHIPDIR)/src/app/server/Dnssd.cpp
SRC_CPP += $(CHIPDIR)/src/app/server/OnboardingCodesUtil.cpp
SRC_CPP += $(CHIPDIR)/src/app/server/Server.cpp
SRC_CPP += $(CHIPDIR)/src/app/server/CommissioningWindowManager.cpp

SRC_CPP += $(CHIPDIR)/src/app/util/attribute-storage.cpp
SRC_CPP += $(CHIPDIR)/src/app/util/attribute-table.cpp
SRC_CPP += $(CHIPDIR)/src/app/util/binding-table.cpp
SRC_CPP += $(CHIPDIR)/src/app/util/DataModelHandler.cpp
SRC_CPP += $(CHIPDIR)/src/app/util/ember-compatibility-functions.cpp
SRC_CPP += $(CHIPDIR)/src/app/util/generic-callback-stubs.cpp
SRC_CPP += $(CHIPDIR)/src/app/util/util.cpp
SRC_CPP += $(CHIPDIR)/src/app/util/privilege-storage.cpp

SRC_CPP += $(CHIPDIR)/src/app/reporting/Engine.cpp
SRC_CPP += $(CHIPDIR)/src/app/reporting/reporting.cpp

SRC_CPP += $(shell cat $(CODEGENDIR)/cluster-file.txt)

SRC_CPP += $(CODEGENDIR)/app/callback-stub.cpp
SRC_CPP += $(CODEGENDIR)/app/cluster-init-callback.cpp
SRC_CPP += $(CODEGENDIR)/zap-generated/IMClusterCommandHandler.cpp

SRC_CPP += $(CHIPDIR)/zzz_generated/app-common/app-common/zap-generated/attributes/Accessors.cpp
SRC_CPP += $(CHIPDIR)/zzz_generated/app-common/app-common/zap-generated/cluster-objects.cpp

# all-clusters-app clusters source files
SRC_CPP += $(CHIPDIR)/examples/all-clusters-app/all-clusters-common/src/static-supported-modes-manager.cpp

# all-clusters-app ameba source files
SRC_CPP += $(CHIPDIR)/examples/all-clusters-app/ameba/main/chipinterface.cpp
SRC_CPP += $(CHIPDIR)/examples/all-clusters-app/ameba/main/ManualOperationCommand.cpp
SRC_CPP += $(CHIPDIR)/examples/all-clusters-app/ameba/main/DeviceCallbacks.cpp
SRC_CPP += $(CHIPDIR)/examples/all-clusters-app/ameba/main/SmokeCOAlarmManager.cpp
SRC_CPP += $(CHIPDIR)/examples/all-clusters-app/ameba/main/CHIPDeviceManager.cpp
SRC_CPP += $(CHIPDIR)/examples/all-clusters-app/ameba/main/Globals.cpp
SRC_CPP += $(CHIPDIR)/examples/all-clusters-app/ameba/main/LEDWidget.cpp

ifeq ($(CHIP_ENABLE_OTA_REQUESTOR), true)
SRC_CPP += $(CHIPDIR)/examples/platform/ameba/ota/OTAInitializer.cpp
endif
SRC_CPP += $(CHIPDIR)/examples/platform/ameba/shell/launch_shell.cpp
SRC_CPP += $(CHIPDIR)/examples/platform/ameba/test_event_trigger/AmebaTestEventTriggerDelegate.cpp

SRC_CPP += $(SDKROOTDIR)/component/application/matter/api/matter_api.cpp
SRC_C += $(SDKROOTDIR)/component/application/matter/example/chiptest/example_matter.c

#lib_version
VER_C += $(TARGET)_version.c

# Generate obj list
# -------------------------------------------------------------------

SRC_O = $(patsubst %.c,%_$(TARGET).o,$(SRC_C))
VER_O = $(patsubst %.c,%_$(TARGET).o,$(VER_C))

SRC_C_LIST = $(notdir $(SRC_C)) $(notdir $(DRAM_C))
OBJ_LIST = $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%_$(TARGET).o,$(SRC_C_LIST)))
DEPENDENCY_LIST = $(addprefix $(OBJ_DIR)/,$(patsubst %.c,%_$(TARGET).d,$(SRC_C_LIST)))

SRC_OO += $(patsubst %.cpp,%_$(TARGET).oo,$(SRC_CPP))
SRC_CPP_LIST = $(notdir $(SRC_CPP))
OBJ_CPP_LIST = $(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%_$(TARGET).oo,$(SRC_CPP_LIST)))
DEPENDENCY_LIST += $(addprefix $(OBJ_DIR)/,$(patsubst %.cpp,%_$(TARGET).d,$(SRC_CPP_LIST)))

# Compile options
# -------------------------------------------------------------------

CFLAGS =
CFLAGS += -march=armv8-m.main+dsp -mthumb -mcmse -mfpu=fpv5-sp-d16 -mfp16-format=ieee -mfloat-abi=softfp -fno-common -fsigned-char
CFLAGS += -Os -fstack-usage -fdata-sections -ffunction-sections  -fno-optimize-sibling-calls
CFLAGS += -g -gdwarf-3 -MMD -nostartfiles -nodefaultlibs -nostdlib

CFLAGS += -D__thumb2__ -DCONFIG_PLATFORM_8735B -DARM_MATH_ARMV8MML -D__FPU_PRESENT -D__ARM_ARCH_7M__=0 
CFLAGS += -D__ARM_ARCH_7EM__=0 -D__ARM_ARCH_8M_MAIN__=1 -D__ARM_ARCH_8M_BASE__=0 
CFLAGS += -D__ARM_FEATURE_FP16_SCALAR_ARITHMETIC=1 -D__DSP_PRESENT=1 -D__ARMVFP__

CFLAGS += -fdiagnostics-color=always

# CHIP options
# -------------------------------------------------------------------
CFLAGS += -DCHIP_PROJECT=1
CFLAGS += -DCONFIG_MATTER=1
CFLAGS += -DCONFIG_MATTER_BLEMGR_ADAPTER=1
CFLAGS += -DCONFIG_ENABLE_OTA_REQUESTOR=1
CFLAGS += -DCONFIG_ENABLE_CHIP_SHELL=1
CFLAGS += -DCONFIG_ENABLE_AMEBA_FACTORY_DATA=0
CFLAGS += -DCONFIG_ENABLE_AMEBA_TEST_EVENT_TRIGGER=0
CFLAGS += -DCHIP_DEVICE_LAYER_TARGET=Ameba
CFLAGS += -DMBEDTLS_CONFIG_FILE=\"mbedtls_config.h\"
CFLAGS += -DCHIP_ADDRESS_RESOLVE_IMPL_INCLUDE_HEADER=\"lib/address_resolve/AddressResolve_DefaultImpl.h\"

CFLAGS += -DLWIP_IPV6_ND=1
CFLAGS += -DLWIP_IPV6_SCOPES=0
CFLAGS += -DLWIP_PBUF_FROM_CUSTOM_POOLS=0
CFLAGS += -DLWIP_IPV6_ROUTE_TABLE_SUPPORT=1

CFLAGS += -DCHIP_DEVICE_LAYER_NONE=0
CFLAGS += -DCHIP_SYSTEM_CONFIG_USE_ZEPHYR_NET_IF=0
CFLAGS += -DCHIP_SYSTEM_CONFIG_USE_BSD_IFADDRS=0
CFLAGS += -DCHIP_SYSTEM_CONFIG_USE_ZEPHYR_SOCKET_EXTENSIONS=0

CFLAGS += -DCHIP_SYSTEM_CONFIG_USE_LWIP=1
CFLAGS += -DCHIP_SYSTEM_CONFIG_USE_SOCKETS=0
CFLAGS += -DCHIP_SYSTEM_CONFIG_USE_NETWORK_FRAMEWORK=0
CFLAGS += -DCHIP_SYSTEM_CONFIG_POSIX_LOCKING=0
CFLAGS += -DINET_CONFIG_ENABLE_IPV4=0
CFLAGS += -DCHIP_SHELL_MAX_TOKENS=11

CFLAGS += -DUSE_ZAP_CONFIG
CFLAGS += -DCHIP_HAVE_CONFIG_H

CPPFLAGS := $(CFLAGS)

CPPFLAGS += -DFD_SETSIZE=10
CPPFLAGS += -Wno-sign-compare
CPPFLAGS += -Wno-unused-function
CPPFLAGS += -Wno-unused-but-set-variable
CPPFLAGS += -Wno-unused-variable
CPPFLAGS += -Wno-deprecated-declarations
CPPFLAGS += -Wno-unused-parameter
CPPFLAGS += -Wno-format

CPPFLAGS += -std=gnu++17
CPPFLAGS += -fno-rtti

# Compile
# -------------------------------------------------------------------

.PHONY: lib_main
lib_main: prerequirement $(SRC_O) $(DRAM_O) $(SRC_OO)
	$(AR) crv $(BIN_DIR)/$(TARGET).a $(OBJ_CPP_LIST) $(OBJ_LIST) $(VER_O)
	cp $(BIN_DIR)/$(TARGET).a ../../../project/realtek_amebapro2_v0_example/GCC-RELEASE/application/output/$(TARGET).a

# Manipulate Image
# -------------------------------------------------------------------

.PHONY: manipulate_images
manipulate_images:
	@echo ===========================================================
	@echo Image manipulating
	@echo ===========================================================

# Generate build info
# -------------------------------------------------------------------

.PHONY: prerequirement
prerequirement:
	@rm -f $(TARGET)_version*.o
	@echo const char $(TARGET)_rev[] = \"$(TARGET)_ver_`git rev-parse HEAD`_`date +%Y/%m/%d-%T`\"\; > $(TARGET)_version.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $(VER_C) -o $(VER_O)
	@echo ===========================================================
	@echo Build $(TARGET)
	@echo ===========================================================
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(INFO_DIR)

$(SRC_OO): %_$(TARGET).oo : %.cpp | prerequirement
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	$(CPP) $(CPPFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.oo,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	#cp $*_$(TARGET).ii $(INFO_DIR)
	#cp $*_$(TARGET).s $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

$(SRC_O): %_$(TARGET).o : %.c | prerequirement
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.o,%.d,$@))
	cp $@ $(OBJ_DIR)/$(notdir $@)
	#cp $*_$(TARGET).i $(INFO_DIR)
	#cp $*_$(TARGET).s $(INFO_DIR)
	chmod 777 $(OBJ_DIR)/$(notdir $@)

-include $(DEPENDENCY_LIST)

.PHONY: clean
clean:
	rm -rf $(TARGET)
	rm -f $(SRC_O) $(DRAM_O) $(VER_O) $(SRC_OO)
	rm -f $(patsubst %.o,%.d,$(SRC_O)) $(patsubst %.o,%.d,$(DRAM_O)) $(patsubst %.o,%.d,$(VER_O)) $(patsubst %.oo,%.d,$(SRC_OO))
	rm -f $(patsubst %.o,%.su,$(SRC_O)) $(patsubst %.o,%.su,$(DRAM_O)) $(patsubst %.o,%.su,$(VER_O)) $(patsubst %.oo,%.su,$(SRC_OO))
	rm -f $(patsubst %.o,%.i,$(SRC_O)) $(patsubst %.o,%.i,$(DRAM_O)) $(patsubst %.o,%.i,$(VER_O)) $(patsubst %.oo,%.ii,$(SRC_OO))
	rm -f $(patsubst %.o,%.s,$(SRC_O)) $(patsubst %.o,%.s,$(DRAM_O)) $(patsubst %.o,%.s,$(VER_O)) $(patsubst %.oo,%.s,$(SRC_OO))
	rm -f *.i
	rm -f *.s
	rm -f $(VER_C)
