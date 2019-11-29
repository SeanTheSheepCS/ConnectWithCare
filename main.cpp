#include "ClientFiles/ClientController.h"
#include "ServerFiles/ServerController.h"
#include "CommonFiles/UnitTests/MessageCreatorsAndConvertersTest.h"
#include <iostream>
#include <string>

#define CLIENT_MODE

int main(int argc, char** argv)
{
	if (argc == 2) {
		return mainServerController(argc,argv);
	}
	else if (argc == 3) {
		return mainClientController(argc,argv);
	}
	else {
		std::cout << "invalid\n";
	}
#ifdef UNIT_TESTS
		return mainMessageUnitTest();
#endif
}
