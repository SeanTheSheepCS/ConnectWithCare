#include "MessageCreatorsAndConvertersTest.h"
#include "../Message.h"
#include "../MessageCodes.h"
#include "../AllMessageTypes.h"
#include "../../ClientFiles/ClientMessageConverter.h"
#include "../../ClientFiles/ClientMessageCreator.h"
#include "../../ServerFiles/ServerMessageConverter.h"
#include "../../ServerFiles/ServerMessageCreator.h"
#include <iostream>

int mainMessageUnitTest()
{
	runUnitTestsForMessages();
	return 0;
}

void runUnitTestsForMessages()
{
	std::cout << "--- LOGIN MESSAGE UNIT TEST ---" << std::endl;
	runLoginMessageTest();
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
	if(converter.isALoginMessage(theMessage))
	{
		LoginMessage theLoginMessageConverted = converter.toLoginMessage(theMessage);
		std::cout << "	" << "OUTPUT" << std::endl;
		std::cout << "		" << theLoginMessageConverted.getUsername() << std::endl;
		std::cout << "		" << theLoginMessageConverted.getPassword() << std::endl;
	}

	LoginMessage anotherLoginMessage = creator.createLoginMessage(string("tom"), string("securepassword"));
	std::cout << "	" << "INPUT" << std::endl;
	std::cout << "		" << anotherLoginMessage.getUsername() << std::endl;
	std::cout << "		" << anotherLoginMessage.getPassword() << std::endl;
	Message anotherMessage = anotherLoginMessage;
	if(converter.isALoginMessage(anotherLoginMessage))
	{
		LoginMessage theLoginMessageConverted = converter.toLoginMessage(anotherMessage);
		std::cout << "	" << "OUTPUT" << std::endl;
		std::cout << "		" << theLoginMessageConverted.getUsername() << std::endl;
		std::cout << "		" << theLoginMessageConverted.getPassword() << std::endl;
	}
}
