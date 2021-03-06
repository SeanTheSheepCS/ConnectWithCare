#include "ServerMessageConverter.h"
#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/UserMessages/UserMessage.h"
#include "../CommonFiles/AllMessageTypes.h"
#include <iostream>
#include "../CommonFiles/Postings/Posting.h"

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

bool ServerMessageConverter::isCreatePostingMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_CREATEPOST)
	{
		return true;
	}
	else
	{
		return false;
	}
}

CreatePostingMessage ServerMessageConverter::toCreatePostingMessage(Message messageToTurnIntoACreatePostingMessage)
{
	unsigned long int messageLength = messageToTurnIntoACreatePostingMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoACreatePostingMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_CREATEPOST)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return CreatePostingMessage(messageLength,messageAsCharArray);
	}
}

bool ServerMessageConverter::isSendUserMessageMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_SENDMESSAGE)
	{
		return true;
	}
	else
	{
		return false;
	}
}

SendUserMessageMessage ServerMessageConverter::toSendUserMessageMessage(Message messageToTurnIntoASendUserMessageMessage)
{
	unsigned long int messageLength = messageToTurnIntoASendUserMessageMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoASendUserMessageMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_SENDMESSAGE)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return SendUserMessageMessage(messageLength,messageAsCharArray);
	}
}

bool ServerMessageConverter::isSendUserMessageJPEGImageMessage(Message messageToDetermineTypeOf)
{
	const unsigned char messageCode = (messageToDetermineTypeOf.getMessageAsCharArray())[0];
	if(messageCode == CLIENTMESSAGECODE_SENDMESSAGEIMG)
	{
		return true;
	}
	else
	{
		return false;
	}
}

SendUserMessageJPEGImageMessage ServerMessageConverter::toSendUserMessageJPEGImageMessage(Message messageToTurnIntoASendUserMessageJPEGImageMessage)
{
	unsigned long int messageLength = messageToTurnIntoASendUserMessageJPEGImageMessage.getLength();
	const unsigned char* messageAsCharArray = messageToTurnIntoASendUserMessageJPEGImageMessage.getMessageAsCharArray();
	if(messageAsCharArray[0] != CLIENTMESSAGECODE_SENDMESSAGEIMG)
	{
		std::cerr << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
	else
	{
		return SendUserMessageJPEGImageMessage(messageLength,messageAsCharArray);
	}
}
