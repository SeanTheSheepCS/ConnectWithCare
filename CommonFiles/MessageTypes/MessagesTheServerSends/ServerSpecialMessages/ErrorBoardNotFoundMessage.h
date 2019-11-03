#ifndef ERROR_BOARD_NOT_FOUND_MESSAGE_H
#define ERROR_BOARD_NOT_FOUND_MESSAGE_H

#include "../ServerSpecialMessages.h"

class ErrorBoardNotFoundMessage : public ServerSpecialMessage
{
	public:
		ErrorBoardNotFoundMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		ErrorBoardNotFoundMessage(const ErrorBoardNotFoundMessage& other);
		ErrorBoardNotFoundMessage& operator=(const ErrorBoardNotFoundMessage& rhs);
		virtual ~ErrorBoardNotFoundMessage();
	protected:
		//
	private:
		//
};

#endif
