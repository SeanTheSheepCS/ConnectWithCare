/*
 * ServerSideController.cpp
 *
 *  Created on: Nov 8, 2019
 *      Author: QCepl
 */

#include "ServerSideController.h"

#include "ServerController.h"
#include "ServerMessageHandler.h"
#include "../ServerModel/LoginDatabaseController.h"

using namespace std;

void checkForCommandLineInputErrors(int argc, char *argv[]) {
        if (argc != 2) {
        cout << "Usage: " << argv[0] << " <Listening Port>";
        cout << endl;
        exit(1);
    }
}

int mainServerController(int argc, char** argv) {
	checkForCommandLineInputErrors(argc, argv);

	ServerSideController controller;

	ServerController server( atoi(argv[1]) );
	LoginDatabaseController loginController;

	controller.addServer(server);
	controller.addLoginDatabase(loginController);

	controller.manageServer();
	//server.communicate();

	return 0;
}

ServerSideController::ServerSideController() {
	// TODO Auto-generated constructor stub

}

void ServerSideController::manageServer() {
	while (1) {
		server.checkForIncomingSocketConnections();
		if (server.canProcessIncomingSockets)
			processIncomingSockets(server.getTempRecvSocketSet() );
	}
	server.closeAllConnections();
}

void ServerSideController::processIncomingSockets(fd_set readySocks) {

}

void ServerSideController::addServer(ServerController& s) { server = s; }
void ServerSideController::addLoginDatabase(LoginDatabaseController& lDB) { loginDatabase = lDB; }

