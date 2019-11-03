#ifndef ERROR_USER_NOT_FOUND_MESSAGE_H
#define ERROR_USER_NOT_FOUND_MESSAGE_H

#include "../ServerSpecialMessages.h"

class ErrorUserNotFoundMessage : public ServerSpecialMessage
{
	public:
		ErrorUserNotFoundMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		ErrorUserNotFoundMessage(const ErrorUserNotFoundMessage& other);
		ErrorUserNotFoundMessage& operator=(const ErrorUserNotFoundMessage& rhs);
		virtual ~ErrorUserNotFoundMessage();
	protected:
		//
	private:
		//
};

#endif
