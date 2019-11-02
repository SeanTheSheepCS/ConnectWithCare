#ifndef SERVER_BASIC_MESSAGES_H
#define SERVER_BASIC_MESSAGES_H

#include "../../Message.h"

class ServerBasicMessage : public Message
{
	public:
		ServerBasicMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
	    ServerBasicMessage(const ServerBasicMessage& other);
	    virtual ServerBasicMessage& operator=(const ServerBasicMessage& rhs);
	    virtual ~ServerBasicMessage();
	protected:
	    unsigned char getMessageCode();
	    unsigned long int getDataLengthInBytes();
	    unsigned long int getIndexOfFirstData();
	private:
		unsigned char messageCode;
	    unsigned long int dataLengthInBytes;
	    unsigned long int indexOfFirstData;
};

#include "ServerBasicMessages/LoginAuthMessage.h"
#include "ServerBasicMessages/LogoutConfirmMessage.h"

#endif
