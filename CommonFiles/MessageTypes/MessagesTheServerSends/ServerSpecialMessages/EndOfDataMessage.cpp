#include "EndOfDataMessage.h"

EndOfDataMessage::EndOfDataMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ServerSpecialMessage(lengthArg, messageAsCharArrayArg)
{

}

EndOfDataMessage::EndOfDataMessage(const EndOfDataMessage& other) : ServerSpecialMessage(other)
{

}

EndOfDataMessage& EndOfDataMessage::operator=(const EndOfDataMessage& rhs)
{
	if(this != &rhs)
	{
		ServerSpecialMessage::operator=(rhs);
	}
	return *this;
}

EndOfDataMessage::~EndOfDataMessage()
{

}
