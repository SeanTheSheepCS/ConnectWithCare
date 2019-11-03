#ifndef ERROR_NO_AUTH_MESSAGE_H
#define ERROR_NO_AUTH_MESSAGE_H

#include "../ServerSpecialMessages.h"

class ErrorNoAuthMessage : public ServerSpecialMessage
{
	public:
		ErrorNoAuthMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		ErrorNoAuthMessage(const ErrorNoAuthMessage& other);
		ErrorNoAuthMessage& operator=(const ErrorNoAuthMessage& rhs);
		virtual ~ErrorNoAuthMessage();
	protected:
		//
	private:
		//
};

#endif
