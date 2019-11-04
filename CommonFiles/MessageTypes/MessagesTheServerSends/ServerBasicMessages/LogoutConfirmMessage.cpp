#include "LogoutConfirmMessage.h"

LogoutConfirmMessage::LogoutConfirmMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ServerBasicMessage(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* pointerToStartOfMessage = &(Message::getMessageAsCharArray()[0]);
	unsigned long int indexOfStartOfData = ServerBasicMessage::getIndexOfFirstData();
	const unsigned char* dataArray = &(pointerToStartOfMessage[indexOfStartOfData]);
	if(dataArray[0] == 1)
	{
		successBit = true;
	}
	else
	{
		successBit = false;
	}
}

LogoutConfirmMessage::LogoutConfirmMessage(const LogoutConfirmMessage& other) : ServerBasicMessage(other)
{
	successBit = other.successBit;
}

LogoutConfirmMessage& LogoutConfirmMessage::operator=(const LogoutConfirmMessage& rhs)
{
	if(this != &rhs)
	{
		ServerBasicMessage::operator=(rhs);
		this->successBit = rhs.successBit;
	}
	return *this;
}

LogoutConfirmMessage::~LogoutConfirmMessage()
{
	successBit = 0;
}

bool LogoutConfirmMessage::getSuccessBit()
{
	return successBit;
}
