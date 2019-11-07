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

bool ServerMessageConverter::isLogoutMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_LOGOUT)
	{
		return true;
	}
	else
	{
		return false;
	}
}

LogoutMessage ServerMessageConverter::toLogoutMessage(Message messageToTurnIntoALogoutMessage)
{
	unsigned long int messageLength = messageToTurnIntoALogoutMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoALogoutMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_LOGOUT)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return LogoutMessage(messageLength,messageAsCharArray);
	}
}

bool ServerMessageConverter::isBoardHistoryMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_BOARDHISTORY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

BoardHistoryMessage ServerMessageConverter::toBoardHistoryMessage(Message messageToTurnIntoABoardHistoryMessage)
{
	unsigned long int messageLength = messageToTurnIntoABoardHistoryMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoABoardHistoryMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_BOARDHISTORY)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return BoardHistoryMessage(messageLength,messageAsCharArray);
	}
}

bool ServerMessageConverter::isBoardSearchMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_BOARDSEARCH)
	{
		return true;
	}
	else
	{
		return false;
	}
}

BoardSearchMessage ServerMessageConverter::toBoardSearchMessage(Message messageToTurnIntoABoardSearchMessage)
{
	unsigned long int messageLength = messageToTurnIntoABoardSearchMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoABoardSearchMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_BOARDSEARCH)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return BoardSearchMessage(messageLength,messageAsCharArray);
	}
}

bool ServerMessageConverter::isUserMessageHistoryMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_MESSAGEHISTORY)
	{
		return true;
	}
	else
	{
		return false;
	}
}

UserMessageHistoryMessage ServerMessageConverter::toUserMessageHistoryMessage(Message messageToTurnIntoAUserMessageHistoryMessage)
{
	unsigned long int messageLength = messageToTurnIntoAUserMessageHistoryMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoAUserMessageHistoryMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_MESSAGEHISTORY)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return UserMessageHistoryMessage(messageLength,messageAsCharArray);
	}
}

bool ServerMessageConverter::isUserMessageHistoryAllMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_MESSAGEHISTALL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

UserMessageHistoryAllMessage ServerMessageConverter::toUserMessageHistoryAllMessage(Message messageToTurnIntoAUserMessageHistoryAllMessage)
{
	unsigned long int messageLength = messageToTurnIntoAUserMessageHistoryAllMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoAUserMessageHistoryAllMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_MESSAGEHISTALL)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return UserMessageHistoryAllMessage(messageLength,messageAsCharArray);
	}
}
