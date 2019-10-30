#include "LoginMessage.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"
#include <string>

LoginMessage::LoginMessage(unsigned long int lengthArg, unsigned char* messageAsCharArrayArg) : ClientBasicMessage(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* pointerToStartOfMessage = &(Message::getMessageAsCharArray()[0]);
	unsigned long int indexOfStartOfData = ClientBasicMessage::getIndexOfFirstData();
	const unsigned char* dataArray = &(pointerToStartOfMessage[indexOfStartOfData]);

	unsigned long int usernameLength = VariableLengthQuantityConverter::convertVariableLengthQuantityToUnsignedLongInt(&(dataArray[0]));
	unsigned short int usernameLengthFieldLength = VariableLengthQuantityConverter::getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
	unsigned long int passwordLength = ClientBasicMessage::getDataLengthInBytes() - usernameLength - usernameLengthFieldLength;
	char* usernameAsCharArray = new char[usernameLength];
	char* passwordAsCharArray = new char[passwordLength];
	int indexInTheMessage = ClientBasicMessage::getIndexOfFirstData() + usernameLengthFieldLength;
	for(unsigned int i = 0; i < usernameLength-1; i++)
	{
		usernameAsCharArray[i] = dataArray[indexInTheMessage];
		indexInTheMessage++;
	}
	usernameAsCharArray[usernameLength-1] = '\0';
	username = std::string(usernameAsCharArray);
	for(unsigned int i = 0; i < passwordLength-1; i++)
	{
		passwordAsCharArray[i] = dataArray[indexInTheMessage];
		indexInTheMessage++;
	}
	passwordAsCharArray[passwordLength-1] = '\0';
	password = std::string(passwordAsCharArray);
	delete usernameAsCharArray;
	delete passwordAsCharArray;
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

