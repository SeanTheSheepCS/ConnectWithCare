################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/CreatePostingImageMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/CreatePostingMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/LoginMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/LogoutMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/SendUserMessageImageMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/SendUserMessageMessage.cpp 

OBJS += \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/CreatePostingImageMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/CreatePostingMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/LoginMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/LogoutMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/SendUserMessageImageMessage.o \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/SendUserMessageMessage.o 

CPP_DEPS += \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/CreatePostingImageMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/CreatePostingMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/LoginMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/LogoutMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/SendUserMessageImageMessage.d \
./CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/SendUserMessageMessage.d 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/%.o: ../CommonFiles/MessageTypes/MessagesTheClientSends/ClientBasicMessages/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


