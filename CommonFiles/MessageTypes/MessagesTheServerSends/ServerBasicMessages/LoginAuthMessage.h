#ifndef LOGIN_AUTH_MESSAGE_H
#define LOGIN_AUTH_MESSAGE_H

#include "../ServerBasicMessages.h"

class LoginAuthMessage : public ServerBasicMessage
{
	public:
		LoginAuthMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
	    LoginAuthMessage(const LoginAuthMessage& other);
	    LoginAuthMessage& operator=(const LoginAuthMessage& rhs);
	    virtual ~LoginAuthMessage();
		bool getValidBit();
	protected:
		//
	private:
		bool validBit;
};

#endif
