#include <string>
#include "UserMessageHistoryAllMessage.h"
#include <iostream>

UserMessageHistoryAllMessage::UserMessageHistoryAllMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientRequestMessage(lengthArg, messageAsCharArrayArg)
{

}

UserMessageHistoryAllMessage::UserMessageHistoryAllMessage(const UserMessageHistoryAllMessage& other) : ClientRequestMessage(other)
{

}

UserMessageHistoryAllMessage& UserMessageHistoryAllMessage::operator=(const UserMessageHistoryAllMessage& rhs)
{
	if(this != &rhs)
	{
		ClientRequestMessage::operator=(rhs);
	}
	return *this;
}

UserMessageHistoryAllMessage::~UserMessageHistoryAllMessage()
{

}
