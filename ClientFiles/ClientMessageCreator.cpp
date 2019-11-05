#include "ClientMessageCreator.h"
#include "../CommonFiles/Utilities/VariableLengthQuantityLibrary.h"
#include "../CommonFiles/MessageTypes/messagesTheClientSends.h"
#include <iostream>

ClientMessageCreator::ClientMessageCreator()
{
	vlqConverter = VariableLengthQuantityConverter();
}

LoginMessage ClientMessageCreator::createLoginMessage(std::string username, std::string password)
{
	unsigned char messageCode = CLIENTMESSAGECODE_LOGIN;
	unsigned char* arrayRepresentingUsernameLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(username.length());
	unsigned short int usernameLengthLengthInBytes = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	//unsigned long int passwordLengthInBytes = convertUnsignedLongIntToVariableLengthQuantity(password.length());

	unsigned long int dataLengthAsInt = usernameLengthLengthInBytes + username.length() + password.length();
	unsigned char* arrayRepresentingDataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(dataLengthAsInt);
	unsigned short int dataLengthVLQFieldLengthInBytes = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	unsigned long int totalMessageLengthInBytes = 1 /* FOR THE MESSAGE CODE */ + dataLengthVLQFieldLengthInBytes + usernameLengthLengthInBytes + username.length() + password.length();

	unsigned char* messageArray = new unsigned char[totalMessageLengthInBytes];
	int currentIndex = 0;
	messageArray[currentIndex] = messageCode;
	currentIndex++;
	for(int i = 0; i < dataLengthVLQFieldLengthInBytes; i++)
	{
		messageArray[currentIndex] = arrayRepresentingDataLengthInVLQ[i];
		currentIndex++;
	}
	for(unsigned int i = 0; i < usernameLengthLengthInBytes; i++)
	{
		messageArray[currentIndex] = arrayRepresentingUsernameLengthInVLQ[i];
		currentIndex++;
	}
	for(unsigned int i = 0; i < username.length(); i++)
	{
		messageArray[currentIndex] = username[i];
		currentIndex++;
	}
	for(unsigned int i = 0; i < password.length(); i++)
	{
		messageArray[currentIndex] = password[i];
		currentIndex++;
	}

	LoginMessage returnValue = LoginMessage(totalMessageLengthInBytes,messageArray);
	delete[] arrayRepresentingUsernameLengthInVLQ;
	delete[] arrayRepresentingDataLengthInVLQ;
	delete[] messageArray;
	return returnValue;
}

LogoutMessage ClientMessageCreator::createLogoutMessage()
{
	unsigned char messageCode = CLIENTMESSAGECODE_LOGOUT;
	unsigned char dataLengthInVLQ = 0x00; //Logout messages carry no data...
	unsigned char* messageAsCharArray = new unsigned char[2];
	messageAsCharArray[0] = messageCode;
	messageAsCharArray[1] = dataLengthInVLQ;

	LogoutMessage returnValue = LogoutMessage(2,messageAsCharArray);
	delete[] messageAsCharArray;
	return returnValue;
}
