#include <string>
#include "UserMessageHistoryMessage.h"
#include <iostream>

UserMessageHistoryMessage::UserMessageHistoryMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientRequestMessage(lengthArg, messageAsCharArrayArg)
{
	unsigned long int usernameStartIndex = this->getIndexOfFirstData();
	char* usernameToGetHistoryWithAsCharArray = new char[lengthArg - usernameStartIndex];
	int indexInUsernameCharArray = 0;
	for(unsigned int i = usernameStartIndex; i < lengthArg; i++)
	{
		usernameToGetHistoryWithAsCharArray[indexInUsernameCharArray] = messageAsCharArrayArg[i];
		indexInUsernameCharArray++;
	}
	usernameToGetHistoryWith = std::string(usernameToGetHistoryWithAsCharArray);

}

UserMessageHistoryMessage::UserMessageHistoryMessage(const UserMessageHistoryMessage& other) : ClientRequestMessage(other)
{
	this->usernameToGetHistoryWith = other.usernameToGetHistoryWith;
}

UserMessageHistoryMessage& UserMessageHistoryMessage::operator=(const UserMessageHistoryMessage& rhs)
{
	if(this != &rhs)
	{
		ClientRequestMessage::operator=(rhs);
		this->usernameToGetHistoryWith = rhs.usernameToGetHistoryWith;
	}
	return *this;
}

UserMessageHistoryMessage::~UserMessageHistoryMessage()
{
	usernameToGetHistoryWith = "";
}

std::string UserMessageHistoryMessage::getUsernameToGetHistoryWith()
{
	return usernameToGetHistoryWith;
}
