#ifndef BOARD_HISTORY_MESSAGE_H
#define BOARD_HISTORY_MESSAGE_H

#include "../ClientRequestMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"

class BoardHistoryMessage : public ClientRequestMessage
{
	public:
		BoardHistoryMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		BoardHistoryMessage(const BoardHistoryMessage& other);
		virtual BoardHistoryMessage& operator=(const BoardHistoryMessage& rhs);
		virtual ~BoardHistoryMessage();
	protected:
		unsigned long int getBoardID();
	private:
		unsigned long int boardID;
};

#endif
