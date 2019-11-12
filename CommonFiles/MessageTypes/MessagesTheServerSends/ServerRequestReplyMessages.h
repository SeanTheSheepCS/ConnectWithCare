#ifndef SERVER_REQUEST_REPLY_MESSAGES
#define SERVER_REQUEST_REPLY_MESSAGES

#include "../../Message.h"

class ServerRequestReplyMessage : public Message
{
	public:
		ServerRequestReplyMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		ServerRequestReplyMessage(const ServerRequestReplyMessage& other);
	    virtual ServerRequestReplyMessage& operator=(const ServerRequestReplyMessage& rhs);
	    virtual ~ServerRequestReplyMessage();
	protected:
	    unsigned char getMessageCode();
	    unsigned long int getDataLengthInBytes();
	    unsigned long int getIndexOfFirstData();
	private:
		unsigned char messageCode;
	    unsigned long int dataLengthInBytes;
	    unsigned long int indexOfFirstData;
};

#include "ServerRequestReplyMessages/PostingDataMessage.h"
#include "ServerRequestReplyMessages/PostingImageDataMessage.h"
#include "ServerRequestReplyMessages/UserMessageDataMessage.h"
#include "ServerRequestReplyMessages/UserMessageImageDataMessage.h"

#endif
