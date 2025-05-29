all: all_clusters

OS := $(shell uname)
LBITS := $(shell getconf LONG_BIT)

SDKROOTDIR         := $(shell pwd)/../../..
MATTER_DIR          = $(SDKROOTDIR)/component/common/application/matter
MATTER_BUILDDIR     = $(MATTER_DIR)/project/amebaz2plus
MATTER_INCLUDE      = $(MATTER_BUILDDIR)/Makefile.include.matter

include $(MATTER_INCLUDE)

export SDKROOTDIR MATTER_INCLUDE

#*****************************************************************************#
#                            TOOLCHAIN EXTRACTION                             #
#*****************************************************************************#

.PHONY: toolchain_matter
toolchain_matter:
	@echo Toolchain unzipping...

ifeq ($(findstring Linux, $(OS)), Linux)
ifneq ("$(LBITS)", "64")
	@echo ONLY 64-BIT LINUX IS SUPPORTED!
	@exit -1
endif
	if [ ! -f $(MATTER_TOOLCHAINDIR)/$(TOOLCHAIN_FILENAME) ] ; then cat $(MATTER_TOOLCHAINDIR)/$(TOOLCHAIN_FILENAME)* > $(MATTER_TOOLCHAINDIR)/$(TOOLCHAIN_FILENAME); fi;\
	if [ ! -d $(SDKROOTDIR)/tools/arm-none-eabi-gcc/asdk-$(TOOLCHAIN_VER) ] ; then mkdir $(SDKROOTDIR)/tools/arm-none-eabi-gcc/asdk-$(TOOLCHAIN_VER); fi;\
	if [ ! -d $(SDKROOTDIR)/tools/arm-none-eabi-gcc/asdk-$(TOOLCHAIN_VER)/$(ASDK_PLATFORM) ] ; then tar -jxf $(MATTER_TOOLCHAINDIR)/$(TOOLCHAIN_FILENAME) -C $(SDKROOTDIR)/tools/arm-none-eabi-gcc/; fi
endif
	@echo Toolchain unzip done!

#*****************************************************************************#
#                         BUILD RULES FOR MATTER EXAMPLES                     #
#*****************************************************************************#

.PHONY: all_clusters
all_clusters: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/all_clusters all

.PHONY: aircon_port
aircon_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/aircon all

.PHONY: air_purifier
air_purifier: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/air_purifier all

.PHONY: bridge_dm
bridge_dm: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/bridge_dm all

.PHONY: chef
chef: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/chef all

.PHONY: dishwasher_port
dishwasher_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/dishwasher all

.PHONY: fan_port
fan_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/fan all

.PHONY: generic_switch
generic_switch_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/generic_switch all

.PHONY: laundrywasher_port
laundrywasher_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/laundrywasher all

.PHONY: light
light: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/light all

.PHONY: light_dm
light_dm: toolchain_matter $(LIGHTING_FILE) copy_gen_files_light_dm
	$(MAKE) -C $(MATTER_MAKEDIR)/light_dm all

.PHONY: light_port
light_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/light_port all

.PHONY: light_switch
light_switch: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/light_switch all

.PHONY: microwaveoven_port
microwaveoven_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/microwave_oven all

.PHONY: otar
otar: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/otar all

.PHONY: refrigerator_port
refrigerator_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/refrigerator all

.PHONY: temp_sensor_port
temp_sensor_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/temperature_sensor all

.PHONY: thermostat_port
thermostat_port: toolchain_matter
	$(MAKE) -C $(MATTER_MAKEDIR)/thermostat all

#*****************************************************************************#
#                         CLEANUP RULES                                       #
#*****************************************************************************#

.PHONY: clean_matter_libs .clean_matter_libs_main .clean_matter_libs_core

clean_matter_libs: .clean_matter_libs_main .clean_matter_libs_core

.clean_matter_libs_main:
	@$(MAKE) -f $(MATTER_MAKEDIR)/all_clusters/lib_chip_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/aircon/lib_chip_aircon_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/air_purifier/lib_chip_air_purifier_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/bridge_dm/lib_chip_bridge_dm_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/chef/lib_chip_chef_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/dishwasher/lib_chip_dishwasher_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/fan/lib_chip_fan_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/generic_switch/lib_chip_generic_switch_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/laundrywasher/lib_chip_laundrywasher_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light/lib_chip_light_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_dm/lib_chip_light_dm_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_port/lib_chip_light_port_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_switch/lib_chip_light_switch_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/microwave_oven/lib_chip_microwave_oven_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/otar/lib_chip_otar_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/refrigerator/lib_chip_refrigerator_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/temperature_sensor/lib_chip_temperature_sensor_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/thermostat/lib_chip_thermostat_main.mk clean

.clean_matter_libs_core:
	@$(MAKE) -f $(MATTER_MAKEDIR)/all_clusters/lib_chip.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/aircon/lib_chip_aircon_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/air_purifier/lib_chip_air_purifier_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/bridge_dm/lib_chip_bridge_dm_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/chef/lib_chip_chef_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/dishwasher/lib_chip_dishwasher_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/fan/lib_chip_fan_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/generic_switch/lib_chip_generic_switch_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/laundrywasher/lib_chip_laundrywasher_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light/lib_chip_light_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_dm/lib_chip_light_dm_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_port/lib_chip_light_port_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_switch/lib_chip_light_switch_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/microwave_oven/lib_chip_microwave_oven_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/otar/lib_chip_otar_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/refrigerator/lib_chip_refrigerator_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/thermostat/lib_chip_thermostat_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/temperature_sensor/lib_chip_temperature_sensor_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/thermostat/lib_chip_thermostat_core.mk clean
	rm -rf $(MATTER_BUILDDIR)/lib_main*
