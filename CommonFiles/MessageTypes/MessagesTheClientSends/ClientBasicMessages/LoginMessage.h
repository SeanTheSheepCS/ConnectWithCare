#ifndef LOGIN_MESSAGE_H
#define LOGIN_MESSAGE_H

class LoginMessage : public ClientBasicMessage
{
	public:
		LoginMessage(ClientBasicMessage clientBasicMessageToTurnIntoALoginMessage);
	    LoginMessage(const LoginMessage& other);
	    LoginMessage& operator=(const LoginMessage& rhs);
	    virtual ~LoginMessage();
		std::string getUsername();
		std::string getPassword();
	protected:
		//
	private:
		std::string username;
		std::string password;
};

#endif
