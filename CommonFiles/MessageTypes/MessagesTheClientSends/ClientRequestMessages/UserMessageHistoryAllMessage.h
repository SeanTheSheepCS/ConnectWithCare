#ifndef USER_MESSAGE_HISTORY_ALL_MESSAGE_H
#define USER_MESSAGE_HISTORY_ALL_MESSAGE_H

#include "../ClientRequestMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"
#include <string>

class UserMessageHistoryAllMessage : public ClientRequestMessage
{
	public:
		UserMessageHistoryAllMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		UserMessageHistoryAllMessage(const UserMessageHistoryAllMessage& other);
		virtual UserMessageHistoryAllMessage& operator=(const UserMessageHistoryAllMessage& rhs);
		virtual ~UserMessageHistoryAllMessage();
	protected:
		//
	private:
		//
};

#endif
