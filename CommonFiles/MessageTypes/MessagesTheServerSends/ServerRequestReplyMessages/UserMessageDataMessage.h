#ifndef USER_MESSAGE_DATA_MESSAGE_H
#define USER_MESSAGE_DATA_MESSAGE_H

#include "../../../UserMessages/UserMessage.h"
#include "../ServerRequestReplyMessages.h"

class UserMessageDataMessage : public ServerRequestReplyMessage
{
	public:
		UserMessageDataMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		UserMessageDataMessage(const UserMessageDataMessage& other);
		virtual UserMessageDataMessage& operator=(const UserMessageDataMessage& rhs);
		virtual ~UserMessageDataMessage();
		UserMessage getUserMessage();
	protected:
		//
	private:
		UserMessage* associatedUserMessage;
};

#endif
