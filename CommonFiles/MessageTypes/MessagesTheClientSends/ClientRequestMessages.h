#ifndef CLIENT_REQUEST_MESSAGES_H
#define CLIENT_REQUEST_MESSAGES_H

#include "../../Date.h"

#include "../../Message.h"

class ClientRequestMessage : public Message
{
	public:
		ClientRequestMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		ClientRequestMessage(const ClientRequestMessage& other);
		virtual ClientRequestMessage& operator=(const ClientRequestMessage& rhs);
		virtual ~ClientRequestMessage();
	protected:
		unsigned char getMessageCode();
		unsigned long int getDataLengthInBytes();
		unsigned long int getIndexOfFirstData();
		const Date getStartDate();
		const Date getEndDate();
	private:
		unsigned char messageCode;
		unsigned long int dataLengthInBytes;
		unsigned long int indexOfFirstData;
		Date* startDate;
		Date* endDate;
};

#include "ClientRequestMessages/BoardHistoryMessage.h"
#include "ClientRequestMessages/BoardSearchMessage.h"
#include "ClientRequestMessages/UserMessageHistoryAllMessage.h"
#include "ClientRequestMessages/UserMessageHistoryMessage.h"


#endif
