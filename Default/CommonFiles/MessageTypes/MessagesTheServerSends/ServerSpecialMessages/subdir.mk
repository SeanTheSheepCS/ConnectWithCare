################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/EndOfDataMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorBoardNotFoundMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorNoAuthMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorUserNotFoundMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorWriteFailedMessage.cpp \
../CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/WriteSuccessfulMessage.cpp 

OBJS += \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/EndOfDataMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorBoardNotFoundMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorNoAuthMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorUserNotFoundMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorWriteFailedMessage.o \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/WriteSuccessfulMessage.o 

CPP_DEPS += \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/EndOfDataMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorBoardNotFoundMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorNoAuthMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorUserNotFoundMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/ErrorWriteFailedMessage.d \
./CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/WriteSuccessfulMessage.d 


# Each subdirectory must supply rules for building sources it contributes
CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/%.o: ../CommonFiles/MessageTypes/MessagesTheServerSends/ServerSpecialMessages/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: Cygwin C++ Compiler'
	g++ -O2 -g -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


