#include "ServerMessageConverter.h"
#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/UserMessage.h"
#include "../CommonFiles/AllMessageTypes.h"
#include <iostream>

ServerMessageConverter::ServerMessageConverter()
{

}

bool ServerMessageConverter::isLoginMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_LOGIN)
	{
		return true;
	}
	else
	{
		return false;
	}
}

LoginMessage ServerMessageConverter::toLoginMessage(Message messageToTurnIntoALoginMessage)
{
	unsigned long int messageLength = messageToTurnIntoALoginMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoALoginMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_LOGIN)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return LoginMessage(messageLength,messageAsCharArray);
	}
}
