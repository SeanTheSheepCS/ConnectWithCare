#include "ClientMessageConverter.h"
#include <iostream>

ClientMessageConverter::ClientMessageConverter()
{

}

bool ClientMessageConverter::isLoginAuthMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_LOGINAUTH)
	{
		return true;
	}
	else
	{
		return false;
	}
}

LoginAuthMessage ClientMessageConverter::toLoginAuthMessage(Message messageToTurnIntoALoginAuthMessage)
{
	//another quick check to be 100% sure this message is a loginAuthMessage...
	const unsigned char* messageAsCharArray = messageToTurnIntoALoginAuthMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_LOGINAUTH)
	{
		return LoginAuthMessage(messageToTurnIntoALoginAuthMessage.getLength(), messageToTurnIntoALoginAuthMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}
