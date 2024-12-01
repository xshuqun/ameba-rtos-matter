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
AS = $(CROSS_COMPILE)as
NM = $(CROSS_COMPILE)nm
LD = $(CROSS_COMPILE)gcc
GDB = $(CROSS_COMPILE)gdb
OBJCOPY = $(CROSS_COMPILE)objcopy
OBJDUMP = $(CROSS_COMPILE)objdump

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
INCLUDES += -I$(CHIPDIR)/config/ameba
INCLUDES += -I$(CHIPDIR)/src/include/platform/Ameba
INCLUDES += -I$(CHIPDIR)/src/include
INCLUDES += -I$(CHIPDIR)/src/lib
INCLUDES += -I$(CHIPDIR)/src
INCLUDES += -I$(CHIPDIR)/src/system
INCLUDES += -I$(CHIPDIR)/src/app
INCLUDES += -I$(CHIPDIR)/third_party/nlassert/repo/include
INCLUDES += -I$(CHIPDIR)/third_party/nlio/repo/include
INCLUDES += -I$(CHIPDIR)/third_party/nlunit-test/repo/src

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

# for matter blemgr adapter
#CFLAGS += -DCONFIG_MATTER_BLEMGR_ADAPTER=1

# CHIP options
# -------------------------------------------------------------------
CFLAGS += -DCHIP_PROJECT=1
CFLAGS += -DCONFIG_MATTER=1
CFLAGS += -DCONFIG_MATTER_BLEMGR_ADAPTER=1
CFLAGS += -DCHIP_DEVICE_LAYER_TARGET=Ameba
CFLAGS += -DMBEDTLS_CONFIG_FILE=\"mbedtls_config.h\"

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

CFLAGS += -DCHIP_SHELL_MAX_TOKENS=11
CFLAGS += -DCONFIG_ENABLE_AMEBA_FACTORY_DATA=0

CXXFLAGS += -DFD_SETSIZE=10

CXXFLAGS += -Wno-sign-compare
CXXFLAGS += -Wno-unused-function
CXXFLAGS += -Wno-unused-but-set-variable
CXXFLAGS += -Wno-unused-label
CXXFLAGS += -Wno-unused-variable
CXXFLAGS += -Wno-deprecated-declarations
CXXFLAGS += -Wno-unused-parameter
CXXFLAGS += -Wno-format

CXXFLAGS += -std=gnu++17
CXXFLAGS += -fno-rtti
CXXFLAGS += -Wno-format-nonliteral
CXXFLAGS += -Wno-format-security

CHIP_CFLAGS = $(CFLAGS)
CHIP_CFLAGS += $(INCLUDES)

CHIP_CXXFLAGS += $(CFLAGS)
CHIP_CXXFLAGS += $(CXXFLAGS)
CHIP_CXXFLAGS += $(INCLUDES)

#*****************************************************************************#
#                        RULES TO GENERATE TARGETS                            #
#*****************************************************************************#

# Define the Rules to build the core targets
all: GENERATE_NINJA

GENERATE_NINJA:
	echo "INSTALL CHIP..." && \
	echo $(BASEDIR) && \
	if [ ! d "$(OUTPUT_DIR")" ]; then mkdir -p "$(OUTPUT_DIR)"; fi && \
	echo                                   > $(OUTPUT_DIR)/args.gn && \
	echo "import(\"//args.gni\")"          >> $(OUTPUT_DIR)/args.gn && \
	echo target_cflags_c  = [$(foreach word,$(CHIP_CFLAGS),\"$(word)\",)] | sed -e 's/=\"/=\\"/g;s/\"\"/\\"\"/g;'  >> $(OUTPUT_DIR)/args.gn && \
	echo target_cflags_cc = [$(foreach word,$(CHIP_CXXFLAGS),\"$(word)\",)] | sed -e 's/=\"/=\\"/g;s/\"\"/\\"\"/g;'   >> $(OUTPUT_DIR)/args.gn && \
	echo ameba_ar = \"arm-none-eabi-ar\"    >> $(OUTPUT_DIR)/args.gn && \
	echo ameba_cc = \"arm-none-eabi-gcc\"   >> $(OUTPUT_DIR)/args.gn && \
	echo ameba_cxx = \"arm-none-eabi-c++\"  >> $(OUTPUT_DIR)/args.gn && \
	echo ameba_cpu = \"ameba\"               >> $(OUTPUT_DIR)/args.gn && \
	echo chip_enable_ota_requestor = "true" >> $(OUTPUT_DIR)/args.gn && \
	echo chip_build_libshell = "true" >> $(OUTPUT_DIR)/args.gn && \
	echo chip_inet_config_enable_ipv4 = "false" >> $(OUTPUT_DIR)/args.gn && \
	echo chip_support_enable_storage_api_audit = "false" >> $(OUTPUT_DIR)/args.gn && \
	echo chip_use_transitional_commissionable_data_provider = "true" >> $(OUTPUT_DIR)/args.gn && \
	echo chip_logging = "true" >> $(OUTPUT_DIR)/args.gn && \
	echo chip_error_logging  = "true" >> $(OUTPUT_DIR)/args.gn && \
	echo chip_progress_logging  = "true" >> $(OUTPUT_DIR)/args.gn && \
	echo chip_detail_logging = "false" >> $(OUTPUT_DIR)/args.gn && \
	sed -i 's/chip_build_tests\ =\ true/chip_build_tests\ =\ false/g' $(CHIPDIR)/config/ameba/args.gni && \
	mkdir -p $(CHIPDIR)/config/ameba/components/chip && \
	cd $(CHIPDIR)/config/ameba/components/chip && gn gen --check --fail-on-unused-args $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip && \
	cd $(CHIPDIR)/config/ameba/components/chip ; ninja -C $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip :ameba && \
	cp -f $(OUTPUT_DIR)/lib/* $(SDKROOTDIR)/project/realtek_amebapro2_v0_example/GCC-RELEASE/application/output

#*****************************************************************************#
#              CLEAN GENERATED FILES                                          #
#*****************************************************************************#
.PHONY: clean
clean:
	echo "RM $(OUTPUT_DIR)"
	rm -rf $(OUTPUT_DIR)

