#include "ClientBasicMessages.h"

ClientBasicMessage::ClientBasicMessage(Message messageToTurnIntoClientBasicMessage) : Message(messageToTurnIntoClientBasicMessage)
{
	char[] messageCharArray = getMessageAsCharArray;
	//Reading message code
	messageCode = messageCharArray[0];
	//Reading the data length (variable length quantity)
	dataLengthInBytes = convertVariableLengthQuantityToUnsignedLongInt(&(messageCharArray[1]));
	indexOfFirstData = getVariableLengthQuantityByteLengthOfLastConversion();
}

ClientBasicMessage::~ClientBasicMessage()
{
	messageCode = 0;
	dataLengthInBytes = 0;
	indexOfFirstData = 0;
}

ClientBasicMessage(const ClientBasicMessage& other)
{
	Message(other);
	this->messageCode = messageCode();
	this->dataLengthInBytes = other.dataLengthInBytes;
	this->indexOfFirstData = other.indexOfFirstData;
}

ClientBasicMessage& operator=(const ClientBasicMessage& rhs)
{
	if(this != &rhs)
	{
		Message::operator=(rhs);
		this->messageCode = rhs.messageCode;
		this->dataLengthInBytes = rhs.dataLengthInBytes;
		this->indexOfFirstData = rhs.indexOfFirstData;
	}
	return *this;
}

unsigned char getMessageCode()
{
	return messageCode;
}

unsigned long int getDataLengthInBytes()
{
	return dataLengthInBytes;
}

unsigned long int getIndexOfFirstData()
{
	return indexOfFirstData;
}
