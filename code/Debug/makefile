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
Calculator_without_ans.lss \

SIZEDUMMY += \
sizedummy \


# All Target
all: Calculator_without_ans.elf secondary-outputs

# Tool invocations
Calculator_without_ans.elf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: AVR C Linker'
	avr-gcc -Wl,-Map,Calculator_without_ans.map -mmcu=atmega16 -o "Calculator_without_ans.elf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

Calculator_without_ans.lss: Calculator_without_ans.elf
	@echo 'Invoking: AVR Create Extended Listing'
	-avr-objdump -h -S Calculator_without_ans.elf  >"Calculator_without_ans.lss"
	@echo 'Finished building: $@'
	@echo ' '

sizedummy: Calculator_without_ans.elf
	@echo 'Invoking: Print Size'
	-avr-size --format=avr --mcu=atmega16 Calculator_without_ans.elf
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(ELFS)$(OBJS)$(ASM_DEPS)$(S_DEPS)$(SIZEDUMMY)$(S_UPPER_DEPS)$(LSS)$(C_DEPS) Calculator_without_ans.elf
	-@echo ' '

secondary-outputs: $(LSS) $(SIZEDUMMY)

.PHONY: all clean dependents

-include ../makefile.targets
