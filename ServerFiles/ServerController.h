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

#define BUFFERSIZE 32
#define MAXPENDING 10

using namespace std;

void checkForCommandLineInputErrors(int argc, char *argv[]);
int mainServerController(int argc, char** argv);

class ServerController {
public:
	ServerController(int port);
	
	void runServer();

private:
	
	int serverSock;
	int port;
	fd_set recvSockSet;
	int maxDesc;
	bool terminated;
	
	//ServerMessageConverter messageConverter;
	//ServerMessageCreator   messageCreator;
	
	void initServer();
	
	void selectIncomingConnection_AddToTempRecvSockSet(fd_set& tempRecvSockSet);
	int  establishConnectionWithClient();
	void addConnectionToReceiveSocketSet(int& sock);
	
	void processSockets (fd_set);
	string receiveData(int sock);

	void configureMessageSend(int sock, string& msgFromClient);
	void sendData (int sock, string outgoingMsg);

	void closeAllClientConnections();

	void listFiles(string& data);
};

#endif

