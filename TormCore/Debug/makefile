-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
endif

-include ../makefile.defs

OPTIONAL_TOOL_DEPS := \
$(wildcard ../makefile.defs) \
$(wildcard ../makefile.init) \
$(wildcard ../makefile.targets) \


BUILD_ARTIFACT_NAME := tormapi
BUILD_ARTIFACT_EXTENSION := so
BUILD_ARTIFACT_PREFIX := lib
BUILD_ARTIFACT := $(BUILD_ARTIFACT_PREFIX)$(BUILD_ARTIFACT_NAME)$(if $(BUILD_ARTIFACT_EXTENSION),.$(BUILD_ARTIFACT_EXTENSION),)

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: main-build

# Main-build Target
main-build: libtormcore.so

# Tool invocations
libtormcore.so: $(OBJS) $(USER_OBJS) makefile $(OPTIONAL_TOOL_DEPS)
	@echo 'Building target: $@'
	@echo 'Invoking: GCC C++ Linker'
	g++ `pkg-config --libs gtk+-3.0` -L/usr/local/lib -shared -o "libtormcore.so" $(OBJS) $(USER_OBJS) $(LIBS) -lzmq -lgdk-3 -lpangocairo-1.0 -lpango-1.0 -lharfbuzz -lgdk_pixbuf-2.0 -lcairo-gobject -lcairo -lgobject-2.0 -lglib-2.0 -lgtk-3 -latk-1.0 -lgio-2.0
	@echo 'Finished building target: $@'
	@echo 'Copying $@ to /usr/local/lib'
	sudo cp $@ /usr/local/lib/.
	@echo ' '

# Other Targets
clean:
	-$(RM) libtormcore.so
	-@echo ' '

.PHONY: all clean dependents main-build

-include ../makefile.targets
