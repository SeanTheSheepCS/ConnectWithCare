#ifndef LOGOUT_CONFIRM_MESSAGE_H
#define LOGOUT_CONFIRM_MESSAGE_H

#include "../ServerBasicMessages.h"

class LogoutConfirmMessage : public ServerBasicMessage
{
	public:
		LogoutConfirmMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		LogoutConfirmMessage(const LogoutConfirmMessage& other);
		LogoutConfirmMessage& operator=(const LogoutConfirmMessage& rhs);
	    virtual ~LogoutConfirmMessage();
		bool getSuccessBit();
	protected:
		//
	private:
		bool successBit;
};

#endif
