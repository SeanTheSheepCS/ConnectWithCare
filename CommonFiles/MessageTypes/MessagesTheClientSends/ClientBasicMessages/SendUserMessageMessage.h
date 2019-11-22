#ifndef SEND_USER_MESSAGE_MESSAGE_H
#define SEND_USER_MESSAGE_MESSAGE_H

#include <string>
#include "../ClientBasicMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"
#include "../../../UserMessage.h"

class SendUserMessageMessage : public ClientBasicMessage
{
	public:
		SendUserMessageMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		SendUserMessageMessage(const SendUserMessageMessage& other);
		virtual SendUserMessageMessage& operator=(const SendUserMessageMessage& rhs);
	    virtual ~SendUserMessageMessage();
		const UserMessage getUserMessage() const;
	protected:
		//
	private:
		UserMessage* theUserMessage;
};

#endif
