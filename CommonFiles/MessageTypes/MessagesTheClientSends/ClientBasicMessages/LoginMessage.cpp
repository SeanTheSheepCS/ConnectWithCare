#include "LoginMessage.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"
#include <string>

LoginMessage::LoginMessage(ClientBasicMessage clientBasicMessageToTurnIntoALoginMessage) : ClientBasicMessage(clientBasicMessageToTurnIntoALoginMessage)
{
	const unsigned char* pointerToStartOfMessage = &(Message::getMessageAsCharArray()[0]);
	unsigned long int indexOfStartOfData = ClientBasicMessage::getIndexOfFirstData();
	const unsigned char* dataArray = &(pointerToStartOfMessage[indexOfStartOfData]);

	unsigned long int usernameLength = VariableLengthQuantityLibrary::convertVariableLengthQuantityToUnsignedLongInt(&(dataArray[0]));
	short int usernameLengthFieldLength = getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
	long int passwordLength = dataLength - usernameLength - usernameLengthFieldLength;
	char[] usernameAsCharArray = new char[usernameLength];
	char[] passwordAsCharArray = new char[passwordLength];
	indexInTheMessage = ClientBasicMessage::getIndexOfFirstData() + usernameLengthFieldLength;
	for(int i = 0; i < usernameLength-1; i++)
	{
		usernameAsCharArray[i] = dataArray[indexInTheMessage];
		indexInTheMessage++;
	}
	usernameAsCharArray[usernameLength-1] = '\0';
	username = std::string(usernameAsCharArray);
	for(int i = 0; i < passwordLength-1; i++)
	{
		passwordAsCharArray[i] = dataArray[indexInTheMessage];
		indexInTheMessage;
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

LoginMessage::LoginMessage& operator=(const LoginMessage& rhs)
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
	username = string("");
	password = string("");
}

std::string LoginMessage::getUsername()
{
	return username;
}

std::string LoginMessage::getPassword()
{
	return password;
}

