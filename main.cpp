#include "ClientFiles/ClientController.h"
#include "ServerFiles/ServerController.h"
#include "CommonFiles/UnitTests/MessageCreatorsAndConvertersTest.h"

//#define CLIENT_MODE

int main(int argc, char** argv)
{
	#ifdef CLIENT_MODE
		return mainClientController(argc,argv);
	#else //SERVER_MODE
		return mainServerController(argc,argv);
	#endif
	#ifdef UNIT_TEST_MODE
		return mainMessageUnitTest();
	#endif
}
