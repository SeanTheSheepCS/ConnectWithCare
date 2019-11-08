#ifndef ServerController_h
#define ServerController_h

#include <iostream>             // for listFiles, openFile
#include <fstream>
#include <string>
#include <sys/socket.h> // for socket(), connect(), send(), and recv()
#include <arpa/inet.h>  // for sockaddr_in and inet_addr()
#include <stdlib.h>     // for atoi() and exit()
#include <string.h>     // for memset()
#include <unistd.h>     // for close()

#include "ServerMessageConverter.h"
#include "ServerMessageCreator.h"
#include "ServerMessageHandler.h"

#include "../ServerModel/LoginDatabaseController.h"

#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"

#define BUFFERSIZE 32
#define MAXPENDING 10

using namespace std;

void checkForCommandLineInputErrors(int argc, char *argv[]);
int mainServerController(int argc, char** argv);

class ServerController {
public:
	ServerController(int port);
	
	void communicate();

	void addLoginDatabase(LoginDatabaseController lDB);

private:
	
	int serverSock;
	int port;
	fd_set recvSockSet;
	fd_set tempRecvSockSet;
	int maxDesc;
	bool terminated;
	
	LoginDatabaseController loginDatabase;

	ServerMessageConverter	 messageConverter;
	ServerMessageCreator	 messageCreator;
	
	void initServer();
	
	void selectIncomingConnection_AddToTempRecvSockSet(fd_set& tempRecvSockSet);
	int  establishConnectionWithClient();
	void addConnectionToReceiveSocketSet(int& sock);
	
	void processIncomingSockets (fd_set);
	Message messageFromDataReceivedFromClient(int clientSock);

	string receiveData(int sock);
	Message specifyTypeOfClientMessage(Message& msgFromClient);
	LoginAuthMessage specifyClientMessageAsLoginMessage(Message& msgFromClient);

	void sendData (int sock, Message msgToClient);

	void closeAllConnections();

	void listFiles(string& data);
};

#endif

