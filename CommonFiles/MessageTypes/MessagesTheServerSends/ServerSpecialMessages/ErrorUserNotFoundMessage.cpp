#include "ErrorUserNotFoundMessage.h"

ErrorUserNotFoundMessage::ErrorUserNotFoundMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ServerSpecialMessage(lengthArg, messageAsCharArrayArg)
{

}

ErrorUserNotFoundMessage::ErrorUserNotFoundMessage(const ErrorUserNotFoundMessage& other) : ServerSpecialMessage(other)
{

}

ErrorUserNotFoundMessage& ErrorUserNotFoundMessage::operator=(const ErrorUserNotFoundMessage& rhs)
{
	if(this != &rhs)
	{
		ServerSpecialMessage::operator=(rhs);
	}
	return *this;
}

ErrorUserNotFoundMessage::~ErrorUserNotFoundMessage()
{

}
