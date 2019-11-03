#include "ErrorNoAuthMessage.h"

ErrorNoAuthMessage::ErrorNoAuthMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ServerSpecialMessage(lengthArg, messageAsCharArrayArg)
{

}

ErrorNoAuthMessage::ErrorNoAuthMessage(const ErrorNoAuthMessage& other) : ServerSpecialMessage(other)
{

}

ErrorNoAuthMessage& ErrorNoAuthMessage::operator=(const ErrorNoAuthMessage& rhs)
{
	if(this != &rhs)
	{
		ServerSpecialMessage::operator=(rhs);
	}
	return *this;
}

ErrorNoAuthMessage::~ErrorNoAuthMessage()
{

}
