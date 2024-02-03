################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
LSS += \
Keypad_calc.lss \

FLASH_IMAGE += \
Keypad_calc.hex \

SIZEDUMMY += \
sizedummy \


# All Target
all: Keypad_calc.elf secondary-outputs

# Tool invocations
Keypad_calc.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Keypad_calc.map -mmcu=atmega32 -o "Keypad_calc.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Keypad_calc.lss: Keypad_calc.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Keypad_calc.elf  >"Keypad_calc.lss"
	@echo 'Finished building: $@'
	@echo ' '

Keypad_calc.hex: Keypad_calc.elf
	@echo 'Create Flash image (ihex format)'
	-avr-objcopy -R .eeprom -R .fuse -R .lock -R .signature -O ihex Keypad_calc.elf  "Keypad_calc.hex"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Keypad_calc.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega32 Keypad_calc.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(FLASH_IMAGE)$(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Keypad_calc.elf
	-@echo ' '

secondary-outputs: $(LSS) $(FLASH_IMAGE) $(SIZEDUMMY)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
