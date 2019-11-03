#ifndef ERROR_WRITE_FAILED_MESSAGE_H
#define ERROR_WRITE_FAILED_MESSAGE_H

#include "../ServerSpecialMessages.h"

class ErrorWriteFailedMessage : public ServerSpecialMessage
{
	public:
		ErrorWriteFailedMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		ErrorWriteFailedMessage(const ErrorWriteFailedMessage& other);
		ErrorWriteFailedMessage& operator=(const ErrorWriteFailedMessage& rhs);
		virtual ~ErrorWriteFailedMessage();
	protected:
		//
	private:
		//
};

#endif
