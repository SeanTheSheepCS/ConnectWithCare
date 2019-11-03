#include "WriteSuccessfulMessage.h"

WriteSuccessfulMessage::WriteSuccessfulMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ServerSpecialMessage(lengthArg, messageAsCharArrayArg)
{

}

WriteSuccessfulMessage::WriteSuccessfulMessage(const WriteSuccessfulMessage& other) : ServerSpecialMessage(other)
{

}

WriteSuccessfulMessage& WriteSuccessfulMessage::operator=(const WriteSuccessfulMessage& rhs)
{
	if(this != &rhs)
	{
		ServerSpecialMessage::operator=(rhs);
	}
	return *this;
}

WriteSuccessfulMessage::~WriteSuccessfulMessage()
{

}
