################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := del

# All of the sources participating in the build are defined here
-include sources.mk
-include View/subdir.mk
-include ServerFiles/subdir.mk
-include CommonFiles/Utilities/subdir.mk
-include CommonFiles/UnitTests/subdir.mk
-include CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/subdir.mk
-include CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/subdir.mk
-include CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/subdir.mk
-include CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/subdir.mk
-include CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/subdir.mk
-include CommonFiles/MessageTypes/MessagesTheClientSends/subdir.mk
-include CommonFiles/subdir.mk
-include ClientFiles/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: ConnectWithCare

# Tool invocations
ConnectWithCare: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cygwin C++ Linker'
	g++  -o "ConnectWithCare" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(OBJS)$(C_UPPER_DEPS)$(CXX_DEPS)$(CPP_DEPS)$(C_DEPS) ConnectWithCare
	-@echo ' '

.PHONY: all clean dependents

-include ../makefile.targets
