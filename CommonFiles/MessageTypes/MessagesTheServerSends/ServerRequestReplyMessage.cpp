#include "ServerRequestReplyMessages.h"
#include <iostream>

ServerRequestReplyMessage::ServerRequestReplyMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg): Message(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* messageCharArray = Message::getMessageAsCharArray();
	//Reading message code
	messageCode = messageCharArray[0];

	//Reading the data length (variable length quantity)
	dataLengthInBytes = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(messageCharArray[1]));
	indexOfFirstData = 1 /* FOR THE MESSAGE CODE*/ + Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
}

ServerRequestReplyMessage::ServerRequestReplyMessage(const ServerRequestReplyMessage& other): Message(other)
{
	this->messageCode = other.messageCode;
	this->dataLengthInBytes = other.dataLengthInBytes;
	this->indexOfFirstData = other.indexOfFirstData;
}

ServerRequestReplyMessage& ServerRequestReplyMessage::operator=(const ServerRequestReplyMessage& rhs)
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

ServerRequestReplyMessage::~ServerRequestReplyMessage()
{
	messageCode = 0;
	dataLengthInBytes = 0;
	indexOfFirstData = 0;
}

unsigned char ServerRequestReplyMessage::getMessageCode()
{
	return messageCode;
}

unsigned long int ServerRequestReplyMessage::getDataLengthInBytes()
{
	return dataLengthInBytes;
}

unsigned long int ServerRequestReplyMessage::getIndexOfFirstData()
{
	return indexOfFirstData;
}
