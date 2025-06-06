all: all_clusters

OS := $(shell uname)
LBITS := $(shell getconf LONG_BIT)

SDKROOTDIR         := $(shell pwd)/../../..
MATTER_DIR          = $(SDKROOTDIR)/component/common/application/matter
MATTER_BUILDDIR     = $(MATTER_DIR)/project/amebaz2
MATTER_INCLUDE      = $(MATTER_BUILDDIR)/Makefile.include.matter

include $(MATTER_INCLUDE)

#*****************************************************************************#
#                         Toolchain Extraction                                #
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
#                            MATTER ZAP files                                 #
#*****************************************************************************#

ALL_CLUSTERS_FILE	= $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen/cluster-file.txt
ALL_CLUSTERS_ZAP	= $(CHIPDIR)/examples/all-clusters-app/all-clusters-common/all-clusters-app.zap
AIR_PURIFIER_FILE	= $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen/cluster-file.txt
AIR_PURIFIER_ZAP	= $(CHIPDIR)/examples/air-purifier-app/air-purifier-common/air-purifier-app.zap
CHEF_FILE			= $(CHIPDIR)/examples/chef/ameba/build/chip/codegen/cluster-file.txt
CHEF_ZAP			= $(CHIPDIR)/examples/chef/devices/$(SAMPLE_NAME).zap
LIGHTING_FILE		= $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/cluster-file.txt
LIGHTING_ZAP		= $(CHIPDIR)/examples/lighting-app/lighting-common/lighting-app.zap
LIGHT_SWITCH_FILE	= $(CHIPDIR)/examples/light-switch-app/ameba/build/chip/codegen/cluster-file.txt
LIGHT_SWITCH_ZAP	= $(CHIPDIR)/examples/light-switch-app/light-switch-common/light-switch-app.zap
OTAR_FILE			= $(CHIPDIR)/examples/ota-requestor-app/ameba/build/chip/codegen/cluster-file.txt
OTAR_ZAP			= $(CHIPDIR)/examples/ota-requestor-app/ota-requestor-common/ota-requestor-app.zap
THERMOSTAT_FILE		= $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen/cluster-file.txt
THERMOSTAT_ZAP		= $(CHIPDIR)/examples/thermostat/thermostat-common/thermostat.zap

AIRCON_FILE			= $(MATTER_EXAMPLEDIR)/aircon/build/chip/codegen/cluster-file.txt
AIRCON_ZAP			= $(MATTER_EXAMPLEDIR)/aircon/aircon-app.zap
BRIDGE_DM_FILE		= $(MATTER_EXAMPLEDIR)/bridge_dm/build/chip/codegen/cluster-file.txt
BRIDGE_DM_ZAP		= $(MATTER_EXAMPLEDIR)/bridge_dm/bridge-app.zap
DISHWASHER_FILE		= $(MATTER_EXAMPLEDIR)/dishwasher/build/chip/codegen/cluster-file.txt
DISHWASHER_ZAP		= $(MATTER_EXAMPLEDIR)/dishwasher/dishwasher-app.zap
FAN_FILE			= $(MATTER_EXAMPLEDIR)/fan/build/chip/codegen/cluster-file.txt
FAN_ZAP				= $(MATTER_EXAMPLEDIR)/fan/fan-app.zap
GENERIC_SWITCH_FILE	= $(MATTER_EXAMPLEDIR)/generic_switch/build/chip/codegen/cluster-file.txt
GENERIC_SWITCH_ZAP	= $(MATTER_EXAMPLEDIR)/generic_switch/generic-switch-app.zap
LAUNDRYWASHER_FILE	= $(MATTER_EXAMPLEDIR)/laundrywasher/build/chip/codegen/cluster-file.txt
LAUNDRYWASHER_ZAP	= $(MATTER_EXAMPLEDIR)/laundrywasher/laundrywasher-app.zap
MICROWAVEOVEN_FILE  = $(MATTER_EXAMPLEDIR)/microwaveoven/build/chip/codegen/cluster-file.txt
MICROWAVEOVEN_ZAP   = $(MATTER_EXAMPLEDIR)/microwaveoven/microwaveoven-app.zap
REFRIGERATOR_FILE	= $(MATTER_EXAMPLEDIR)/refrigerator/build/chip/codegen/cluster-file.txt
REFRIGERATOR_ZAP	= $(MATTER_EXAMPLEDIR)/refrigerator/refrigerator-app.zap
TEMP_SENSOR_FILE	= $(MATTER_EXAMPLEDIR)/temperature_sensor/build/chip/codegen/cluster-file.txt
TEMP_SENSOR_ZAP		= $(MATTER_EXAMPLEDIR)/temperature_sensor/temp-sensor-app.zap

#*****************************************************************************#
#                      RULES TO MAKE MATTER DIRS                              #
#*****************************************************************************#

$(ALL_CLUSTERS_FILE): $(ALL_CLUSTERS_ZAP)
	@cp $(MATTER_EXAMPLEDIR)/chiptest/all-clusters-app.zap $(ALL_CLUSTERS_ZAP)
	@mkdir -p $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/all-clusters-app/ameba/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/all-clusters-app/ameba/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/all-clusters-app/all-clusters-common/all-clusters-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(CHIPDIR)/examples/all-clusters-app/ameba/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(AIR_PURIFIER_FILE): $(AIR_PURIFIER_ZAP)
	@mkdir -p $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/air-purifier-app/ameba/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/air-purifier-app/ameba/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/air-purifier-app/air-purifier-common/air-purifier-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(CHIPDIR)/examples/air-purifier-app/ameba/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(CHEF_FILE): $(CHEF_ZAP)
	@mkdir -p $(CHIPDIR)/examples/chef-app/ameba/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/chef-app/ameba/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/chef-app/ameba/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/chef-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/chef-app/chef-common/chef-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(CHIPDIR)/examples/chef-app/ameba/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(LIGHTING_FILE): $(LIGHTING_ZAP)
	@mkdir -p $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/lighting-app/ameba/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/lighting-app/ameba/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/lighting-app/lighting-common/lighting-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(LIGHT_SWITCH_FILE): $(LIGHT_SWITCH_ZAP)
	@mkdir -p $(CHIPDIR)/examples/light-switch-app/ameba/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/light-switch-app/ameba/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/light-switch-app/ameba/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/light-switch-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/light-switch-app/light-switch-common/light-switch-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(CHIPDIR)/examples/light-switch-app/ameba/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(OTAR_FILE): $(OTAR_ZAP)
	@mkdir -p $(CHIPDIR)/examples/ota-requestor-app/ameba/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/ota-requestor-app/ameba/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/ota-requestor-app/ameba/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/ota-requestor-app/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/ota-requestor-app/ota-requestor-common/ota-requestor-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(CHIPDIR)/examples/ota-requestor-app/ameba/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(AIRCON_FILE): $(AIRCON_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/aircon/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/aircon/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/aircon/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/aircon/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/aircon/aircon-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(BRIDGE_DM_FILE): $(BRIDGE_DM_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/bridge_dm/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/bridge_dm/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/bridge_dm/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/bridge_dm/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/bridge_dm/bridge-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(MATTER_EXAMPLEDIR)/bridge_dm/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)
	@cp $(MATTER_EXAMPLEDIR)/bridge_dm/endpoint_config.h $(MATTER_EXAMPLEDIR)/bridge_dm/build/chip/codegen/zap-generated
	@cp $(MATTER_EXAMPLEDIR)/bridge_dm/gen_config.h $(MATTER_EXAMPLEDIR)/bridge_dm/build/chip/codegen/zap-generated

$(DISHWASHER_FILE): $(DISHWASHER_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/dishwasher/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/dishwasher/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/dishwasher/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/dishwasher/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/dishwasher/dishwasher-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(FAN_FILE): $(FAN_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/fan/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/fan/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/fan/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/fan/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/fan/fan-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(GENERIC_SWITCH_FILE): $(GENERIC_SWITCH_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/generic_switch/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/generic_switch/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/generic_switch/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/generic_switch/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/generic_switch/generic-switch-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(LAUNDRYWASHER_FILE): $(LAUNDRYWASHER_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/laundrywasher/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/laundrywasher/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/laundrywasher/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/laundrywasher/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/laundrywasher/laundrywasher-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(MICROWAVEOVEN_FILE): $(MICROWAVEOVEN_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/microwaveoven/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/microwaveoven/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/microwaveoven/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/microwaveoven/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/microwaveoven/microwaveoven-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(REFRIGERATOR_FILE): $(REFRIGERATOR_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/refrigerator/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/refrigerator/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/refrigerator/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/refrigerator/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/refrigerator/refrigerator-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(TEMP_SENSOR_FILE): $(TEMP_SENSOR_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/temperature_sensor/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/temperature_sensor/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/temperature_sensor/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/temperature_sensor/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/temperature_sensor/temp-sensor-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

$(THERMOSTAT_FILE): $(THERMOSTAT_ZAP)
	@mkdir -p $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json --output-dir examples/thermostat/ameba/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json --output-dir examples/thermostat/ameba/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(CHIPDIR)/examples/thermostat/thermostat-common/thermostat.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $(CHIPDIR)/examples/thermostat/ameba/build/chip/codegen/cluster-file.txt
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

copy_gen_files_light_dm:
	@cp $(MATTER_EXAMPLEDIR)/light_dm/endpoint_config.h $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/zap-generated
	@cp $(MATTER_EXAMPLEDIR)/light_dm/gen_config.h $(CHIPDIR)/examples/lighting-app/ameba/build/chip/codegen/zap-generated

#*****************************************************************************#
#                         MATTER MAKE DEFINES                                 #
#*****************************************************************************#

.PHONY: all_clusters
all_clusters: toolchain_matter $(ALL_CLUSTERS_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/all_clusters/lib_chip.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/all_clusters/lib_chip_main.mk all

.PHONY: aircon_port
aircon_port: toolchain_matter $(AIRCON_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/aircon/lib_chip_aircon_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/aircon/lib_chip_aircon_main.mk all

.PHONY: air_purifier
air_purifier: toolchain_matter $(AIR_PURIFIER_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/air_purifier/lib_chip_air_purifier_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/air_purifier/lib_chip_air_purifier_main.mk all

.PHONY: bridge_dm
bridge_dm: toolchain_matter $(BRIDGE_DM_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/bridge_dm/lib_chip_bridge_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/bridge_dm/lib_chip_bridge_main.mk all

.PHONY: chef
chef: toolchain_matter $(CHEF_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/chef/lib_chip_chef_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/chef/lib_chip_chef_main.mk all

.PHONY: dishwasher_port
dishwasher_port: toolchain_matter $(DISHWASHER_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/dishwasher/lib_chip_dishwasher_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/dishwasher/lib_chip_dishwasher_main.mk all

.PHONY: fan_port
fan_port: toolchain_matter $(FAN_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/fan/lib_chip_fan_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/fan/lib_chip_fan_main.mk all

.PHONY: generic_switch
generic_switch_port: toolchain_matter $(GENERIC_SWITCH_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/generic_switch/lib_chip_generic_switch_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/generic_switch/lib_chip_generic_switch_main.mk all

.PHONY: laundrywasher_port
laundrywasher_port: toolchain_matter $(LAUNDRYWASHER_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/laundrywasher/lib_chip_laundrywasher_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/laundrywasher/lib_chip_laundrywasher_main.mk all

.PHONY: light
light: toolchain_matter $(LIGHTING_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/light/lib_chip_light_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/light/lib_chip_light_main.mk all

.PHONY: light_dm
light_dm: toolchain_matter $(LIGHTING_FILE) copy_gen_files_light_dm
	$(MAKE) -f $(MATTER_MAKEDIR)/light_dm/lib_chip_light_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/light_dm/lib_chip_light_main.mk all

.PHONY: light_port
light_port: toolchain_matter $(LIGHTING_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/light_port/lib_chip_light_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/light_port/lib_chip_light_main.mk all

.PHONY: light_switch
light_switch: toolchain_matter $(LIGHT_SWITCH_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/light_switch/lib_chip_light_switch_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/light_switch/lib_chip_light_switch_main.mk all

.PHONY: microwaveoven_port
microwaveoven_port: toolchain_matter $(MICROWAVEOVEN_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/microwaveoven/lib_chip_microwaveoven_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/microwaveoven/lib_chip_microwaveoven_main.mk all

.PHONY: otar
otar: toolchain_matter $(OTAR_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/otar/lib_chip_otar_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/otar/lib_chip_otar_main.mk all

.PHONY: refrigerator_port
refrigerator_port: toolchain_matter $(REFRIGERATOR_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/refrigerator/lib_chip_refrigerator_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/refrigerator/lib_chip_refrigerator_main.mk all

.PHONY: temp_sensor_port
temp_sensor_port: toolchain_matter $(TEMP_SENSOR_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/temperature_sensor/lib_chip_temp_sensor_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/temperature_sensor/lib_chip_temp_sensor_main.mk all

.PHONY: thermostat_port
thermostat_port: toolchain_matter $(THERMOSTAT_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/thermostat/lib_chip_thermostat_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/thermostat/lib_chip_thermostat_main.mk all

.PHONY: clean_matter_libs
clean_matter_libs:
	@$(MAKE) -f $(MATTER_MAKEDIR)/all_clusters/lib_chip_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/aircon/lib_chip_aircon_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/air_purifier/lib_chip_air_purifier_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/bridge_dm/lib_chip_bridge_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/chef/lib_chip_chef_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/dishwasher/lib_chip_dishwasher_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/fan/lib_chip_fan_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/generic_switch/lib_chip_generic_switch_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/laundrywasher/lib_chip_laundrywasher_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light/lib_chip_light_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_dm/lib_chip_light_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_port/lib_chip_light_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_switch/lib_chip_light_switch_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/microwaveoven/lib_chip_microwaveoven_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/otar/lib_chip_otar_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/refrigerator/lib_chip_refrigerator_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/temperature_sensor/lib_chip_temp_sensor_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/thermostat/lib_chip_thermostat_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/all_clusters/lib_chip.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/aircon/lib_chip_aircon_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/air_purifier/lib_chip_air_purifier_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/bridge_dm/lib_chip_bridge_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/chef/lib_chip_chef_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/dishwasher/lib_chip_dishwasher_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/fan/lib_chip_fan_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/generic_switch/lib_chip_generic_switch_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/laundrywasher/lib_chip_laundrywasher_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light/lib_chip_light_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_dm/lib_chip_light_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_port/lib_chip_light_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/light_switch/lib_chip_light_switch_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/microwaveoven/lib_chip_microwaveoven_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/otar/lib_chip_otar_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/refrigerator/lib_chip_refrigerator_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/thermostat/lib_chip_thermostat_core.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/temperature_sensor/lib_chip_temp_sensor_core.mk clean
	rm -rf $(MATTER_BUILDDIR)/lib_main*
