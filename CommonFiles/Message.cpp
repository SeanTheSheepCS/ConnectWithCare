#include "Message.h"
#include <string.h>

Message::Message(unsigned long int lengthArg, unsigned char* messageAsCharArrayArg)
{
	length = lengthArg;
	messageAsCharArray = new unsigned char[lengthArg];
	for(int i = 0; i < length; i++)
	{
		messageAsCharArray[i] = messageAsCharArrayArg[i];
	}
}

Message::Message(const Message& other)
{
	this->length = other.length;
	this->messageAsCharArray = new unsigned char[other.length];
	for(int i = 0; i < length; i++)
	{
		messageAsCharArray[i] = other.messageAsCharArray[i];
	}
}

Message& Message::operator=(const Message& rhs)
{
	if(this == &rhs)
	{
		this->length = rhs.length;
		delete[] messageAsCharArray;
		messageAsCharArray = new unsigned char[rhs.length];
		for(int i = 0; i < length; i++)
		{
			messageAsCharArray[i] = rhs.messageAsCharArray[i];
		}
	}
	return *this;
}

Message::~Message()
{
	length = 0;
	delete[] messageAsCharArray;
}

unsigned long int Message::getLength()
{
	return length;
}

const unsigned char* Message::getMessageAsCharArray()
{
	return messageAsCharArray;
}
