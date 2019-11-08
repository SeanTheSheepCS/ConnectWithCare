#include "ClientFiles/ClientController.h"
#include "ServerFiles/ServerController.h"
#include "CommonFiles/UnitTests/MessageCreatorsAndConvertersTest.h"

#define SERVER_MODE

int main(int argc, char** argv)
{
	#ifdef CLIENT_MODE
		return mainClientController(argc,argv);
	#endif
	#ifdef SERVER_MODE
		return mainServerController(argc,argv);
	#endif
	#ifdef UNIT_TEST_MODE
		return mainMessageUnitTest();
	#endif
}
