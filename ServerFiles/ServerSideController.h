/*
 * ServerSideController.h
 *
 *  Created on: Nov 8, 2019
 *      Author: QCepl
 */

#ifndef SERVERSIDECONTROLLER_H_
#define SERVERSIDECONTROLLER_H_

#include "ServerController.h"
#include "ServerMessageHandler.h"
#include "../ServerModel/LoginDatabaseController.h"

void checkForCommandLineInputErrors(int argc, char *argv[]);
int mainServerController(int argc, char** argv);

class ServerSideController {
public:
	ServerSideController();

	void manageServer();

	void processIncomingSockets(fd_set readySocks);

	void addServer(ServerController& s);
	void addLoginDatabase(LoginDatabaseController& lDB);
private:
	ServerController& 			server;
	ServerMessageHandler& 		messageHandler;
	LoginDatabaseController& 	loginDatabase;
};

#endif /* SERVERSIDECONTROLLER_H_ */
