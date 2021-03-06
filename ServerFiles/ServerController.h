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
#include <map>
#include <queue>
#include <vector>

#include "ServerMessageConverter.h"
#include "ServerMessageCreator.h"
#include "ClientConnectionInformation.h"

#include "../ServerModel/LoginDatabaseController.h"
#include "../ServerModel/PostDatabaseController.h"
#include "../ServerModel/MessageDatabaseController.h"

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
	void addMessageDatabase(MessageDatabaseController mDB);
private:
	
	int serverSock;
	int port;
	fd_set recvSockSet;
	fd_set tempRecvSockSet;
	int maxDesc;
	bool terminated;
	
	map<string, ClientConnectionInformation> onlineUsers;
	vector<ClientConnectionInformation> activeConnections;

	LoginDatabaseController loginDatabase;
	PostDatabaseController postDatabase;
	MessageDatabaseController messageDatabase;

	ServerMessageConverter	 messageConverter;
	ServerMessageCreator	 messageCreator;
	
	void initServer();
	
	void selectIncomingConnection_AddToTempRecvSockSet(fd_set& tempRecvSockSet);
	int  establishConnectionWithClient();
	void addConnectionToReceiveSocketSet(int sock);
	
	void processIncomingSockets (fd_set);
	Message messageFromDataReceivedFromClient(int clientSock);

	vector<unsigned char> receiveData(int sock);
	queue<Message> specifyTypeOfClientMessage(Message msgFromClient, ClientConnectionInformation& clientInfo);

	queue<Message> putSingleMessageInQueue(Message msg);

	queue<Message> specifyClientMessageAsLoginMessage(Message& msgFromClient);
	queue<Message> specifyClientMessageAsLogoutMessage(Message& msgFromClient);

	queue<Message> clarifyClientMessageAsSendUserMessage(Message& msgFromClient, ClientConnectionInformation& clientInfo);
	queue<Message> clarifyClientMessageAsSendUserJPEGImageMessage(Message& msgFromClient, ClientConnectionInformation& clientInfo);
	queue<Message> clarifyClientMessageAsUserMessageHistoryMessage(Message& msgFromClient, ClientConnectionInformation& clientInfo);
		queue<Message> putUserMessagesInQueueAndReturnToClient(vector<UserMessage>& selectedMsgs);
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

