#include "ServerSpecialMessages.h"

ServerSpecialMessage::ServerSpecialMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : Message(lengthArg, messageAsCharArrayArg)
{
	messageCode = messageAsCharArrayArg[0];
}

ServerSpecialMessage::ServerSpecialMessage(const ServerSpecialMessage& other) : Message(other)
{
	messageCode = other.messageCode;
}

ServerSpecialMessage& ServerSpecialMessage::operator=(const ServerSpecialMessage& rhs)
{
	if(this != &rhs)
	{
		Message::operator=(rhs);
		this->messageCode = rhs.messageCode;
	}
	return *this;
}

ServerSpecialMessage::~ServerSpecialMessage()
{
	messageCode = 0;
}

unsigned char ServerSpecialMessage::getMessageCode()
{
	return messageCode;
}
