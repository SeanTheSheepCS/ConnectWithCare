#include "SendUserMessageJPEGImageMessage.h"

#include "../../../UserMessages/UserMessage.h"
#include "../../../MultimediaComponentLibrary/MultimediaComponents/AllMultimediaComponents.h"

SendUserMessageJPEGImageMessage::SendUserMessageJPEGImageMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientBasicMessage(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* dataArray = &(messageAsCharArrayArg[this->getIndexOfFirstData()]);
	unsigned long int usernameOfTheSenderLength = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(dataArray[0]));
	unsigned short int usernameOfTheSenderLengthFieldLength =  Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
	char* usernameOfTheSenderAsCharArray = new char[usernameOfTheSenderLength+1];
	for(unsigned int i = 0; i < usernameOfTheSenderLength; i++)
	{
		usernameOfTheSenderAsCharArray[i] = dataArray[usernameOfTheSenderLengthFieldLength + i];
	}
	usernameOfTheSenderAsCharArray[usernameOfTheSenderLength] = '\0';
	std::string usernameOfTheSender = std::string(usernameOfTheSenderAsCharArray);

	const unsigned char* dataArrayStartingAtUsernameOfRecipient = &(dataArray[usernameOfTheSenderLengthFieldLength + usernameOfTheSenderLength]);
	unsigned long int usernameOfTheRecipientLength = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(dataArrayStartingAtUsernameOfRecipient[0]));
	unsigned short int usernameOfTheRecipientLengthFieldLength =  Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
	char* usernameOfTheRecipientAsCharArray = new char[usernameOfTheRecipientLength+1];
	for(unsigned int i = 0; i < usernameOfTheRecipientLength; i++)
	{
		usernameOfTheRecipientAsCharArray[i] = dataArrayStartingAtUsernameOfRecipient[usernameOfTheRecipientLengthFieldLength + i];
	}
	usernameOfTheRecipientAsCharArray[usernameOfTheRecipientLength] = '\0';
	std::string usernameOfTheRecipient = std::string(usernameOfTheRecipientAsCharArray);

	const unsigned char* dataArrayStartingAtDate = &(dataArrayStartingAtUsernameOfRecipient[usernameOfTheRecipientLengthFieldLength + usernameOfTheRecipientLength]);
	Date dateCreated = Date(dataArrayStartingAtDate);

	unsigned long int indexInDataArrayThatTheMessageTextLengthStartsAt = 0 + usernameOfTheSenderLengthFieldLength + usernameOfTheSenderLength + usernameOfTheRecipientLengthFieldLength + usernameOfTheRecipientLength + 5 /* FOR THE DATE */;
	unsigned long int messageTextLength = vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(dataArray[indexInDataArrayThatTheMessageTextLengthStartsAt]));
	unsigned short int messageTextLengthFieldLength = vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
	char* messageTextAsCharArray = new char[messageTextLength+1];
	for(unsigned int i = 0; i < messageTextLength; i++)
	{
		messageTextAsCharArray[i] = dataArray[indexInDataArrayThatTheMessageTextLengthStartsAt + messageTextLengthFieldLength + i];
	}
	messageTextAsCharArray[messageTextLength] = '\0';
	std::string messageText = std::string(messageTextAsCharArray);

	this->multimediaComponents = new vector<MultimediaComponent>();

	const unsigned char* dataArrayStartingAtMultimediaContent = &(dataArrayStartingAtDate[0 + 5 /* FOR THE DATE */ + messageTextLengthFieldLength + messageTextLength]);
	unsigned long int numberOfMultimediaContentsOnTheMessage = vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(dataArrayStartingAtMultimediaContent);
	unsigned short int lengthOfNumberOfMultimediaContentsOnTheMessageField = vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();

	if(numberOfMultimediaContentsOnTheMessage != 0)
	{
		const unsigned char* dataArrayStartingAtCurrentMMCComponent = &(dataArrayStartingAtMultimediaContent[lengthOfNumberOfMultimediaContentsOnTheMessageField]);
		for(unsigned int i = 0; i < numberOfMultimediaContentsOnTheMessage; i++)
		{
			unsigned long int lengthOfMultimediaComponentID = vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(dataArrayStartingAtCurrentMMCComponent);
			unsigned long int lengthOflengthOfMultimediaComponentIDField = vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();

			const unsigned char* dataArrayStartingAtCurrentMMCComponentID = &(dataArrayStartingAtCurrentMMCComponent[lengthOflengthOfMultimediaComponentIDField]);
			unsigned long int multimediaContentID = vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(dataArrayStartingAtCurrentMMCComponentID);

			const unsigned char* dataArrayStartingAtCurrentMMCComponentFilenameLengthField = &(dataArrayStartingAtCurrentMMCComponentID[lengthOfMultimediaComponentID]);
			unsigned long int lengthOfMMCComponentFilename = vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(dataArrayStartingAtCurrentMMCComponentFilenameLengthField);
			unsigned short int lengthOfLengthOfMMCComponentFilenameField = vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();

			const unsigned char* dataArrayStartingAtCurrentMMCComponentFilename = &(dataArrayStartingAtCurrentMMCComponentFilenameLengthField[lengthOfLengthOfMMCComponentFilenameField]);
			char* filenameAsCharArray = new char[lengthOfMMCComponentFilename+1];
			for(unsigned int i = 0; i < lengthOfMMCComponentFilename; i++)
			{
				filenameAsCharArray[i] = dataArrayStartingAtCurrentMMCComponentFilename[i];
			}
			filenameAsCharArray[lengthOfMMCComponentFilename] = '\0';
			std::string filename = std::string(filenameAsCharArray);
			MMCImageJPEG* componentToAddToList = new MMCImageJPEG(filename, multimediaContentID);
			this->multimediaComponents->push_back(*componentToAddToList);
			delete componentToAddToList;
			delete[] filenameAsCharArray;
			dataArrayStartingAtCurrentMMCComponent = &(dataArrayStartingAtCurrentMMCComponentFilename[lengthOfMMCComponentFilename]);
		}
	}

	theUserMessage = new UserMessage(usernameOfTheSender, usernameOfTheRecipient, dateCreated, messageText);
	delete[] usernameOfTheSenderAsCharArray;
	delete[] usernameOfTheRecipientAsCharArray;
	delete[] messageTextAsCharArray;
}

SendUserMessageJPEGImageMessage::SendUserMessageJPEGImageMessage(const SendUserMessageJPEGImageMessage& other) : ClientBasicMessage(other)
{
	this->theUserMessage = new UserMessage(other.getUserMessage());
	this->multimediaComponents = new vector<MultimediaComponent>();
	for(unsigned int i = 0; i < other.getMultimediaComponents().size(); i++)
	{
		this->multimediaComponents->push_back(other.getMultimediaComponents().at(i));
	}
}

SendUserMessageJPEGImageMessage& SendUserMessageJPEGImageMessage::operator=(const SendUserMessageJPEGImageMessage& rhs)
{
	if(this != &rhs)
	{
		ClientBasicMessage::operator=(rhs);
		delete theUserMessage;
		this->theUserMessage = new UserMessage(rhs.getUserMessage());
		delete multimediaComponents;
		this->multimediaComponents = new vector<MultimediaComponent>();
		for(unsigned int i = 0; i < rhs.getMultimediaComponents().size(); i++)
		{
			this->multimediaComponents->push_back(rhs.getMultimediaComponents().at(i));
		}
	}
	return *this;
}

SendUserMessageJPEGImageMessage::~SendUserMessageJPEGImageMessage()
{
	delete theUserMessage;
	delete multimediaComponents;
}

const UserMessage SendUserMessageJPEGImageMessage::getUserMessage() const
{
	return *theUserMessage;
}

const vector<MultimediaComponent> SendUserMessageJPEGImageMessage::getMultimediaComponents() const
{
	return *multimediaComponents;
}
