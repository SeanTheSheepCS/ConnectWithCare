#include "ErrorWriteFailedMessage.h"

ErrorWriteFailedMessage::ErrorWriteFailedMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ServerSpecialMessage(lengthArg, messageAsCharArrayArg)
{

}

ErrorWriteFailedMessage::ErrorWriteFailedMessage(const ErrorWriteFailedMessage& other) : ServerSpecialMessage(other)
{

}

ErrorWriteFailedMessage& ErrorWriteFailedMessage::operator=(const ErrorWriteFailedMessage& rhs)
{
	if(this != &rhs)
	{
		ServerSpecialMessage::operator=(rhs);
	}
	return *this;
}

ErrorWriteFailedMessage::~ErrorWriteFailedMessage()
{

}
