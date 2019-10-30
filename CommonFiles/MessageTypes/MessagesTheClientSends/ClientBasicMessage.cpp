#include "ClientBasicMessages.h"
#include "../../Utilities/VariableLengthQuantityLibrary.h"
#include <iostream>

ClientBasicMessage::ClientBasicMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : Message(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* messageCharArray = Message::getMessageAsCharArray();
	//Reading message code
	messageCode = messageCharArray[0];
	//Reading the data length (variable length quantity)
	dataLengthInBytes = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(messageCharArray[1]));
	indexOfFirstData = 1 /* FOR THE MESSAGE CODE*/ + Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
}

ClientBasicMessage::~ClientBasicMessage()
{
	messageCode = 0;
	dataLengthInBytes = 0;
	indexOfFirstData = 0;
}


ClientBasicMessage::ClientBasicMessage(const ClientBasicMessage& other) : Message(other)
{
	this->messageCode = other.messageCode;
	this->dataLengthInBytes = other.dataLengthInBytes;
	this->indexOfFirstData = other.indexOfFirstData;
}

ClientBasicMessage& ClientBasicMessage::operator=(const ClientBasicMessage& rhs)
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

unsigned char ClientBasicMessage::getMessageCode()
{
	return messageCode;
}

unsigned long int ClientBasicMessage::getDataLengthInBytes()
{
	return dataLengthInBytes;
}

unsigned long int ClientBasicMessage::getIndexOfFirstData()
{
	return indexOfFirstData;
}
