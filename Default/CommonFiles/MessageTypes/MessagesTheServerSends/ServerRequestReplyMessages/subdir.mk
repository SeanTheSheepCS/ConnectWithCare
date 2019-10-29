################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/PostingDataMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/PostingImageDataMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/UserMessageDataMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/UserMessageImageDataMessage.cpp 

OBJS += \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/PostingDataMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/PostingImageDataMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/UserMessageDataMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/UserMessageImageDataMessage.o 

CPP_DEPS += \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/PostingDataMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/PostingImageDataMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/UserMessageDataMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/UserMessageImageDataMessage.d 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/%.o: ../CommonFiles/MessageTypes/MessagesTheServerSends/ServerRequestReplyMessages/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


