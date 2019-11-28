#ifndef SEND_USER_MESSAGE_IMAGE_MESSAGE_H
#define SEND_USER_MESSAGE_IMAGE_MESSAGE_H

#include <string>
#include <vector>

#include "../../../UserMessages/UserMessage.h"
#include "../../../MultimediaComponentLibrary/MultimediaComponents/AllMultimediaComponents.h"
#include "../ClientBasicMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"

class SendUserMessageJPEGImageMessage : public ClientBasicMessage
{
	public:
		SendUserMessageJPEGImageMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		SendUserMessageJPEGImageMessage(const SendUserMessageJPEGImageMessage& other);
		virtual SendUserMessageJPEGImageMessage& operator=(const SendUserMessageJPEGImageMessage& rhs);
	    virtual ~SendUserMessageJPEGImageMessage();
		const UserMessage getUserMessage() const;
		const vector<MultimediaComponent> getMultimediaComponents() const;
	protected:
		//
	private:
		UserMessage* theUserMessage;
		vector<MultimediaComponent>* multimediaComponents;
};

#endif
