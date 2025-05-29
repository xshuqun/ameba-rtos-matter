include $(MATTER_INCLUDE)

#*****************************************************************************#
#                        MATTER DEVICE TYPE DECLARATION                       #
#*****************************************************************************#

TARGET_NAME		= generic_switch
APP_NAME		= generic-switch

#*****************************************************************************#
#                            MATTER ZAP files                                 #
#*****************************************************************************#

CLUSTERS_FILE	= $(MATTER_EXAMPLEDIR)/$(TARGET_NAME)/build/chip/codegen/cluster-file.txt
CLUSTERS_ZAP	= $(MATTER_EXAMPLEDIR)/$(TARGET_NAME)/$(APP_NAME)-app.zap

#*****************************************************************************#
#                     ZAP GENERATION FOR MATTER EXAMPLES                      #
#*****************************************************************************#

$(CLUSTERS_FILE): $(CLUSTERS_ZAP)
	@mkdir -p $(MATTER_EXAMPLEDIR)/$(TARGET_NAME)/build/chip/codegen/zap-generated
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/matter-idl-server.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/$(TARGET_NAME)/build/chip/codegen/zap-generated  $^
	@python3 $(CHIPDIR)/scripts/tools/zap/generate.py --no-prettify-output --templates src/app/zap-templates/app-templates.json -z $(CHIPDIR)/src/app/zap-templates/zcl/zcl.json --output-dir $(MATTER_EXAMPLEDIR)/$(TARGET_NAME)/build/chip/codegen/zap-generated $^
	@python3 $(CHIPDIR)/scripts/codegen.py --generator cpp-app --output-dir $(MATTER_EXAMPLEDIR)/$(TARGET_NAME)/build/chip/codegen --expected-outputs $(MATTER_TOOLDIR)/codegen_helpers/expected.outputs $(MATTER_EXAMPLEDIR)/$(TARGET_NAME)/$(APP_NAME)-app.matter
	@python3 $(CHIPDIR)/src/app/zap_cluster_list.py --zap_file $^ > $@
	@python3 $(MATTER_TOOLDIR)/codegen_helpers/parse_clusters.py --cluster_file $@ --chip_path $(CHIPDIR)

#*****************************************************************************#
#                         MATTER MAKE DEFINES                                 #
#*****************************************************************************#

.PHONY: all
all: $(CLUSTERS_FILE)
	$(MAKE) -f $(MATTER_MAKEDIR)/$(TARGET_NAME)/lib_chip_$(TARGET_NAME)_core.mk all
	$(MAKE) -f $(MATTER_MAKEDIR)/$(TARGET_NAME)/lib_chip_$(TARGET_NAME)_main.mk all

.PHONY: clean
clean:
	@$(MAKE) -f $(MATTER_MAKEDIR)/$(TARGET_NAME)/lib_chip_$(TARGET_NAME)_main.mk clean
	@$(MAKE) -f $(MATTER_MAKEDIR)/$(TARGET_NAME)/lib_chip_$(TARGET_NAME)_core.mk clean
