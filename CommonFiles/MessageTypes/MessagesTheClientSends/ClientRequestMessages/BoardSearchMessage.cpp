#include "BoardSearchMessage.h"
#include <iostream>
#include <string>

BoardSearchMessage::BoardSearchMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientRequestMessage(lengthArg, messageAsCharArrayArg)
{
	boardID = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(messageAsCharArrayArg[this->getIndexOfFirstData()]));
	unsigned short int lengthInBytesOfVLQValueOfBoardID = Message::vlqConverter.getVariableLengthQuantityByteLengthOfLastConversionFromVLQToUnsignedLongInt();
    unsigned short int indexOfFirstLetterOfKeyword = this->getIndexOfFirstData() + lengthInBytesOfVLQValueOfBoardID;
    char* searchKeywordAsCharArray = new char[1 + this->getLength() - indexOfFirstLetterOfKeyword];
    int indexInCharArray = 0;
    for(unsigned long int i = indexOfFirstLetterOfKeyword; i < this->getLength(); i++)
    {
    	searchKeywordAsCharArray[indexInCharArray] = messageAsCharArrayArg[i];
    	indexInCharArray++;
    }
    searchKeywordAsCharArray[indexInCharArray] = '\0';
    searchKeyword = std::string(searchKeywordAsCharArray);
    delete[] searchKeywordAsCharArray;
}

BoardSearchMessage::BoardSearchMessage(const BoardSearchMessage& other) : ClientRequestMessage(other)
{
	this->boardID = other.boardID;
	this->searchKeyword = std::string(searchKeyword);
}

BoardSearchMessage& BoardSearchMessage::operator=(const BoardSearchMessage& rhs)
{
	if(this != &rhs)
	{
		ClientRequestMessage::operator=(rhs);
		this->boardID = rhs.boardID;
		this->searchKeyword = std::string(searchKeyword);
	}
	return *this;
}

BoardSearchMessage::~BoardSearchMessage()
{
	boardID = 0;
}

unsigned long int BoardSearchMessage::getBoardID()
{
	return boardID;
}

std::string BoardSearchMessage::getSearchKeyword()
{
	return searchKeyword;
}
