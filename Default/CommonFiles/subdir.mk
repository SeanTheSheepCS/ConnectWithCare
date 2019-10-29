################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonFiles/Message.cpp \
../CommonFiles/Posting.cpp \
../CommonFiles/UserMessage.cpp 

OBJS += \
./CommonFiles/Message.o \
./CommonFiles/Posting.o \
./CommonFiles/UserMessage.o 

CPP_DEPS += \
./CommonFiles/Message.d \
./CommonFiles/Posting.d \
./CommonFiles/UserMessage.d 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/%.o: ../CommonFiles/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


