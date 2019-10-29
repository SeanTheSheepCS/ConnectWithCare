################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ClientFiles/ClientController.cpp \
../ClientFiles/ClientMessageConverter.cpp \
../ClientFiles/ClientMessageCreator.cpp 

OBJS += \
./ClientFiles/ClientController.o \
./ClientFiles/ClientMessageConverter.o \
./ClientFiles/ClientMessageCreator.o 

CPP_DEPS += \
./ClientFiles/ClientController.d \
./ClientFiles/ClientMessageConverter.d \
./ClientFiles/ClientMessageCreator.d 


# Each subdirectory must supply rules for building sources it contributes
ClientFiles/%.o: ../ClientFiles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


