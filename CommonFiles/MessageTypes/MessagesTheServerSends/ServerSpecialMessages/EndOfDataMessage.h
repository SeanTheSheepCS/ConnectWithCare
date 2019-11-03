#ifndef END_OF_DATA_MESSAGE_H
#define END_OF_DATA_MESSAGE_H

#include "../ServerSpecialMessages.h"

class EndOfDataMessage : public ServerSpecialMessage
{
	public:
		EndOfDataMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		EndOfDataMessage(const EndOfDataMessage& other);
		EndOfDataMessage& operator=(const EndOfDataMessage& rhs);
		virtual ~EndOfDataMessage();
	protected:
		//
	private:
		//
};

#endif
