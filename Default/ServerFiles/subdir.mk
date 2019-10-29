################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../ServerFiles/ServerController.cpp \
../ServerFiles/ServerMessageConverter.cpp \
../ServerFiles/ServerMessageCreator.cpp 

OBJS += \
./ServerFiles/ServerController.o \
./ServerFiles/ServerMessageConverter.o \
./ServerFiles/ServerMessageCreator.o 

CPP_DEPS += \
./ServerFiles/ServerController.d \
./ServerFiles/ServerMessageConverter.d \
./ServerFiles/ServerMessageCreator.d 


# Each subdirectory must supply rules for building sources it contributes
ServerFiles/%.o: ../ServerFiles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


