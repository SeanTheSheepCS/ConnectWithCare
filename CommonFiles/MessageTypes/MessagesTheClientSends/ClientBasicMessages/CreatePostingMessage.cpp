#include "CreatePostingMessage.h"
#include <iostream>

CreatePostingMessage::CreatePostingMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientBasicMessage(lengthArg, messageAsCharArrayArg)
{
	const unsigned char* dataArray = &(messageAsCharArrayArg[this->getIndexOfFirstData()]);
	boardIDThatThePostingBelongsTo = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(dataArray);
	unsigned short int lengthOfBoardIDInVLQ = Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();

	const unsigned char* pointerToStartOfPostingDateCharArrayForm = &(dataArray[lengthOfBoardIDInVLQ]);
	Date postingDate = Date(pointerToStartOfPostingDateCharArrayForm);

	const unsigned char* pointerToTheStartOfTheUsernameLengthInVLQPortionOfThePosting = &(dataArray[lengthOfBoardIDInVLQ + 5]);
	unsigned long int lengthOfUsernameField = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(pointerToTheStartOfTheUsernameLengthInVLQPortionOfThePosting);
	unsigned short int lengthOfUsernameLengthInVLQField = Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();

	char* usernameAsCharArray = new char[lengthOfUsernameField+1];
	const unsigned char* pointerToStartOfUsernameField = &(dataArray[lengthOfBoardIDInVLQ + 5 + lengthOfUsernameLengthInVLQField]);
	for(unsigned int i = 0; i < lengthOfUsernameField; i++)
	{
		usernameAsCharArray[i] = pointerToStartOfUsernameField[i];
	}
	usernameAsCharArray[lengthOfUsernameField] = '\0';
	string usernameWhoCreatedThisPosting = string(usernameAsCharArray);

	const unsigned char* pointerToStartOfPostingTextCharArrayForm = &(dataArray[lengthOfBoardIDInVLQ + 5 + lengthOfUsernameLengthInVLQField + usernameWhoCreatedThisPosting.size()]);
	unsigned long int lengthOfPostingText = (this->getLength()) - lengthOfBoardIDInVLQ - 5 - this->getIndexOfFirstData();
	char* pointerToTextInCStringForm = new char[lengthOfPostingText+1];
	for(unsigned int i = 0; i < lengthOfPostingText; i++)
	{
		pointerToTextInCStringForm[i] = pointerToStartOfPostingTextCharArrayForm[i];
	}
	pointerToTextInCStringForm[lengthOfPostingText] = '\0';
	std::string stringFormOfPostingText = std::string(pointerToTextInCStringForm);
	thePosting = new Posting(stringFormOfPostingText, usernameWhoCreatedThisPosting, postingDate);
}

CreatePostingMessage::CreatePostingMessage(const CreatePostingMessage& other) : ClientBasicMessage(other)
{
	this->boardIDThatThePostingBelongsTo = other.boardIDThatThePostingBelongsTo;
	this->thePosting = new Posting(*(other.thePosting));
}

CreatePostingMessage& CreatePostingMessage::operator=(const CreatePostingMessage& rhs)
{
	if(this != &rhs)
	{
		ClientBasicMessage::operator=(rhs);
		this->boardIDThatThePostingBelongsTo = rhs.boardIDThatThePostingBelongsTo;
		this->thePosting = rhs.thePosting;
	}
	return *this;
}

CreatePostingMessage::~CreatePostingMessage()
{
	boardIDThatThePostingBelongsTo = 0;
	delete thePosting;
}

unsigned long int CreatePostingMessage::getBoardIDThatThePostingBelongsTo()
{
	return boardIDThatThePostingBelongsTo;
}

const Posting CreatePostingMessage::getPosting()
{
	return *thePosting;
}
