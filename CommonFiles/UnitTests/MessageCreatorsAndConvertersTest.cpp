#include "MessageCreatorsAndConvertersTest.h"
#include "../Message.h"
#include "../MessageCodes.h"
#include "../AllMessageTypes.h"
#include "../../ClientFiles/ClientMessageConverter.h"
#include "../../ClientFiles/ClientMessageCreator.h"
#include "../../ServerFiles/ServerMessageConverter.h"
#include "../../ServerFiles/ServerMessageCreator.h"

int main()
{
	runLoginMessageTest();
}

void runLoginMessageTest()
{
	ClientMessageCreator creator;
	LoginMessage theLoginMessage = creator.createLoginMessage(string("john_doe"), string("passw0rd"));
	std::cout << theLoginMessage.getUsername() << std::endl;
	std::cout << theLoginMessage.getPassword() << std::endl;
	Message theMessage = theLoginMessage;
	ServerMessageConverter converter;
	if(converter.isALoginMessage(theMessage))
	{
		LoginMessage theLoginMessageConverted = converter.toLoginMessage(theMessage);
		std::cout << theLoginMessageConverted.getUsername() << std::endl;
		std::cout << theLoginMessageConverted.getPassword() << std::endl;
	}
}
