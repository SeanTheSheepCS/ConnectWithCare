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

bool ClientMessageConverter::isLogoutConfirmMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_LOGOUTCONFIRM)
	{
		return true;
	}
	else
	{
		return false;
	}
}

LogoutConfirmMessage ClientMessageConverter::toLogoutConfirmMessage(Message messageToTurnIntoALogoutConfirmMessage)
{
	//another quick check to be 100% sure this message is a logoutConfirmMessage...
	const unsigned char* messageAsCharArray = messageToTurnIntoALogoutConfirmMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_LOGOUTCONFIRM)
	{
		return LogoutConfirmMessage(messageToTurnIntoALogoutConfirmMessage.getLength(), messageToTurnIntoALogoutConfirmMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}

bool ClientMessageConverter::isPostingDataMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_POSTINGDATA)
	{
		return true;
	}
	else
	{
		return false;
	}
}

PostingDataMessage ClientMessageConverter::toPostingDataMessage(Message messageToTurnIntoPostingDataMessage)
{
	//another quick check to be 100% sure this message is a postingDataMessage...
	const unsigned char* messageAsCharArray = messageToTurnIntoPostingDataMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_POSTINGDATA)
	{
		return PostingDataMessage(messageToTurnIntoPostingDataMessage.getLength(), messageToTurnIntoPostingDataMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}

bool ClientMessageConverter::isErrorNoAuthMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ERRORNOAUTH)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ErrorNoAuthMessage ClientMessageConverter::toErrorNoAuthMessage(Message messageToTurnIntoAnErrorNoAuthMessage)
{
	//another quick check to be 100% sure this message is an errornoauthmessage...
	const unsigned char* messageAsCharArray = messageToTurnIntoAnErrorNoAuthMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ERRORNOAUTH)
	{
		return ErrorNoAuthMessage(messageToTurnIntoAnErrorNoAuthMessage.getLength(), messageToTurnIntoAnErrorNoAuthMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}

bool ClientMessageConverter::isErrorUserNotFoundMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ERRORUSERNOTFOUND)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ErrorUserNotFoundMessage ClientMessageConverter::toErrorUserNotFoundMessage(Message messageToTurnIntoAUserNotFoundMessage)
{
	//another quick check to be 100% sure this message is an usernotfoundmessage...
	const unsigned char* messageAsCharArray = messageToTurnIntoAUserNotFoundMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ERRORUSERNOTFOUND)
	{
		return ErrorUserNotFoundMessage(messageToTurnIntoAUserNotFoundMessage.getLength(), messageToTurnIntoAUserNotFoundMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}

bool ClientMessageConverter::isErrorBoardNotFoundMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ERRORBOARDNOTFOUND)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ErrorBoardNotFoundMessage ClientMessageConverter::toErrorBoardNotFoundMessage(Message messageToTurnIntoAnErrorBoardNotFoundMessage)
{
	//another quick check to be 100% sure this message is a boardnotfoundmessage...
	const unsigned char* messageAsCharArray = messageToTurnIntoAnErrorBoardNotFoundMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ERRORBOARDNOTFOUND)
	{
		return ErrorBoardNotFoundMessage(messageToTurnIntoAnErrorBoardNotFoundMessage.getLength(), messageToTurnIntoAnErrorBoardNotFoundMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}

bool ClientMessageConverter::isErrorWriteFailedMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ERRORWRITEFAILED)
	{
		return true;
	}
	else
	{
		return false;
	}
}

ErrorWriteFailedMessage ClientMessageConverter::toErrorWriteFailedMessage(Message messageToTurnIntoAnErrorWriteFailedMessage)
{
	//another quick check to be 100% sure this message is an errorwritefailed message...
	const unsigned char* messageAsCharArray = messageToTurnIntoAnErrorWriteFailedMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ERRORWRITEFAILED)
	{
		return ErrorWriteFailedMessage(messageToTurnIntoAnErrorWriteFailedMessage.getLength(), messageToTurnIntoAnErrorWriteFailedMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}

bool ClientMessageConverter::isWriteSuccessfulMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_WRITESUCCESSFUL)
	{
		return true;
	}
	else
	{
		return false;
	}
}

WriteSuccessfulMessage ClientMessageConverter::toWriteSuccessfulMessage(Message messageToTurnIntoAWriteSuccessfulMessage)
{
	//another quick check to be 100% sure this message is a writesuccessful message...
	const unsigned char* messageAsCharArray = messageToTurnIntoAWriteSuccessfulMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_WRITESUCCESSFUL)
	{
		return WriteSuccessfulMessage(messageToTurnIntoAWriteSuccessfulMessage.getLength(), messageToTurnIntoAWriteSuccessfulMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}

bool ClientMessageConverter::isEndOfDataMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ENDOFDATA)
	{
		return true;
	}
	else
	{
		return false;
	}
}

EndOfDataMessage ClientMessageConverter::toEndOfDataMessage(Message messageToTurnIntoAnEndOfDataMessage)
{
	//another quick check to be 100% sure this message is an endofdata message...
	const unsigned char* messageAsCharArray = messageToTurnIntoAnEndOfDataMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_ENDOFDATA)
	{
		return EndOfDataMessage(messageToTurnIntoAnEndOfDataMessage.getLength(), messageToTurnIntoAnEndOfDataMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}

bool ClientMessageConverter::isUserMessageDataMessage(Message messageToDetermineTypeOf)
{
	const unsigned char* messageAsCharArray = messageToDetermineTypeOf.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_MESSAGEDATA)
	{
		return true;
	}
	else
	{
		return false;
	}
}
UserMessageDataMessage ClientMessageConverter::toUserMessageDataMessage(Message messageToTurnIntoAUserMessageDataMessage)
{
	//another quick check to be 100% sure this message is an userMessageDataMessage message...
	const unsigned char* messageAsCharArray = messageToTurnIntoAUserMessageDataMessage.getMessageAsCharArray();
	const unsigned char messageCode = messageAsCharArray[0];
	if(messageCode == SERVERMESSAGECODE_MESSAGEDATA)
	{
		return UserMessageDataMessage(messageToTurnIntoAUserMessageDataMessage.getLength(), messageToTurnIntoAUserMessageDataMessage.getMessageAsCharArray());
	}
	else
	{
		std::cout << "ERROR: MADE ILLEGAL MESSAGE CONVERSION" << std::endl;
		exit(1);
	}
}
