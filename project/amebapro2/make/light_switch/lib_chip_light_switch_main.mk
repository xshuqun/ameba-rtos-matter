SHELL = /bin/bash

OS := $(shell uname)

# Directory
# -------------------------------------------------------------------

SDKROOTDIR         := $(shell pwd)/../../..
CHIPDIR             = $(SDKROOTDIR)/third_party/connectedhomeip
OUTPUT_DIR          = $(CHIPDIR)/examples/light-switch-app/ameba/build/chip
CODEGENDIR          = $(OUTPUT_DIR)/codegen

MATTER_DIR          = $(SDKROOTDIR)/component/application/matter
MATTER_BUILDDIR     = $(MATTER_DIR)/project/amebapro2
MATTER_INCLUDE      = $(MATTER_BUILDDIR)/Makefile.include.matter
MATTER_INCLUDE_HDR  = $(MATTER_BUILDDIR)/Makefile.include.hdr.list

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

# Initialize target name and target object files
# -------------------------------------------------------------------

all: lib_main

TARGET=lib_main
OBJ_DIR=$(TARGET)/Debug/obj
BIN_DIR=$(TARGET)/Debug/bin
INFO_DIR=$(TARGET)/Debug/info

# Build Definition
# -------------------------------------------------------------------

CHIP_ENABLE_AMEBA_DLOG = $(shell grep "\#define CONFIG_ENABLE_AMEBA_DLOG " $(MATTER_DIR)/common/include/platform_opts_matter.h | tr -s '[:space:]' | cut -d' ' -f3)
CHIP_ENABLE_OTA_REQUESTOR = $(shell grep 'chip_enable_ota_requestor' $(OUTPUT_DIR)/args.gn | cut -d' ' -f3)
CHIP_ENABLE_SHELL = $(shell grep 'chip_build_libshell' $(OUTPUT_DIR)/args.gn | cut -d' ' -f3)

# Include folder list
# -------------------------------------------------------------------

include $(MATTER_INCLUDE_HDR)

# Matter (CHIP) Include folder list
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
INCLUDES += -I$(CHIPDIR)/examples/light-switch-app/light-switch-common
INCLUDES += -I$(CHIPDIR)/examples/light-switch-app/light-switch-common/include
INCLUDES += -I$(CHIPDIR)/examples/light-switch-app/ameba/main/include
INCLUDES += -I$(CHIPDIR)/examples/light-switch-app/ameba/build/chip/gen/include
INCLUDES += -I$(CODEGENDIR)

# Source file list
# -------------------------------------------------------------------

SRC_C =
SRC_C += $(CHIPDIR)/examples/platform/ameba/route_hook/ameba_route_hook.c
SRC_C += $(CHIPDIR)/examples/platform/ameba/route_hook/ameba_route_table.c
SRC_C += $(MATTER_DIR)/examples/matter_example_entry.c
SRC_C += $(MATTER_DIR)/examples/chiptest/example_matter.c
SRC_C += $(MATTER_DIR)/common/mbedtls/mbedtls_memory.c

SRC_CPP = 
SRC_CPP += $(CHIPDIR)/examples/providers/DeviceInfoProviderImpl.cpp

SRC_CPP += $(CHIPDIR)/src/app/icd/server/ICDMonitoringTable.cpp
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
SRC_CPP += $(CHIPDIR)/src/app/util/ember-global-attribute-access-interface.cpp
SRC_CPP += $(CHIPDIR)/src/app/util/ember-io-storage.cpp
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

# light-switch-app ameba source files
SRC_CPP += $(CHIPDIR)/examples/light-switch-app/ameba/main/chipinterface.cpp
SRC_CPP += $(CHIPDIR)/examples/light-switch-app/ameba/main/BindingHandler.cpp
SRC_CPP += $(CHIPDIR)/examples/light-switch-app/ameba/main/DeviceCallbacks.cpp
SRC_CPP += $(CHIPDIR)/examples/light-switch-app/ameba/main/CHIPDeviceManager.cpp
SRC_CPP += $(CHIPDIR)/examples/light-switch-app/ameba/main/Globals.cpp
SRC_CPP += $(CHIPDIR)/examples/light-switch-app/ameba/main/LEDWidget.cpp

ifeq ($(CHIP_ENABLE_OTA_REQUESTOR), true)
SRC_CPP += $(CHIPDIR)/examples/platform/ameba/ota/OTAInitializer.cpp
endif
SRC_CPP += $(CHIPDIR)/examples/platform/ameba/shell/launch_shell.cpp

SRC_CPP += $(MATTER_DIR)/api/matter_api.cpp
SRC_CPP += $(MATTER_DIR)/core/matter_device_utils.cpp

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
CFLAGS += -fdiagnostics-color=always
CFLAGS += -g -gdwarf-3 -MMD -nostartfiles -nodefaultlibs -nostdlib
CFLAGS += -D__thumb2__ -DCONFIG_PLATFORM_8735B -DARM_MATH_ARMV8MML -D__FPU_PRESENT -D__ARM_ARCH_7M__=0 
CFLAGS += -D__ARM_ARCH_7EM__=0 -D__ARM_ARCH_8M_MAIN__=1 -D__ARM_ARCH_8M_BASE__=0 
CFLAGS += -D__ARM_FEATURE_FP16_SCALAR_ARITHMETIC=1 -D__DSP_PRESENT=1 -D__ARMVFP__

# CHIP options
# -------------------------------------------------------------------

# General Flags
include $(MATTER_INCLUDE)

CFLAGS += -DCHIP_PROJECT=1

# Matter Shell Flags
ifeq ($(CHIP_ENABLE_SHELL), true)
CFLAGS += -DCONFIG_ENABLE_CHIP_SHELL=1
endif

# Others
CFLAGS += -DCHIP_ADDRESS_RESOLVE_IMPL_INCLUDE_HEADER=\"lib/address_resolve/AddressResolve_DefaultImpl.h\"
CFLAGS += -DUSE_ZAP_CONFIG

CPPFLAGS += $(CFLAGS)

# Compile
# -------------------------------------------------------------------

.PHONY: lib_main
lib_main: prerequirement $(SRC_O) $(DRAM_O) $(SRC_OO)
	$(AR) crv $(BIN_DIR)/$(TARGET).a $(OBJ_CPP_LIST) $(OBJ_LIST) $(VER_O)
	cp $(BIN_DIR)/$(TARGET).a $(SDKROOTDIR)/project/realtek_amebapro2_v0_example/GCC-RELEASE/application/output/$(TARGET).a

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
	@if [ ! -d $(ARM_GCC_TOOLCHAIN) ]; then \
		echo ===========================================================; \
		echo Toolchain not found, \"make toolchain\" first!; \
		echo ===========================================================; \
		exit -1; \
	fi
	@echo ===========================================================
	@echo Build $(TARGET)
	@echo ===========================================================
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)
	mkdir -p $(INFO_DIR)

$(SRC_OO): %_$(TARGET).oo : %.cpp | prerequirement
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -o $@
	$(CC) $(CPPFLAGS) $(INCLUDES) -c $< -MM -MT $@ -MF $(OBJ_DIR)/$(notdir $(patsubst %.oo,%.d,$@))
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