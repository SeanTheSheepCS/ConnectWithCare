#ifndef SERVER_SPECIAL_MESSAGES
#define SERVER_SPECIAL_MESSAGES

#include "../../Message.h"

class ServerSpecialMessage : public Message
{
	public:
		ServerSpecialMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		ServerSpecialMessage(const ServerSpecialMessage& other);
	    virtual ServerSpecialMessage& operator=(const ServerSpecialMessage& rhs);
	    virtual ~ServerSpecialMessage();
	protected:
	    unsigned char getMessageCode();
	private:
		unsigned char messageCode;
};

#include "ServerSpecialMessages/EndOfDataMessage.h"
#include "ServerSpecialMessages/ErrorBoardNotFoundMessage.h"
#include "ServerSpecialMessages/ErrorNoAuthMessage.h"
#include "ServerSpecialMessages/ErrorUserNotFoundMessage.h"
#include "ServerSpecialMessages/ErrorWriteFailedMessage.h"
#include "ServerSpecialMessages/WriteSuccessfulMessage.h"

#endif
