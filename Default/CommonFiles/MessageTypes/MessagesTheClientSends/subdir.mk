################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessage.cpp 

OBJS += \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessage.o 

CPP_DEPS += \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessage.d 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/MessageTypes/MessagesTheClientSends/%.o: ../CommonFiles/MessageTypes/MessagesTheClientSends/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

