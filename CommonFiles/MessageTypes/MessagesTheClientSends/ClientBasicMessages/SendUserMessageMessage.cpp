#include "SendUserMessageMessage.h"
#include "../../../UserMessage.h"

SendUserMessageMessage::SendUserMessageMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientBasicMessage(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* dataArray = &(messageAsCharArrayArg[this->getIndexOfFirstData()]);
	unsigned long int usernameOfTheSenderLength = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(dataArray[0]));
	unsigned short int usernameOfTheSenderLengthFieldLength =  Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
	char* usernameOfTheSenderAsCharArray = new char[usernameOfTheSenderLength+1];
	for(int i = 0; i < usernameOfTheSenderLength; i++)
	{
		usernameOfTheSenderAsCharArray[i] = dataArray[usernameOfTheSenderLengthFieldLength + i];
	}
	usernameOfTheSenderAsCharArray[usernameOfTheSenderLength] = '\0';
	std::string usernameOfTheSender = std::string(usernameOfTheSenderAsCharArray);

	const unsigned char* dataArrayStartingAtUsernameOfRecipient = &(dataArray[usernameOfTheSenderLengthFieldLength + usernameOfTheSenderLength]);
	unsigned long int usernameOfTheRecipientLength = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(dataArrayStartingAtUsernameOfRecipient[0]));
	unsigned short int usernameOfTheRecipientLengthFieldLength =  Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
	char* usernameOfTheRecipientAsCharArray = new char[usernameOfTheRecipientLength+1];
	for(int i = 0; i < usernameOfTheRecipientLength; i++)
	{
		usernameOfTheRecipientAsCharArray[i] = dataArrayStartingAtUsernameOfRecipient[usernameOfTheRecipientLengthFieldLength + i];
	}
	usernameOfTheRecipientAsCharArray[usernameOfTheRecipientLength] = '\0';
	std::string usernameOfTheRecipient = std::string(usernameOfTheRecipientAsCharArray);

	const unsigned char* dataArrayStartingAtDate = &(dataArrayStartingAtUsernameOfRecipient[usernameOfTheRecipientLengthFieldLength + usernameOfTheRecipientLength]);
	Date dateCreated = Date(dataArrayStartingAtDate);

	unsigned long int indexInDataArrayThatTheMessageTextStartsAt = 0 + usernameOfTheSenderLengthFieldLength + usernameOfTheSenderLength + usernameOfTheRecipientLengthFieldLength + usernameOfTheRecipientLength + 5 /* FOR THE DATE */;
	unsigned long int messageTextLength = this->getDataLengthInBytes() - indexInDataArrayThatTheMessageTextStartsAt;
	char* messageTextAsCharArray = new char[messageTextLength+1];
	for(int i = 0; i < messageTextLength; i++)
	{
		messageTextAsCharArray[i] = dataArray[indexInDataArrayThatTheMessageTextStartsAt + i];
	}
	messageTextAsCharArray[messageTextLength] = '\0';
	std::string messageText = std::string(messageTextAsCharArray);

	theUserMessage = new UserMessage(usernameOfTheSender, usernameOfTheRecipient, dateCreated, messageText);
	delete[] usernameOfTheSenderAsCharArray;
	delete[] usernameOfTheRecipientAsCharArray;
	delete[] messageTextAsCharArray;
}

SendUserMessageMessage::SendUserMessageMessage(const SendUserMessageMessage& other) : ClientBasicMessage(other)
{
	this->theUserMessage = new UserMessage(other.getUserMessage());
}

SendUserMessageMessage& SendUserMessageMessage::operator=(const SendUserMessageMessage& rhs)
{
	if(this != &rhs)
	{
		ClientBasicMessage::operator=(rhs);
		delete theUserMessage;
		this->theUserMessage = new UserMessage(rhs.getUserMessage());
	}
	return *this;
}

SendUserMessageMessage::~SendUserMessageMessage()
{
	delete theUserMessage;
}

const UserMessage SendUserMessageMessage::getUserMessage() const
{
	return *theUserMessage;
}
