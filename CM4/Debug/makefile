################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/MemMang/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS/subdir.mk
-include Middlewares/Third_Party/FreeRTOS/Source/subdir.mk
-include Drivers/STM32H7xx_HAL_Driver/Src/subdir.mk
-include Drivers/BSP/Components/lan8742/subdir.mk
-include Core/Startup/subdir.mk
-include Core/Src/subdir.mk
-include Common/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
009GUPIK_ROV_ETH_CM4.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
009GUPIK_ROV_ETH_CM4.list \

OBJCOPY_BIN += \
009GUPIK_ROV_ETH_CM4.bin \


# All Target
all: 009GUPIK_ROV_ETH_CM4.elf secondary-outputs

# Tool invocations
009GUPIK_ROV_ETH_CM4.elf: $(OBJS) $(USER_OBJS) E:\GUPIK_ROV_MODULES\009GUPIK_ROV_ETH\CM4\STM32H745ZITX_FLASH.ld
	arm-none-eabi-gcc -o "009GUPIK_ROV_ETH_CM4.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m4 -T"E:\GUPIK_ROV_MODULES\009GUPIK_ROV_ETH\CM4\STM32H745ZITX_FLASH.ld" --specs=nosys.specs -Wl,-Map="009GUPIK_ROV_ETH_CM4.map" -Wl,--gc-sections -static --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

009GUPIK_ROV_ETH_CM4.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "009GUPIK_ROV_ETH_CM4.list"
	@echo 'Finished building: $@'
	@echo ' '

009GUPIK_ROV_ETH_CM4.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "009GUPIK_ROV_ETH_CM4.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
