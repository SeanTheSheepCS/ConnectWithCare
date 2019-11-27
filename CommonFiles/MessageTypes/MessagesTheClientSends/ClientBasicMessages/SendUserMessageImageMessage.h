#ifndef SEND_USER_MESSAGE_IMAGE_MESSAGE_H
#define SEND_USER_MESSAGE_IMAGE_MESSAGE_H

#include <string>
#include <vector>

#include "../../../UserMessages/UserMessage.h"
#include "../ClientBasicMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"

class SendUserMessageImageMessage : public ClientBasicMessage
{
	public:
		SendUserMessageImageMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		SendUserMessageImageMessage(const SendUserMessageImageMessage& other);
		virtual SendUserMessageImageMessage& operator=(const SendUserMessageImageMessage& rhs);
	    virtual ~SendUserMessageImageMessage();
		const UserMessage getUserMessage() const;
	protected:
		//
	private:
		UserMessage* theUserMessage;
		vector<unsigned long int> MMCImageIDs;
};

#endif
