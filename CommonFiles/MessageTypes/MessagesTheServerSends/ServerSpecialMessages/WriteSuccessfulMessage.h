#ifndef WRITE_SUCCESSFUL_MESSAGE_H
#define WRITE_SUCCESSFUL_MESSAGE_H

#include "../ServerSpecialMessages.h"

class WriteSuccessfulMessage : public ServerSpecialMessage
{
	public:
		WriteSuccessfulMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		WriteSuccessfulMessage(const WriteSuccessfulMessage& other);
		WriteSuccessfulMessage& operator=(const WriteSuccessfulMessage& rhs);
		virtual ~WriteSuccessfulMessage();
	protected:
		//
	private:
		//
};

#endif
