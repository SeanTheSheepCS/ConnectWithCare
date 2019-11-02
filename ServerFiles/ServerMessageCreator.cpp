#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Message.h"
#include "ServerMessageCreator.h"
#include <string>

ServerMessageCreator::ServerMessageCreator()
{
	vlqConverter = VariableLengthQuantityConverter();
}

LoginAuthMessage ServerMessageCreator::createLoginAuthMessage(bool whetherTheLoginWasAccepted)
{
	unsigned char messageCode = SERVERMESSAGECODE_LOGINAUTH;
	unsigned char* dataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(1); // The 1 is here since we are only sending one byte.
	unsigned short int dataLengthInVLQLengthInBytes = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	unsigned char validByte;
	if(whetherTheLoginWasAccepted == true)
	{
		validByte = 0x01;
	}
	else
	{
		validByte = 0x00;
	}
	unsigned short int totalMessageLength = 1 /* for message code */ + dataLengthInVLQLengthInBytes + 1 /* for the valid byte */;
	unsigned char* messageAsCharArray = new unsigned char[totalMessageLength];
	unsigned short int currentIndexInMessageCharArray = 0;
	messageAsCharArray[currentIndexInMessageCharArray] = messageCode;
	currentIndexInMessageCharArray++;
	for(int i = 0; i < dataLengthInVLQLengthInBytes; i++)
	{
		messageAsCharArray[currentIndexInMessageCharArray] = dataLengthInVLQ[i];
		currentIndexInMessageCharArray++;
	}
	messageAsCharArray[currentIndexInMessageCharArray] = validByte;
	LoginAuthMessage returnValue = LoginAuthMessage(totalMessageLength,messageAsCharArray);
	delete[] messageAsCharArray;
	return returnValue;
}
