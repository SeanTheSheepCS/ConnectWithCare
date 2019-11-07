#ifndef USER_MESSAGE_HISTORY_MESSAGE_H
#define USER_MESSAGE_HISTORY_MESSAGE_H

#include "../ClientRequestMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"
#include <string>

class UserMessageHistoryMessage : public ClientRequestMessage
{
	public:
		UserMessageHistoryMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		UserMessageHistoryMessage(const UserMessageHistoryMessage& other);
		virtual UserMessageHistoryMessage& operator=(const UserMessageHistoryMessage& rhs);
		virtual ~UserMessageHistoryMessage();
		std::string getUsernameToGetHistoryWith();
	protected:
		//
	private:
		std::string usernameToGetHistoryWith;
};

#endif
