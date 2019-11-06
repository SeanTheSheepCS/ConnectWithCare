#include "BoardHistoryMessage.h"
#include <iostream>

BoardHistoryMessage::BoardHistoryMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ClientRequestMessage(lengthArg, messageAsCharArrayArg)
{
	boardID = Message::vlqConverter.convertVariableLengthQuantityToUnsignedLongInt(&(messageAsCharArrayArg[this->getIndexOfFirstData()]));
}

BoardHistoryMessage::BoardHistoryMessage(const BoardHistoryMessage& other) : ClientRequestMessage(other)
{
	this->boardID = other.boardID;
}

BoardHistoryMessage& BoardHistoryMessage::operator=(const BoardHistoryMessage& rhs)
{
	if(this != &rhs)
	{
		ClientRequestMessage::operator=(rhs);
		this->boardID = rhs.boardID;
	}
	return *this;
}

BoardHistoryMessage::~BoardHistoryMessage()
{
	boardID = 0;
}

unsigned long int BoardHistoryMessage::getBoardID()
{
	return boardID;
}
