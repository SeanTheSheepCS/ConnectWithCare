#ifndef USER_MESSAGE_H
#define USER_MESSAGE_H

#include "../Date.h"
#include <string>

class UserMessage
{
	public:
		UserMessage(std::string usernameOfTheSenderArg, std::string usernameOfTheRecipientArg, Date dateCreatedArg, std::string messageTextArg);
		UserMessage(const UserMessage& other);
		UserMessage& operator=(const UserMessage& rhs);
		~UserMessage();
		Date getDateCreated() const;
		std::string getMessageText() const;
		std::string getUsernameOfTheSender() const;
		std::string getUsernameOfTheRecipient() const;

		bool operator<(const UserMessage& rhs) const;
	protected:
		//
	private:
		Date* dateCreated;
		std::string* messageText;
		std::string* usernameOfTheSender;
		std::string* usernameOfTheRecipient;
};

#endif
