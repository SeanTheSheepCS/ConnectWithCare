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

BoardHistoryMessage ClientMessageCreator::createBoardHistoryMessage(Date startDate, Date endDate, unsigned long int boardID)
{
	unsigned char messageCode = CLIENTMESSAGECODE_BOARDHISTORY;
	const unsigned char* startDateInFiveByteRepresentation = startDate.toFiveByteFormat();
	const unsigned char* endDateInFiveByteRepresentation = endDate.toFiveByteFormat();
	const unsigned char* boardIDSplitIntoBytes = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(boardID);
	const unsigned short int lengthOfBoardIDSplitIntoBytes = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	const unsigned char* dataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfBoardIDSplitIntoBytes);
	const unsigned short int lengthOfDataLengthInVLQField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	const unsigned short int totalDataLengthInBytes = 1 /* MESSAGE CODE */ + 5 /* START DATE */ + 5 /* END DATE */ + lengthOfDataLengthInVLQField + lengthOfBoardIDSplitIntoBytes;

	unsigned char* messageAsCharArray = new unsigned char[totalDataLengthInBytes];
	int currentIndexInTheMessage = 0;

	messageAsCharArray[currentIndexInTheMessage] = messageCode;
	currentIndexInTheMessage++;
	for(int i = 0; i < 5; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = startDateInFiveByteRepresentation[i];
		currentIndexInTheMessage++;
	}
	for(int i = 0; i < 5; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = endDateInFiveByteRepresentation[i];
		currentIndexInTheMessage++;
	}
	for(int i = 0; i < lengthOfDataLengthInVLQField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = dataLengthInVLQ[i];
		currentIndexInTheMessage++;
	}
	for(int i = 0; i < lengthOfBoardIDSplitIntoBytes; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = boardIDSplitIntoBytes[i];
		currentIndexInTheMessage++;
	}

	BoardHistoryMessage returnValue = BoardHistoryMessage(totalDataLengthInBytes, messageAsCharArray);
	delete[] messageAsCharArray;
	return returnValue;
}

BoardSearchMessage ClientMessageCreator::createBoardSearchMessage(Date startDate, Date endDate, long int boardID, std::string searchKeyword)
{
	unsigned char messageCode = CLIENTMESSAGECODE_BOARDSEARCH;
	const unsigned char* startDateInFiveByteRepresentation = startDate.toFiveByteFormat();
	const unsigned char* endDateInFiveByteRepresentation = endDate.toFiveByteFormat();
	const unsigned char* boardIDSplitIntoBytes = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(boardID);
	const unsigned short int lengthOfBoardIDSplitIntoBytes = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	const unsigned char* dataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfBoardIDSplitIntoBytes);
	const unsigned short int lengthOfDataLengthInVLQField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	char* searchKeywordAsCharArray = new char[searchKeyword.size()];
	for(unsigned short int i = 0; i < searchKeyword.size(); i++)
	{
		searchKeywordAsCharArray[i] = searchKeyword[i];
	}
	const unsigned short int totalDataLengthInBytes = 1 /* MESSAGE CODE */ + 5 /* START DATE */ + 5 /* END DATE */ + lengthOfDataLengthInVLQField + lengthOfBoardIDSplitIntoBytes + searchKeyword.size();

	unsigned char* messageAsCharArray = new unsigned char[totalDataLengthInBytes];
	int currentIndexInTheMessage = 0;

	messageAsCharArray[currentIndexInTheMessage] = messageCode;
	currentIndexInTheMessage++;
	for(int i = 0; i < 5; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = startDateInFiveByteRepresentation[i];
		currentIndexInTheMessage++;
	}
	for(int i = 0; i < 5; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = endDateInFiveByteRepresentation[i];
		currentIndexInTheMessage++;
	}
	for(int i = 0; i < lengthOfDataLengthInVLQField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = dataLengthInVLQ[i];
		currentIndexInTheMessage++;
	}
	for(int i = 0; i < lengthOfBoardIDSplitIntoBytes; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = boardIDSplitIntoBytes[i];
		currentIndexInTheMessage++;
	}
	for(unsigned short int i = 0; i < searchKeyword.size(); i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = searchKeywordAsCharArray[i];
		currentIndexInTheMessage++;
	}

	BoardSearchMessage returnValue = BoardSearchMessage(totalDataLengthInBytes, messageAsCharArray);
	delete[] messageAsCharArray;
	return returnValue;
}

UserMessageHistoryMessage ClientMessageCreator::createUserMessageHistoryMessage(Date startDate, Date endDate, std::string usernameWhoseHistoryWithYouYouWantToGet)
{
	unsigned char messageCode = CLIENTMESSAGECODE_MESSAGEHISTORY;
	const unsigned char* startDateInFiveByteRepresentation = startDate.toFiveByteFormat();
	const unsigned char* endDateInFiveByteRepresentation = endDate.toFiveByteFormat();

	unsigned long int lengthOfUsernameAsCharArray = usernameWhoseHistoryWithYouYouWantToGet.size();
	const char* usernameAsCharArray = usernameWhoseHistoryWithYouYouWantToGet.c_str();

	const unsigned char* dataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfUsernameAsCharArray);
	const unsigned short int lengthOfDataLengthInVLQField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const unsigned short int totalDataLengthInBytes = 1 /* MESSAGE CODE */ + 5 /* START DATE */ + 5 /* END DATE */ + lengthOfDataLengthInVLQField + lengthOfUsernameAsCharArray;

	unsigned char* messageAsCharArray = new unsigned char[totalDataLengthInBytes];
	int currentIndexInTheMessage = 0;

	messageAsCharArray[currentIndexInTheMessage] = messageCode;
	currentIndexInTheMessage++;
	for(unsigned int i = 0; i < 5; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = startDateInFiveByteRepresentation[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < 5; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = endDateInFiveByteRepresentation[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfDataLengthInVLQField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = dataLengthInVLQ[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameAsCharArray; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameAsCharArray[i];
		currentIndexInTheMessage++;
	}

	UserMessageHistoryMessage returnValue = UserMessageHistoryMessage(totalDataLengthInBytes, messageAsCharArray);
	delete[] messageAsCharArray;
	return returnValue;
}

UserMessageHistoryAllMessage ClientMessageCreator::createUserMessageHistoryAllMessage(Date startDate, Date endDate)
{
	unsigned char messageCode = CLIENTMESSAGECODE_MESSAGEHISTALL;
	const unsigned char* startDateInFiveByteRepresentation = startDate.toFiveByteFormat();
	const unsigned char* endDateInFiveByteRepresentation = endDate.toFiveByteFormat();

	const unsigned char dataLengthInVLQ = 0x00;
	const unsigned short int lengthOfDataLengthInVLQField = 1;

	const unsigned short int totalDataLengthInBytes = 1 /* MESSAGE CODE */ + 5 /* START DATE */ + 5 /* END DATE */ + lengthOfDataLengthInVLQField;

	unsigned char* messageAsCharArray = new unsigned char[totalDataLengthInBytes];
	int currentIndexInTheMessage = 0;

	messageAsCharArray[currentIndexInTheMessage] = messageCode;
	currentIndexInTheMessage++;
	for(unsigned int i = 0; i < 5; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = startDateInFiveByteRepresentation[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < 5; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = endDateInFiveByteRepresentation[i];
		currentIndexInTheMessage++;
	}

	messageAsCharArray[currentIndexInTheMessage] = dataLengthInVLQ;
	currentIndexInTheMessage++;

	UserMessageHistoryAllMessage returnValue = UserMessageHistoryAllMessage(totalDataLengthInBytes, messageAsCharArray);
	delete[] messageAsCharArray;
	return returnValue;
}

CreatePostingMessage ClientMessageCreator::createCreatePostingMessage(unsigned long int boardIDToPostTo, Posting postToConvertToMessage)
{
	unsigned char messageCode = CLIENTMESSAGECODE_CREATEPOST;
	const unsigned char* boardIDSplitIntoBytes = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(boardIDToPostTo);
	const unsigned short int lengthOfBoardIDSplitIntoBytes = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const unsigned char* postingDate = postToConvertToMessage.getDateTimePosted().toFiveByteFormat();
	const unsigned short int lengthOfPostingDate = 5;

	const char* usernameAsCharArray = postToConvertToMessage.getUsernameOfUserWhoCreatedThisPost().c_str();
	const unsigned short int lengthOfUsername = postToConvertToMessage.getUsernameOfUserWhoCreatedThisPost().size();
	const unsigned char* usernameLengthFieldAsCharArray = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfUsername);
	const unsigned short int lengthOfUsernameLengthField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const char* postingTextAsCharArray = postToConvertToMessage.getPostText().c_str();
	const unsigned long int lengthOfPostingText = postToConvertToMessage.getPostText().size();

	unsigned long int dataLengthAsUnsignedLong = lengthOfBoardIDSplitIntoBytes + lengthOfUsernameLengthField + lengthOfUsername + lengthOfPostingDate + lengthOfPostingText;
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

	CreatePostingMessage returnValue = CreatePostingMessage(totalDataLengthInBytes, messageAsCharArray);
	delete[] messageAsCharArray;
	delete[] dataLengthInVLQ;
	return returnValue;
}
