#ifndef LOGIN_MESSAGE_H
#define LOGIN_MESSAGE_H

#include <string>
#include "../ClientBasicMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"

class LoginMessage : public ClientBasicMessage
{
	public:
		LoginMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
	    LoginMessage(const LoginMessage& other);
	    LoginMessage& operator=(const LoginMessage& rhs);
	    virtual ~LoginMessage();
		std::string getUsername();
		std::string getPassword();
	protected:
		//
	private:
		VariableLengthQuantityConverter vlqConverter;
		std::string username;
		std::string password;
};

#endif
