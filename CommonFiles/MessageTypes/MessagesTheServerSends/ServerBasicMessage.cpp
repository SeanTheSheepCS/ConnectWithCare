#include "ServerBasicMessages.h"

ServerBasicMessage::ServerBasicMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : Message(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* messageCharArray = Message::getMessageAsCharArray();
	//Reading message code
	messageCode = messageCharArray[0];
	//Reading the data length (variable length quantity)
	dataLengthInBytes = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(messageCharArray[1]));
	indexOfFirstData = 1 /* FOR THE MESSAGE CODE*/ + Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
}

ServerBasicMessage::ServerBasicMessage(const ServerBasicMessage& other) : Message(other)
{
	this->messageCode = other.messageCode;
	this->dataLengthInBytes = other.dataLengthInBytes;
	this->indexOfFirstData = other.indexOfFirstData;
}

ServerBasicMessage& ServerBasicMessage::operator=(const ServerBasicMessage& rhs)
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

ServerBasicMessage::~ServerBasicMessage()
{
	messageCode = 0;
	dataLengthInBytes = 0;
	indexOfFirstData = 0;
}

unsigned char ServerBasicMessage::getMessageCode()
{
	return messageCode;
}

unsigned long int ServerBasicMessage::getDataLengthInBytes()
{
	return dataLengthInBytes;
}

unsigned long int ServerBasicMessage::getIndexOfFirstData()
{
	return indexOfFirstData;
}
