#ifndef LOGOUT_MESSAGE_H
#define LOGOUT_MESSAGE_H

#include <string>
#include "../ClientBasicMessages.h"

class LogoutMessage : public ClientBasicMessage
{
	public:
		LogoutMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
	    LogoutMessage(const LogoutMessage& other);
	    LogoutMessage& operator=(const LogoutMessage& rhs);
	    virtual ~LogoutMessage();
	protected:
		//
	private:
		//
};

#endif
