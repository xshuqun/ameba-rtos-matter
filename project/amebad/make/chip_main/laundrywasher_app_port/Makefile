include $(MAKE_INCLUDE_GEN) $(MATTER_MAIN_SRC)

.PHONY: all clean

#*****************************************************************************#
#                              VARIABLES                                      #
#*****************************************************************************#
OUTPUT_DIR = $(MATTER_EXAMPLEDIR)/laundrywasher/build/chip
CODEGEN_DIR = $(OUTPUT_DIR)/codegen

DIR += $(SRCDIR)
DIR += $(CODEGEN_DIR)/app
DIR += $(CODEGEN_DIR)/zap-generated
DIR += $(MATTER_EXAMPLEDIR)/laundrywasher

vpath %.cpp $(DIR) $(shell find $(DIR) -type d)
vpath %.c $(DIR) $(shell find $(DIR) -type d)

#*****************************************************************************#
#                              BUILD DEFINITIONS                              #
#*****************************************************************************#
include $(MATTER_INCLUDE_BUILD_OPT)

#*****************************************************************************#
#                              CFLAGS                                         #
#*****************************************************************************#
GLOBAL_CFLAGS += -DCHIP_PROJECT=1
GLOBAL_CFLAGS += -DSTD_PRINTF=1
GLOBAL_CFLAGS += -DCHIP_ADDRESS_RESOLVE_IMPL_INCLUDE_HEADER=\"lib/address_resolve/AddressResolve_DefaultImpl.h\"

# matter blemgr adapter options
ifeq ($(CONFIG_BLE_MATTER_ADAPTER),y)
GLOBAL_CFLAGS += -DCONFIG_MATTER_BLEMGR_ADAPTER=1
endif

#*****************************************************************************#
#                              INCLUDE FILE LIST                              #
#*****************************************************************************#
IFLAGS += -I$(CODEGEN_DIR)
IFLAGS += -I$(CODEGEN_DIR)/zap-generated
IFLAGS += -I$(MATTER_EXAMPLEDIR)/laundrywasher
IFLAGS += -I$(MATTER_EXAMPLEDIR)/laundrywasher/build/chip/gen/include

#*****************************************************************************#
#                              SOURCE FILE LIST                               #
#*****************************************************************************#
# porting layer src files
CPPSRC += $(MATTER_COREDIR)/matter_core.cpp
CPPSRC += $(MATTER_COREDIR)/matter_interaction.cpp
ifeq ($(CHIP_ENABLE_OTA_REQUESTOR), 1)
CPPSRC += $(MATTER_COREDIR)/matter_ota_initializer.cpp
endif

# laundrywasher-app src files
CPPSRC += $(MATTER_DRIVERDIR)/device/washer_driver.cpp
CPPSRC += $(MATTER_DRIVERDIR)/matter_drivers/laundry_washer_controls/ameba_laundry_washer_controls_delegate.cpp
CPPSRC += $(MATTER_DRIVERDIR)/matter_drivers/laundry_washer_mode/ameba_laundry_washer_mode_delegate.cpp
CPPSRC += $(MATTER_DRIVERDIR)/matter_drivers/laundry_washer_mode/ameba_laundry_washer_mode_instance.cpp
CPPSRC += $(MATTER_DRIVERDIR)/matter_drivers/operational_state/ameba_operational_state_delegate.cpp
CPPSRC += $(MATTER_DRIVERDIR)/matter_drivers/operational_state/ameba_operational_state_instance.cpp
CPPSRC += $(MATTER_EXAMPLEDIR)/laundrywasher/example_matter_laundrywasher.cpp
CPPSRC += $(MATTER_EXAMPLEDIR)/laundrywasher/matter_drivers.cpp

#*****************************************************************************#
#                              OBJECT FILE LIST                               #
#*****************************************************************************#
CPPOBJS = $(CPPSRC:.cpp=.o)
COBJS = $(notdir $(CSRC:.c=.o))
OBJS = $(CPPOBJS) $(COBJS)
STATIC_LIB = lib_main.a

#*****************************************************************************#
#                              INCLUDE DEPENDENCY                             #
#*****************************************************************************#
-include $(OBJS:.o=.d)

#*****************************************************************************#
#                              RULES TO GENERATE TARGETS                      #
#*****************************************************************************#
all: CORE_TARGETS

#*****************************************************************************#
#                              GENERATE OBJECT FILE                           #
#*****************************************************************************#
CORE_TARGETS: $(CPPOBJS) $(COBJS) $(STATIC_LIB)

$(CPPOBJS): %.o: %.cpp
	$(CC) -ffunction-sections $(CPPFLAGS) $(MODULE_IFLAGS) -c $< -o $@
	@foldername=$$(basename $$(dirname $<)); \
	mkdir -p $${foldername}; \
	cp $@ $${foldername}/$(notdir $@)

$(STATIC_LIB):$(OBJS)
	$(AR) rvs $@ *.o */*.o
	$(MOVE) -f $@ $(ROOTDIR)/lib/application

#*****************************************************************************#
#                              CLEAN GENERATED FILES                          #
#*****************************************************************************#
clean:
	find $(MATTER_BUILDDIR)/make/chip_main/laundrywasher_app_port/ -mindepth 1 -type d -exec rm -r {} +
	rm -f $(patsubst %.cpp,%.d,$(CPPSRC:.cpp=.d))
	rm -f $(patsubst %.cpp,%.su,$(CPPSRC:.cpp=.su))
	rm -f $(patsubst %.cpp,%.o,$(CPPSRC:.cpp=.o))
	rm -f *.d *.su *.o
	rm -f $(MATTER_EXAMPLEDIR)/laundrywasher/laundrywasher-app.matter

-include $(DEPS)
