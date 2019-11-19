#include "UserMessage.h"

UserMessage::UserMessage(std::string usernameOfTheSenderArg, std::string usernameOfTheRecipientArg, Date dateCreatedArg, std::string messageTextArg)
{
	usernameOfTheSender = new std::string(usernameOfTheSenderArg);
	usernameOfTheRecipient = new std::string(usernameOfTheRecipientArg);
	dateCreated = new Date(dateCreatedArg);
	messageText = new std::string(messageTextArg);
}

UserMessage::UserMessage(const UserMessage& other)
{
	this->usernameOfTheSender = new std::string(other.getUsernameOfTheSender());
	this->usernameOfTheRecipient = new std::string(other.getUsernameOfTheRecipient());
	this->dateCreated = new Date(other.getDateCreated());
	this->messageText = new std::string(other.getMessageText());
}

UserMessage& UserMessage::operator=(const UserMessage& rhs)
{
	if(this != &rhs)
	{
		delete usernameOfTheSender;
		delete usernameOfTheRecipient;
		delete dateCreated;
		delete messageText;
		this->usernameOfTheSender = new std::string(rhs.getUsernameOfTheSender());
		this->usernameOfTheRecipient = new std::string(rhs.getUsernameOfTheRecipient());
		this->dateCreated = new Date(rhs.getDateCreated());
		this->messageText = new std::string(rhs.getMessageText());
	}
	return *this;
}

UserMessage::~UserMessage()
{
	delete usernameOfTheSender;
	delete usernameOfTheRecipient;
	delete dateCreated;
	delete messageText;
}

Date UserMessage::getDateCreated() const
{
	return *dateCreated;
}

std::string UserMessage::getMessageText() const
{
	return *messageText;
}

std::string UserMessage::getUsernameOfTheSender() const
{
	return *usernameOfTheSender;
}

std::string UserMessage::getUsernameOfTheRecipient() const
{
	return *usernameOfTheRecipient;
}
