################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/BoardHistoryMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/BoardSearchMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/UserMessageHistoryAllMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/UserMessageHistoryMessage.cpp 

OBJS += \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/BoardHistoryMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/BoardSearchMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/UserMessageHistoryAllMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/UserMessageHistoryMessage.o 

CPP_DEPS += \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/BoardHistoryMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/BoardSearchMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/UserMessageHistoryAllMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/UserMessageHistoryMessage.d 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/%.o: ../CommonFiles/MessageTypes/MessagesTheClientSends/ClientRequestMessages/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


