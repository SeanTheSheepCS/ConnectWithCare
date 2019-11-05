#include "LogoutMessage.h"

LogoutMessage::LogoutMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientBasicMessage(lengthArg, messageAsCharArrayArg)
{

}

LogoutMessage::LogoutMessage(const LogoutMessage& other) : ClientBasicMessage(other)
{

}

LogoutMessage& LogoutMessage::operator=(const LogoutMessage& rhs)
{
	if(this != &rhs)
	{
		ClientBasicMessage::operator=(rhs);
	}
	return *this;
}

LogoutMessage::~LogoutMessage()
{

}
