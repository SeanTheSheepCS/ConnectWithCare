#include "LoginMessage.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"
#include <string>
#include <iostream>

LoginMessage::LoginMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientBasicMessage(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* pointerToStartOfMessage = &(Message::getMessageAsCharArray()[0]);
	unsigned long int indexOfStartOfData = ClientBasicMessage::getIndexOfFirstData();
	const unsigned char* dataArray = &(pointerToStartOfMessage[indexOfStartOfData]);
	unsigned long int usernameLength = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(dataArray[0]));
	unsigned long int usernameLengthFieldLength = Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
	unsigned long int passwordLength = ClientBasicMessage::getDataLengthInBytes() - usernameLength - usernameLengthFieldLength;
	char* usernameAsCharArray = new char[usernameLength+1];
	char* passwordAsCharArray = new char[passwordLength+1];
	int indexInDataArray = usernameLengthFieldLength /*AN INITIAL OFFSET SO THAT WE DO NOT READ THE UNL FIELD AGAIN */;
	for(unsigned int i = 0; i < usernameLength; i++)
	{
		usernameAsCharArray[i] = dataArray[indexInDataArray];
		indexInDataArray++;
	}
	usernameAsCharArray[usernameLength] = '\0';
	username = std::string(usernameAsCharArray);
	for(unsigned int i = 0; i < passwordLength; i++)
	{
		passwordAsCharArray[i] = dataArray[indexInDataArray];
		indexInDataArray++;
	}
	passwordAsCharArray[passwordLength] = '\0';
	password = std::string(passwordAsCharArray);

	delete[] usernameAsCharArray;
	delete[] passwordAsCharArray;
}

LoginMessage::LoginMessage(const LoginMessage& other): ClientBasicMessage(other)
{
	this->username = other.username;
	this->password = other.password;
}

LoginMessage& LoginMessage::operator=(const LoginMessage& rhs)
{
	if(this != &rhs)
	{
		ClientBasicMessage::operator=(rhs);
		this->username = rhs.username;
		this->password = rhs.password;
	}
	return *this;
}

LoginMessage::~LoginMessage()
{
	username = std::string("");
	password = std::string("");
}

std::string LoginMessage::getUsername()
{
	return username;
}

std::string LoginMessage::getPassword()
{
	return password;
}

