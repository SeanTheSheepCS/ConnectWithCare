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
#include <queue>
#include <vector>

#include "ServerMessageConverter.h"
#include "ServerMessageCreator.h"
#include "ClientConnectionInformation.h"

#include "../ServerModel/LoginDatabaseController.h"
#include "../ServerModel/PostDatabaseController.h"

#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"
#include "../CommonFiles/MessageCodes.h"

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
	void addBulBoDatabase(PostDatabaseController pDB);
private:
	
	int serverSock;
	int port;
	fd_set recvSockSet;
	fd_set tempRecvSockSet;
	int maxDesc;
	bool terminated;
	
	LoginDatabaseController loginDatabase;
	PostDatabaseController postDatabase;

	ServerMessageConverter	 messageConverter;
	ServerMessageCreator	 messageCreator;
	
	void initServer();
	
	void selectIncomingConnection_AddToTempRecvSockSet(fd_set& tempRecvSockSet);
	int  establishConnectionWithClient();
	void addConnectionToReceiveSocketSet(int& sock);
	
	void processIncomingSockets (fd_set);
	Message messageFromDataReceivedFromClient(int clientSock);

	vector<char> receiveData(int sock);
	queue<Message> specifyTypeOfClientMessage(Message msgFromClient);

	queue<Message> putSingleMessageInQueue(Message msg);

	queue<Message> specifyClientMessageAsLoginMessage(Message& msgFromClient);
	queue<Message> specifyClientMessageAsLogoutMessage(Message& msgFromClient);

	queue<Message> clarifyClientMessageAsSendUserMessage(Message& msgFromClient);
	queue<Message> clarifyClientMessageAsSendUserJPEGImageMessage(Message& msgFromClient);
	queue<Message> clarifyClientMessageAsUserMessageHistoryMessage(Message& msgFromClient);
	queue<Message> clarifyClientMessageAsUserMessageHistoryAllMessage(Message& msgFromClient);

	queue<Message> specifyClientMessageAsPostingMessage(Message& msgFromClient);
	queue<Message> specifyClientMessageAsBoardHistoryMessage(Message& msgFromClient);
		queue<Message> putPostingsInQueueAndReturnToClient(vector<Posting> selectedPosts, unsigned long int boardIDTheUserWantsHistoryOf);
	queue<Message> specifyClientMessageAsBoardSearchMessage(Message& msgFromClient);

	void popQueueAndSendDataToClient(int sock, queue<Message> msgQueueToClient);
	void sendData (int sock, Message msgToClient);

	void closeAllConnections();

	void listFiles(string& data);
};

#endif

