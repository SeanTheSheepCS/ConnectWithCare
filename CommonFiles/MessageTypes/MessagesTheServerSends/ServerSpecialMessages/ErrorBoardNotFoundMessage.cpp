#include "ErrorBoardNotFoundMessage.h"

ErrorBoardNotFoundMessage::ErrorBoardNotFoundMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg) : ServerSpecialMessage(lengthArg, messageAsCharArrayArg)
{

}

ErrorBoardNotFoundMessage::ErrorBoardNotFoundMessage(const ErrorBoardNotFoundMessage& other) : ServerSpecialMessage(other)
{

}

ErrorBoardNotFoundMessage& ErrorBoardNotFoundMessage::operator=(const ErrorBoardNotFoundMessage& rhs)
{
	if(this != &rhs)
	{
		ServerSpecialMessage::operator=(rhs);
	}
	return *this;
}

ErrorBoardNotFoundMessage::~ErrorBoardNotFoundMessage()
{

}
