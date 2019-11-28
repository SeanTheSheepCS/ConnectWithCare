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

SendUserMessageMessage ClientMessageCreator::createSendUserMessageMessage(UserMessage userMessageToConvertToMessage)
{
	unsigned char messageCode = CLIENTMESSAGECODE_SENDMESSAGE;
	const unsigned short int lengthOfMessageCode = 1;

	const char* usernameOfSenderAsCharArray = userMessageToConvertToMessage.getUsernameOfTheSender().c_str();
	const unsigned short int lengthOfUsernameOfSender = userMessageToConvertToMessage.getUsernameOfTheSender().size();
	const unsigned char* usernameOfSenderLengthFieldAsCharArray = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfUsernameOfSender);
	const unsigned short int lengthOfUsernameOfSenderLengthField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const char* usernameOfRecipientAsCharArray = userMessageToConvertToMessage.getUsernameOfTheRecipient().c_str();
	const unsigned short int lengthOfUsernameOfRecipient = userMessageToConvertToMessage.getUsernameOfTheRecipient().size();
	const unsigned char* usernameOfRecipientLengthFieldAsCharArray = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfUsernameOfRecipient);
	const unsigned short int lengthOfUsernameOfRecipientLengthField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const unsigned char* dateAsCharArray = userMessageToConvertToMessage.getDateCreated().toFiveByteFormat();
	const unsigned short int lengthOfDateAsCharArray = 5;

	const char* messageText = userMessageToConvertToMessage.getMessageText().c_str();
	const unsigned long int lengthOfMessageText = userMessageToConvertToMessage.getMessageText().size();

	unsigned long int dataLengthAsUnsignedLong = lengthOfUsernameOfSenderLengthField + lengthOfUsernameOfSender + lengthOfUsernameOfRecipientLengthField + lengthOfUsernameOfRecipient + lengthOfDateAsCharArray + lengthOfMessageText;
	const unsigned char* dataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(dataLengthAsUnsignedLong);
	const unsigned short int lengthOfDataLengthInVLQField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	unsigned long totalMessageLength = lengthOfMessageCode + lengthOfDataLengthInVLQField + dataLengthAsUnsignedLong;

	unsigned char* messageAsCharArray = new unsigned char[totalMessageLength];
	unsigned long int currentIndexInTheMessage = 0;

	messageAsCharArray[currentIndexInTheMessage] = messageCode;
	currentIndexInTheMessage++;

	for(unsigned int i = 0; i < lengthOfDataLengthInVLQField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = dataLengthInVLQ[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameOfSenderLengthField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameOfSenderLengthFieldAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameOfSender; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameOfSenderAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameOfRecipientLengthField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameOfRecipientLengthFieldAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameOfRecipient; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameOfRecipientAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfDateAsCharArray; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = dateAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfMessageText; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = messageText[i];
		currentIndexInTheMessage++;
	}

	SendUserMessageMessage returnValue = SendUserMessageMessage(totalMessageLength, messageAsCharArray);
	delete[] messageAsCharArray;
	delete[] usernameOfRecipientLengthFieldAsCharArray;
	delete[] usernameOfSenderLengthFieldAsCharArray;
	delete[] dataLengthInVLQ;
	return returnValue;
}

SendUserMessageJPEGImageMessage ClientMessageCreator::createSendUserMessageJPEGImageMessage(UserMessage userMessageToConvertToUserMessageWithAJPEGImage, std::vector<MultimediaComponent> multimediaComponents)
{
	unsigned char messageCode = CLIENTMESSAGECODE_SENDMESSAGEIMG;
	const unsigned short int lengthOfMessageCode = 1;

	const char* usernameOfSenderAsCharArray = userMessageToConvertToUserMessageWithAJPEGImage.getUsernameOfTheSender().c_str();
	const unsigned short int lengthOfUsernameOfSender = userMessageToConvertToUserMessageWithAJPEGImage.getUsernameOfTheSender().size();
	const unsigned char* usernameOfSenderLengthFieldAsCharArray = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfUsernameOfSender);
	const unsigned short int lengthOfUsernameOfSenderLengthField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const char* usernameOfRecipientAsCharArray = userMessageToConvertToUserMessageWithAJPEGImage.getUsernameOfTheRecipient().c_str();
	const unsigned short int lengthOfUsernameOfRecipient = userMessageToConvertToUserMessageWithAJPEGImage.getUsernameOfTheRecipient().size();
	const unsigned char* usernameOfRecipientLengthFieldAsCharArray = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfUsernameOfRecipient);
	const unsigned short int lengthOfUsernameOfRecipientLengthField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	const unsigned char* dateAsCharArray = userMessageToConvertToUserMessageWithAJPEGImage.getDateCreated().toFiveByteFormat();
	const unsigned short int lengthOfDateAsCharArray = 5;

	const char* messageText = userMessageToConvertToUserMessageWithAJPEGImage.getMessageText().c_str();
	const unsigned long int lengthOfMessageText = userMessageToConvertToUserMessageWithAJPEGImage.getMessageText().size();

	unsigned long int lengthOfAllMultimediaComponentDataAddedTogether = 0;
	std::vector<const unsigned char*>* vectorFilledWithEveryMMCComponentAsACharArray = new std::vector<const unsigned char*>;
	std::vector<unsigned long int>* vectorFilledWithTheLengthOfEveryMMCComponentAsCharArray = new std::vector<unsigned long int>;

	//HANDLE MMC STUFF

	unsigned long int numberOfMultimediaComponentsAttachedToMessage = multimediaComponents.size();
	const unsigned char* numberOfMultimediaComponentsAttachedToMessageAsVLQArray = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(numberOfMultimediaComponentsAttachedToMessage);
	unsigned short int lengthOfNumberOfMultimediaComponentsField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
	lengthOfAllMultimediaComponentDataAddedTogether += lengthOfNumberOfMultimediaComponentsField;
	if(numberOfMultimediaComponentsAttachedToMessage != 0)
	{
		for(unsigned int i = 0; i < numberOfMultimediaComponentsAttachedToMessage; i++)
		{
			MultimediaComponent currentMultimediaComponent = multimediaComponents.at(i);

			unsigned long int idOfCurrentComponent = currentMultimediaComponent.getMultimediaComponentID();
			const unsigned char* idOfCurrentComponentInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(idOfCurrentComponent);
			unsigned short int lengthOfIDOfCurrentComponentField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

			std::string filenameOfCurrentComponent = currentMultimediaComponent.getFilename();
			unsigned long int lengthOfFilename = filenameOfCurrentComponent.size();
			const unsigned char* lengthOfFilenameInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(lengthOfFilename);
			unsigned short int lengthOfLengthOfFilenameField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();
			char* filenameAsCharArray = new char[lengthOfFilename+1];
			for(unsigned int i = 0; i < lengthOfFilename; i++)
			{
				filenameAsCharArray[i] = filenameOfCurrentComponent[i];
			}
			filenameAsCharArray[lengthOfFilename] = '\0';

			unsigned long int multimediaComponentAsCharArrayLength = lengthOfIDOfCurrentComponentField + lengthOfLengthOfFilenameField + lengthOfFilename;
			unsigned char* multimediaComponentAsCharArray = new unsigned char[multimediaComponentAsCharArrayLength];
			for(int i = 0; i < lengthOfIDOfCurrentComponentField; i++)
			{
				multimediaComponentAsCharArray[i] = idOfCurrentComponentInVLQ[i];
			}
			for(int i = 0; i < lengthOfLengthOfFilenameField; i++)
			{
				multimediaComponentAsCharArray[i + lengthOfIDOfCurrentComponentField] = lengthOfFilenameInVLQ[i];
			}
			for(unsigned int i = 0; i < lengthOfFilename; i++)
			{
				multimediaComponentAsCharArray[i + lengthOfIDOfCurrentComponentField + lengthOfLengthOfFilenameField] = filenameAsCharArray[i];
			}
			vectorFilledWithEveryMMCComponentAsACharArray->push_back(multimediaComponentAsCharArray);
			vectorFilledWithTheLengthOfEveryMMCComponentAsCharArray->push_back(multimediaComponentAsCharArrayLength);
			lengthOfAllMultimediaComponentDataAddedTogether += multimediaComponentAsCharArrayLength;
			delete[] idOfCurrentComponentInVLQ;
			delete[] lengthOfFilenameInVLQ;
			delete[] filenameAsCharArray;
		}
	}

	// END HANDLE MMC STUFF

	unsigned long int dataLengthAsUnsignedLong = lengthOfUsernameOfSenderLengthField + lengthOfUsernameOfSender + lengthOfUsernameOfRecipientLengthField + lengthOfUsernameOfRecipient + lengthOfDateAsCharArray + lengthOfMessageText + lengthOfAllMultimediaComponentDataAddedTogether;
	const unsigned char* dataLengthInVLQ = vlqConverter.convertUnsignedLongIntToVariableLengthQuantity(dataLengthAsUnsignedLong);
	const unsigned short int lengthOfDataLengthInVLQField = vlqConverter.getArrayLengthFromLastConversionFromUnsignedLongIntToVLQ();

	unsigned long totalMessageLength = lengthOfMessageCode + lengthOfDataLengthInVLQField + dataLengthAsUnsignedLong;

	unsigned char* messageAsCharArray = new unsigned char[totalMessageLength];
	unsigned long int currentIndexInTheMessage = 0;

	messageAsCharArray[currentIndexInTheMessage] = messageCode;
	currentIndexInTheMessage++;

	for(unsigned int i = 0; i < lengthOfDataLengthInVLQField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = dataLengthInVLQ[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameOfSenderLengthField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameOfSenderLengthFieldAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameOfSender; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameOfSenderAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameOfRecipientLengthField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameOfRecipientLengthFieldAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfUsernameOfRecipient; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = usernameOfRecipientAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfDateAsCharArray; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = dateAsCharArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfMessageText; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = messageText[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < lengthOfNumberOfMultimediaComponentsField; i++)
	{
		messageAsCharArray[currentIndexInTheMessage] = numberOfMultimediaComponentsAttachedToMessageAsVLQArray[i];
		currentIndexInTheMessage++;
	}
	for(unsigned int i = 0; i < vectorFilledWithEveryMMCComponentAsACharArray->size(); i++)
	{
		unsigned const char* currentMMCComponentAsCharArray = vectorFilledWithEveryMMCComponentAsACharArray->at(i);
		unsigned long int lengthOfCurrentMMCComponentAsCharArray = vectorFilledWithTheLengthOfEveryMMCComponentAsCharArray->at(i);
		for(unsigned int i = 0; i < lengthOfCurrentMMCComponentAsCharArray; i++)
		{
			messageAsCharArray[currentIndexInTheMessage] = currentMMCComponentAsCharArray[i];
			currentIndexInTheMessage++;
		}
	}

	SendUserMessageJPEGImageMessage returnValue = SendUserMessageJPEGImageMessage(totalMessageLength, messageAsCharArray);
	for(unsigned int i = 0; i < vectorFilledWithEveryMMCComponentAsACharArray->size(); i++)
	{
		delete[] vectorFilledWithEveryMMCComponentAsACharArray->at(i);
	}
	delete vectorFilledWithEveryMMCComponentAsACharArray;
	delete vectorFilledWithTheLengthOfEveryMMCComponentAsCharArray;
	delete[] messageAsCharArray;
	delete[] usernameOfRecipientLengthFieldAsCharArray;
	delete[] usernameOfSenderLengthFieldAsCharArray;
	delete[] dataLengthInVLQ;
	return returnValue;
}
