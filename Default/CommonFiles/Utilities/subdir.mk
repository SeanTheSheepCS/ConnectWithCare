################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonFiles/Utilities/VariableLengthQuantityLibrary.cpp 

OBJS += \
./CommonFiles/Utilities/VariableLengthQuantityLibrary.o 

CPP_DEPS += \
./CommonFiles/Utilities/VariableLengthQuantityLibrary.d 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/Utilities/%.o: ../CommonFiles/Utilities/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


