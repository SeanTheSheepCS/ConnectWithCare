#include "MessageCreatorsAndConvertersTest.h"
#include "../Message.h"
#include "../MessageCodes.h"
#include "../AllMessageTypes.h"
#include "../../ClientFiles/ClientMessageConverter.h"
#include "../../ClientFiles/ClientMessageCreator.h"
#include "../../ServerFiles/ServerMessageConverter.h"
#include "../../ServerFiles/ServerMessageCreator.h"
#include <iostream>

int numberOfTestsPassed = 0; // ONLY CHANGE ME THROUGH TESTS PASSED AND TESTS FAILED!!!!
int numberOfTestsAdministered = 0; // ONLY CHANGE ME THROUGH TESTS PASSED AND TESTS FAILED!!!!

int mainMessageUnitTest()
{
	runUnitTestsForMessages();
	return 0;
}

void runUnitTestsForMessages()
{
	std::cout << "--- LOGIN MESSAGE UNIT TEST ---" << std::endl;
	runLoginMessageTest();
	runLoginAuthMessageTest();
	runServerSpecialMessagesTest();
	std::cout << "TESTS PASSED: " << std::dec << numberOfTestsPassed << "/" << std::dec << numberOfTestsAdministered << std::endl;
}

void runLoginMessageTest()
{

	ClientMessageCreator creator = ClientMessageCreator();
	LoginMessage theLoginMessage = creator.createLoginMessage(string("john_doe"), string("passw0rd"));
	std::cout << "	" << "INPUT" << std::endl;
	std::cout << "		" << theLoginMessage.getUsername() << std::endl;
	std::cout << "		" << theLoginMessage.getPassword() << std::endl;
	Message theMessage = theLoginMessage;
	ServerMessageConverter converter;
	if(converter.isLoginMessage(theMessage))
	{
		LoginMessage theLoginMessageConverted = converter.toLoginMessage(theMessage);
		std::cout << "	" << "OUTPUT" << std::endl;
		std::cout << "		" << theLoginMessageConverted.getUsername() << std::endl;
		std::cout << "		" << theLoginMessageConverted.getPassword() << std::endl;
		if(theLoginMessageConverted.getUsername() == "john_doe")
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
		if(theLoginMessageConverted.getPassword() == "passw0rd")
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}

	LoginMessage anotherLoginMessage = creator.createLoginMessage(string("tom"), string("securepassword"));
	std::cout << "	" << "INPUT" << std::endl;
	std::cout << "		" << anotherLoginMessage.getUsername() << std::endl;
	std::cout << "		" << anotherLoginMessage.getPassword() << std::endl;
	Message anotherMessage = anotherLoginMessage;
	if(converter.isLoginMessage(anotherLoginMessage))
	{
		LoginMessage theLoginMessageConverted = converter.toLoginMessage(anotherMessage);
		std::cout << "	" << "OUTPUT" << std::endl;
		std::cout << "		" << theLoginMessageConverted.getUsername() << std::endl;
		std::cout << "		" << theLoginMessageConverted.getPassword() << std::endl;
		if(theLoginMessageConverted.getUsername() == "tom")
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
		if(theLoginMessageConverted.getPassword() == "securepassword")
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
}

void runLoginAuthMessageTest()
{
	ServerMessageCreator creator = ServerMessageCreator();
	LoginAuthMessage theLoginAuthMessage = creator.createLoginAuthMessage(false);
	std::cout << "	" << "INPUT" << std::endl;
	std::cout << "		" << "FALSE" << std::endl;
	Message theMessage = Message(theLoginAuthMessage.getLength(), theLoginAuthMessage.getMessageAsCharArray());
	ClientMessageConverter converter;
	if(converter.isLoginAuthMessage(theMessage))
	{
		LoginAuthMessage theLoginAuthMessageConverted = converter.toLoginAuthMessage(theMessage);
		std::cout << "	" << "OUTPUT" << std::endl;
		if(theLoginAuthMessageConverted.getValidBit() == true)
		{
			std::cout << "		" << "TRUE" << std::endl;
			testFailed();
		}
		else
		{
			std::cout << "		" << "FALSE" << std::endl;
			testPassed();
		}
	}

	LoginAuthMessage anotherLoginAuthMessage = creator.createLoginAuthMessage(true);
	std::cout << "	" << "INPUT" << std::endl;
	std::cout << "		" << "TRUE" << std::endl;
	Message anotherMessage =Message(anotherLoginAuthMessage.getLength(), anotherLoginAuthMessage.getMessageAsCharArray());
	if(converter.isLoginAuthMessage(anotherMessage))
	{
		LoginAuthMessage theLoginAuthMessageConverted = converter.toLoginAuthMessage(anotherMessage);
		std::cout << "	" << "OUTPUT" << std::endl;
		if(theLoginAuthMessageConverted.getValidBit() == true)
		{
			std::cout << "		" << "TRUE" << std::endl;
			testPassed();
		}
		else
		{
			std::cout << "		" << "FALSE" << std::endl;
			testFailed();
		}
	}
}

void runServerSpecialMessagesTest()
{
	ServerMessageCreator creator = ServerMessageCreator();
	ClientMessageConverter converter;

	EndOfDataMessage eodMessage = creator.createEndOfDataMessage();
	Message exampleMessage = Message(eodMessage.getLength(), eodMessage.getMessageAsCharArray());
	if(converter.isEndOfDataMessage(exampleMessage))
	{
		EndOfDataMessage eodMessageAgain = converter.toEndOfDataMessage(exampleMessage);
		if((eodMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ENDOFDATA)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isErrorBoardNotFoundMessage(exampleMessage) || converter.isErrorNoAuthMessage(exampleMessage) || converter.isErrorUserNotFoundMessage(exampleMessage) ||
			converter.isErrorWriteFailedMessage(exampleMessage) || converter.isWriteSuccessfulMessage(exampleMessage))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	ErrorBoardNotFoundMessage ebnfMessage = creator.createErrorBoardNotFoundMessage();
	Message exampleMessageTwo = Message(ebnfMessage.getLength(), ebnfMessage.getMessageAsCharArray());
	if(converter.isErrorBoardNotFoundMessage(exampleMessageTwo))
	{
		ErrorBoardNotFoundMessage ebnfMessageAgain = converter.toErrorBoardNotFoundMessage(exampleMessageTwo);
		if((ebnfMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ERRORBOARDNOTFOUND)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageTwo) || converter.isErrorNoAuthMessage(exampleMessageTwo) || converter.isErrorUserNotFoundMessage(exampleMessageTwo) ||
			converter.isErrorWriteFailedMessage(exampleMessageTwo) || converter.isWriteSuccessfulMessage(exampleMessageTwo))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	ErrorNoAuthMessage enaMessage = creator.createErrorNoAuthMessage();
	Message exampleMessageThree = Message(enaMessage.getLength(), enaMessage.getMessageAsCharArray());
	if(converter.isErrorNoAuthMessage(exampleMessageThree))
	{
		ErrorNoAuthMessage enaMessageAgain = converter.toErrorNoAuthMessage(exampleMessageThree);
		if((enaMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ERRORNOAUTH)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageThree) || converter.isErrorBoardNotFoundMessage(exampleMessageThree) || converter.isErrorUserNotFoundMessage(exampleMessageThree) ||
			converter.isErrorWriteFailedMessage(exampleMessageThree) || converter.isWriteSuccessfulMessage(exampleMessageThree))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	ErrorUserNotFoundMessage eunfMessage = creator.createErrorUserNotFoundMessage();
	Message exampleMessageFour = Message(eunfMessage.getLength(), eunfMessage.getMessageAsCharArray());
	if(converter.isErrorUserNotFoundMessage(exampleMessageFour))
	{
		ErrorUserNotFoundMessage enufMessageAgain = converter.toErrorUserNotFoundMessage(exampleMessageFour);
		if((enufMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ERRORUSERNOTFOUND)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageFour) || converter.isErrorBoardNotFoundMessage(exampleMessageFour) || converter.isErrorNoAuthMessage(exampleMessageFour) ||
			converter.isErrorWriteFailedMessage(exampleMessageFour) || converter.isWriteSuccessfulMessage(exampleMessageFour))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	ErrorWriteFailedMessage ewfMessage = creator.createErrorWriteFailedMessage();
	Message exampleMessageFive = Message(ewfMessage.getLength(), ewfMessage.getMessageAsCharArray());
	if(converter.isErrorWriteFailedMessage(exampleMessageFive))
	{
		ErrorWriteFailedMessage ewfMessageAgain = converter.toErrorWriteFailedMessage(exampleMessageFive);
		if((ewfMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_ERRORWRITEFAILED)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageFive) || converter.isErrorBoardNotFoundMessage(exampleMessageFive) || converter.isErrorNoAuthMessage(exampleMessageFive) ||
			converter.isErrorUserNotFoundMessage(exampleMessageFive) || converter.isWriteSuccessfulMessage(exampleMessageFive))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}

	WriteSuccessfulMessage wsMessage = creator.createWriteSuccessfulMessage();
	Message exampleMessageSix = Message(wsMessage.getLength(), wsMessage.getMessageAsCharArray());
	if(converter.isWriteSuccessfulMessage(exampleMessageSix))
	{
		WriteSuccessfulMessage wsMessageAgain = converter.toWriteSuccessfulMessage(exampleMessageSix);
		if((wsMessageAgain.getMessageAsCharArray())[0] == SERVERMESSAGECODE_WRITESUCCESSFUL)
		{
			testPassed();
		}
		else
		{
			testFailed();
		}
	}
	else
	{
		testFailed();
	}
	if(converter.isEndOfDataMessage(exampleMessageSix) || converter.isErrorBoardNotFoundMessage(exampleMessageSix) || converter.isErrorNoAuthMessage(exampleMessageSix) ||
			converter.isErrorUserNotFoundMessage(exampleMessageSix) || converter.isErrorWriteFailedMessage(exampleMessageSix))
	{
		testFailed();
	}
	else
	{
		testPassed();
	}
}

void testPassed()
{
	numberOfTestsPassed++;
	numberOfTestsAdministered++;
}

void testFailed()
{
	numberOfTestsAdministered++;
}

