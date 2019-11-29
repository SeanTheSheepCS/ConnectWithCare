#include "Message.h"
#include <string.h>
#include <iostream>

#include "Utilities/VariableLengthQuantityLibrary.h"

Message::Message(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg)
{
	vlqConverter = VariableLengthQuantityConverter();
	length = lengthArg;
	messageAsCharArray = new unsigned char[lengthArg];
	for(unsigned int i = 0; i < length; i++)
	{
		messageAsCharArray[i] = messageAsCharArrayArg[i];
	}
}

Message::Message(const Message& other)
{
	this->length = other.length;
	this->messageAsCharArray = new unsigned char[other.length];
	for(unsigned int i = 0; i < length; i++)
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
		for(unsigned int i = 0; i < length; i++)
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

unsigned long int Message::getLength() const
{
	return length;
}

const unsigned char* Message::getMessageAsCharArray() const
{
	return messageAsCharArray;
}

void Message::printMessageToStdOut() const
{
	for(unsigned int i = 0; i < this->length; i++)
	{
		std::cout << std::hex << (this->messageAsCharArray)[i] << std::endl;
	}
}
