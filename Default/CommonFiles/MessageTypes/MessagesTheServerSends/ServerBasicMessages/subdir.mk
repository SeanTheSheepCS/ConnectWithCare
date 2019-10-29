################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/LoginAuthMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/LogoutConfirmMessage.cpp 

OBJS += \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/LoginAuthMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/LogoutConfirmMessage.o 

CPP_DEPS += \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/LoginAuthMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/LogoutConfirmMessage.d 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/%.o: ../CommonFiles/MessageTypes/MessagesTheServerSends/ServerBasicMessages/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


