#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Message.h"
#include "ServerMessageCreator.h"
#include <string>
#include <iostream>

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

LogoutConfirmMessage ServerMessageCreator::createLogoutConfirmMessage(bool whetherTheLogoutWasSuccessful)
{
	unsigned char messageCode = SERVERMESSAGECODE_LOGOUTCONFIRM;
	unsigned char* dataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(1); // The 1 is here since we are only sending one byte.
	unsigned short int dataLengthInVLQLengthInBytes = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	unsigned char successByte;
	if(whetherTheLogoutWasSuccessful == true)
	{
		successByte = 0x01;
	}
	else
	{
		successByte = 0x00;
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
	messageAsCharArray[currentIndexInMessageCharArray] = successByte;
	LogoutConfirmMessage returnValue = LogoutConfirmMessage(totalMessageLength,messageAsCharArray);
	delete[] messageAsCharArray;
	return returnValue;
}

PostingDataMessage ServerMessageCreator::createPostingDataMessage(Posting postToConvertToMessage, unsigned long int boardIDThatThePostBelongsTo)
{
	unsigned char messageCode = SERVERMESSAGECODE_POSTINGDATA;

	const unsigned char* boardIDSplitIntoBytes = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(boardIDThatThePostBelongsTo);
	const unsigned short int lengthOfBoardIDSplitIntoBytes = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const unsigned char* postingDate = postToConvertToMessage.getDateTimePosted().toFiveByteFormat();
	const unsigned short int lengthOfPostingDate = 5;

	const char* usernameAsCharArray = postToConvertToMessage.getUsernameOfUserWhoCreatedThisPost().c_str();
	const unsigned short int lengthOfUsername = postToConvertToMessage.getUsernameOfUserWhoCreatedThisPost().size();
	const unsigned char* usernameLengthFieldAsCharArray = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfUsername);
	const unsigned short int lengthOfUsernameLengthField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const char* postingTextAsCharArray = postToConvertToMessage.getPostText().c_str();
	const unsigned long int lengthOfPostingText = postToConvertToMessage.getPostText().size();

	unsigned long int dataLengthAsUnsignedLong = lengthOfBoardIDSplitIntoBytes + lengthOfPostingDate + lengthOfUsernameLengthField + lengthOfUsername + lengthOfPostingText;
	const unsigned char* dataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(dataLengthAsUnsignedLong);
	const unsigned short int lengthOfDataLengthInVLQField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const unsigned short int totalDataLengthInBytes = 1 /* MESSAGE CODE */ + lengthOfDataLengthInVLQField + dataLengthAsUnsignedLong;

	unsigned char* messageAsCharArray = new unsigned char[totalDataLengthInBytes];
	int currentIndexInTheMessage = 0;

	messageAsCharArray[currentIndexInTheMessage] = messageCode;
	currentIndexInTheMessage++;
	for(unsigned int i = 0; i < lengthOfDataLengthInVLQField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = dataLengthInVLQ[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfBoardIDSplitIntoBytes; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = boardIDSplitIntoBytes[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfPostingDate; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = postingDate[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameLengthField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameLengthFieldAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsername; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfPostingText; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = postingTextAsCharArray[i];
		currentIndexInTheMessage++;
	}

	PostingDataMessage returnValue = PostingDataMessage(totalDataLengthInBytes, messageAsCharArray);
	delete[] messageAsCharArray;
	delete[] dataLengthInVLQ;
	return returnValue;
}

ErrorNoAuthMessage ServerMessageCreator::createErrorNoAuthMessage()
{
	unsigned char messageCode = SERVERMESSAGECODE_ERRORNOAUTH;
	return ErrorNoAuthMessage(1, &messageCode);
}

ErrorUserNotFoundMessage ServerMessageCreator::createErrorUserNotFoundMessage()
{
	unsigned char messageCode = SERVERMESSAGECODE_ERRORUSERNOTFOUND;
	return ErrorUserNotFoundMessage(1, &messageCode);
}

ErrorBoardNotFoundMessage ServerMessageCreator::createErrorBoardNotFoundMessage()
{
	unsigned char messageCode = SERVERMESSAGECODE_ERRORBOARDNOTFOUND;
	return ErrorBoardNotFoundMessage(1, &messageCode);
}

ErrorWriteFailedMessage ServerMessageCreator::createErrorWriteFailedMessage()
{
	unsigned char messageCode = SERVERMESSAGECODE_ERRORWRITEFAILED;
	return ErrorWriteFailedMessage(1, &messageCode);
}

WriteSuccessfulMessage ServerMessageCreator::createWriteSuccessfulMessage()
{
	unsigned char messageCode = SERVERMESSAGECODE_WRITESUCCESSFUL;
	return WriteSuccessfulMessage(1, &messageCode);
}

EndOfDataMessage ServerMessageCreator::createEndOfDataMessage()
{
	unsigned char messageCode = SERVERMESSAGECODE_ENDOFDATA;
	return EndOfDataMessage(1, &messageCode);
}
