#ifndef BOARD_SEARCH_MESSAGE_H
#define BOARD_SEARCH_MESSAGE_H

#include "../ClientRequestMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"

class BoardSearchMessage : public ClientRequestMessage
{
	public:
	BoardSearchMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
	BoardSearchMessage(const BoardSearchMessage& other);
		virtual BoardSearchMessage& operator=(const BoardSearchMessage& rhs);
		virtual ~BoardSearchMessage();
		unsigned long int getBoardID();
		std::string getSearchKeyword();
	protected:
		//
	private:
		unsigned long int boardID;
		std::string searchKeyword;
};

#endif
