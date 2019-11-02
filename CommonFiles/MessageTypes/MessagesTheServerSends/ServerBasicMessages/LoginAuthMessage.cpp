#include "LoginAuthMessage.h"

LoginAuthMessage::LoginAuthMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ServerBasicMessage(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* pointerToStartOfMessage = &(Message::getMessageAsCharArray()[0]);
	unsigned long int indexOfStartOfData = ServerBasicMessage::getIndexOfFirstData();
	const unsigned char* dataArray = &(pointerToStartOfMessage[indexOfStartOfData]);
	if(dataArray[0] == 1)
	{
		validBit = true;
	}
	else
	{
		validBit = false;
	}
}

LoginAuthMessage::LoginAuthMessage(const LoginAuthMessage& other) : ServerBasicMessage(other)
{
	validBit = other.validBit;
}

LoginAuthMessage& LoginAuthMessage::operator=(const LoginAuthMessage& rhs)
{
	if(this != &rhs)
	{
		ServerBasicMessage::operator=(rhs);
		this->validBit = rhs.validBit;
	}
	return *this;
}

LoginAuthMessage::~LoginAuthMessage()
{
	validBit = 0;
}

bool LoginAuthMessage::getValidBit()
{
	return validBit;
}
