#include <iostream>
#include <fstream> // for listFiles, openFile
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <queue>

#include "ServerController.h"
#include "ServerMessageConverter.h"



#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"

//#include "../ServerModel/LoginDatabaseController.h"

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

	ServerController server( atoi(argv[1]) );

	LoginDatabaseController logDB;
	PostDatabaseController pDB;
	MessageDatabaseController mDB;

	server.addLoginDatabase(logDB);
	server.addBulBoDatabase(pDB);
	server.addMessageDatabase(mDB);

	server.communicate();

	return 0;
}

ServerController::ServerController(int port) {
	maxDesc = 0;
	this->port = port;
	
	terminated = false;

	activeConnections = vector<ClientConnectionInformation>();
	onlineUsers = map<string, ClientConnectionInformation>();

	messageConverter = ServerMessageConverter();
	messageCreator = ServerMessageCreator();
	
	initServer();
}

void ServerController::initServer() {
    struct sockaddr_in serverAddr;   // address of the server

    // Create a TCP socket
    // * AF_INET: using address family "Internet Protocol address"
    // * SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams.
    // * IPPROTO_TCP: TCP protocol
    if ((serverSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
        cout << "socket() failed" << endl;
        exit(1);
    }

    // Free up the port before binding
    // * sock: the socket just created
    // * SOL_SOCKET: set the protocol level at the socket level
    // * SO_REUSEADDR: allow reuse of local addresses
    // * &yes: set SO_REUSEADDR on a socket to true (1)
    // * sizeof(int): size of the value pointed by "yes"
    int yes = 1;
    if (setsockopt(serverSock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
        cout << "setsockopt() failed" << endl;
        exit(1);
    }

    // Initialize the server information
    // Note that we can't choose a port less than 1023 if we are not privileged users (root)
    memset(&serverAddr, 0, sizeof(serverAddr));         // Zero out the structure
    serverAddr.sin_family = AF_INET;                    // Use Internet address family
    serverAddr.sin_port = htons(port);                  // Server port number
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);     // Any incoming interface

    // Bind to the local address
    if (bind(serverSock, (sockaddr*)&serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "bind() failed" << endl;
        exit(1);
    }

    // Listen for connection requests
    if (listen(serverSock, MAXPENDING) < 0)
    {
        cout << "listen() failed" << endl;
        exit(1);
    }

    // Clear the socket sets
    FD_ZERO(&recvSockSet);

    // Add the listening socket to the set
    addConnectionToReceiveSocketSet(serverSock);
}

void ServerController::addLoginDatabase(LoginDatabaseController lDB) {
	loginDatabase = lDB;
}
void ServerController::addBulBoDatabase(PostDatabaseController pDB) {
	postDatabase = pDB;
}
void ServerController::addMessageDatabase(MessageDatabaseController mDB) {
	messageDatabase = mDB;
}

void ServerController::communicate() {
	int clientSock;
	
	// Run the server until a "terminate" command is received)
	while (!terminated)
	{
		// copy the receive descriptors to the working set
		memcpy(&tempRecvSockSet, &recvSockSet, sizeof(recvSockSet));
		
		selectIncomingConnection_AddToTempRecvSockSet(tempRecvSockSet);
		
		// First, process new connection request, if any.
		if (FD_ISSET(serverSock, &tempRecvSockSet) ) {

			clientSock = establishConnectionWithClient();
			//ClientConnectionInformation CCI =establishConnectionWithClient();
			//activeConnections.push_back( establishConnectionWithClient() );
			//clientSock = CCI.getCurrentClientSocket();
			//addConnectionToReceiveSocketSet(activeConnections[0].getCurrentClientSocket());
			addConnectionToReceiveSocketSet(clientSock);
		}
		else {
			processIncomingSockets(tempRecvSockSet);
		}
	}
	closeAllConnections();
}

void ServerController::selectIncomingConnection_AddToTempRecvSockSet(fd_set& tempRecvSockSet) {
	// Select timeout has to be reset every time before select() is
	// called, since select() may update the timeout parameter to
	// indicate how much time was left.
	struct timeval selectTime = {0, 10};
	int ready = select(maxDesc + 1, &tempRecvSockSet, NULL, NULL, &selectTime);
	if (ready < 0) {
		cout << "select() failed" << endl;
		terminated = true;
	}
}

int ServerController::establishConnectionWithClient() {
    struct sockaddr_in clientAddr;
	unsigned int sizeClientAddr = sizeof(clientAddr);
	int clientSock;
	
	// Establish a connection
	if ((clientSock = accept(serverSock, (struct sockaddr*) &clientAddr, (socklen_t*) &sizeClientAddr)) < 0) {
		cout << "Error in accept()" << endl;
		terminated = true;
	}
	cout << "Accepted a connection from " << inet_ntoa(clientAddr.sin_addr) << ":" << clientAddr.sin_port;
	cout << endl;
	//ClientConnectionInformation clientInfo = ClientConnectionInformation(clientAddr, clientSock);
	return clientSock;
}
void ServerController::addConnectionToReceiveSocketSet(int sock) {
	FD_SET(sock, &recvSockSet);
	maxDesc = max(maxDesc, sock);
}

void ServerController::processIncomingSockets (fd_set readySocks) {
	// Loop through the descriptors and process
	for (int clientSock = 0; clientSock <= maxDesc; clientSock++) {
		if (!FD_ISSET(clientSock, &readySocks))
			continue;
		ClientConnectionInformation clientInfo;
		// Receive data from the TCP client
		Message msgFromClient = messageFromDataReceivedFromClient(clientSock);

		//cout << hex << (messageCreator.createErrorNoAuthMessage().getMessageAsCharArray())[0] << endl;
		queue<Message> msgQueueToClient = specifyTypeOfClientMessage(msgFromClient, clientInfo);
		popQueueAndSendDataToClient(clientSock, msgQueueToClient);
	}
}

vector<unsigned char> ServerController::receiveData(int clientSock) {
	char inBuffer[BUFFERSIZE];
	vector<unsigned char> msgBuilder;
	int bytesRecv = 0, totalBytesRecv = 0;
	bool continueToReceiveMsg = true;
	
	cout << "Server receiving message" << "\n";
	do {
		memset(&inBuffer, 0, BUFFERSIZE);
		
		bytesRecv = recv(clientSock, (char *) &inBuffer, BUFFERSIZE, 0);
		totalBytesRecv += bytesRecv;

		cout << inBuffer << "\n";

		if (bytesRecv < 0) {
			continueToReceiveMsg = false;
			cout << "tcp recv() failed." << endl;
			FD_CLR(clientSock, &recvSockSet);
	
			// Update the max descriptor
			while (FD_ISSET(maxDesc, &recvSockSet) == false)
				maxDesc -= 1;
		}
		else if (bytesRecv == 0) {
			continueToReceiveMsg = false;
			cout << "tcp connection is closed." << endl;
			FD_CLR(clientSock, &recvSockSet);
			
			// Update the max descriptor
			while (FD_ISSET(maxDesc, &recvSockSet) == false) 
				maxDesc -= 1;
		}
		else if (bytesRecv < BUFFERSIZE) {
			// Finish receive
			continueToReceiveMsg = false;
		}
		for (int i = 0; i < bytesRecv; i++) {
			msgBuilder.push_back(inBuffer[i]);
		}
	} while(continueToReceiveMsg);
	
	cout << "tcp Received message size: " << totalBytesRecv << endl;

	//cout << "Client: " << msgBuilder;
	
	return msgBuilder;
}

Message ServerController::messageFromDataReceivedFromClient (int clientSock) {
	vector<unsigned char> msgFromClientVector = receiveData(clientSock);
	cout << "Vector ";
	for (int p = 0; p < msgFromClientVector.size(); p++) {
		cout << msgFromClientVector[p] << "\n";
	}
	cout << "\n";

	unsigned char msgFromClientArray[msgFromClientVector.size()];
	unsigned char* charPointer = msgFromClientArray;
	for (int i = 0; i < msgFromClientVector.size(); i++, charPointer++) {
		*charPointer = msgFromClientVector[i];
	}
	cout << "array " <<msgFromClientArray << "\n";
	return Message(msgFromClientVector.size(), msgFromClientArray );
}

queue<Message> ServerController::specifyTypeOfClientMessage(Message msgFromClient, ClientConnectionInformation& clientInfo) {
	if (messageConverter.isLoginMessage(msgFromClient) ) {
		return specifyClientMessageAsLoginMessage(msgFromClient);
	}
	else if (messageConverter.isLogoutMessage(msgFromClient)) {
		return specifyClientMessageAsLogoutMessage(msgFromClient);
	}
	else if (messageConverter.isSendUserMessageMessage(msgFromClient)) {
		return clarifyClientMessageAsSendUserMessage(msgFromClient, clientInfo);
	}
	else if (messageConverter.isSendUserMessageJPEGImageMessage(msgFromClient)) {
		//SendUserMessageJPEGImageMessage toSendUserMessageJPEGImageMessage(
	}
	else if (messageConverter.isUserMessageHistoryMessage(msgFromClient)) {
		return clarifyClientMessageAsUserMessageHistoryMessage(msgFromClient, clientInfo);//UserMessageHistoryMessage toUserMessageHistoryMessage(
	}
	else if (messageConverter.isUserMessageHistoryAllMessage(msgFromClient)) {
		//UserMessageHistoryAllMessage toUserMessageHistoryAllMessage(
	}
	else if (messageConverter.isCreatePostingMessage(msgFromClient) ) {
		return specifyClientMessageAsPostingMessage(msgFromClient);
	}
	else if (messageConverter.isBoardHistoryMessage(msgFromClient)) {
		return specifyClientMessageAsBoardHistoryMessage(msgFromClient);
	}
	else if (messageConverter.isBoardSearchMessage(msgFromClient)) {
		return specifyClientMessageAsBoardSearchMessage(msgFromClient);
	}
}
queue<Message> ServerController::putSingleMessageInQueue(Message msg) {
	queue<Message> msgToClientInQueue;
	msgToClientInQueue.push(msg);
	return msgToClientInQueue;
}

queue<Message> ServerController::specifyClientMessageAsLoginMessage(Message& msgFromClient) {
	LoginMessage loginMessageFromClient = messageConverter.toLoginMessage(msgFromClient);
	bool validated = loginDatabase.validateUser(loginMessageFromClient.getUsername(), loginMessageFromClient.getPassword());
	if (validated) {
		queue<Message> validatedQueue;
		validatedQueue.push(messageCreator.createLoginAuthMessage(validated));
		string username = loginMessageFromClient.getUsername();
		unsigned char* accountType = loginDatabase.getAccountType( username );
		unsigned long int accounTypeLength = sizeof(accountType)/sizeof(accountType[0]);
		validatedQueue.push(Message(accounTypeLength , accountType));
		return validatedQueue;
	}
	else {
		return putSingleMessageInQueue(messageCreator.createErrorNoAuthMessage() );
		//cout <<hex <<(specifyClientMessageAsLoginMessageFailure().getMessageAsCharArray())[0]<< "\n";
	}
}

queue<Message> ServerController::specifyClientMessageAsLogoutMessage(Message& msgFromClient) {
	LogoutMessage logoutMessageFromClient = messageConverter.toLogoutMessage(msgFromClient);
	bool whetherTheLogoutWasSuccessful = loginDatabase.confirmLogout();

	return putSingleMessageInQueue( messageCreator.createLogoutConfirmMessage(whetherTheLogoutWasSuccessful) );
}
queue<Message> ServerController::clarifyClientMessageAsSendUserMessage(Message& msgFromClient, ClientConnectionInformation& clientInfo) {
	SendUserMessageMessage sendUserMessageMessage = messageConverter.toSendUserMessageMessage(msgFromClient);
}
queue<Message> ServerController::clarifyClientMessageAsSendUserJPEGImageMessage(Message& msgFromClient, ClientConnectionInformation& clientInfo) {
	SendUserMessageJPEGImageMessage sendUserJPEGMessage = messageConverter.toSendUserMessageJPEGImageMessage(msgFromClient);
}
queue<Message> ServerController::clarifyClientMessageAsUserMessageHistoryMessage(Message& msgFromClient, ClientConnectionInformation& clientInfo) {

	vector<UserMessage> selectedMsgs;
	UserMessageHistoryMessage userMessageHistoryMessage = messageConverter.toUserMessageHistoryMessage(msgFromClient);
	unsigned long int specialMessageCode = messageDatabase.getConversationHistoryAndPlaceInVector(userMessageHistoryMessage, clientInfo.getUsername(), selectedMsgs);
	if (specialMessageCode == SERVERMESSAGECODE_ERRORUSERNOTFOUND) {
		return putSingleMessageInQueue( messageCreator.createErrorUserNotFoundMessage() );
	}
	else {
		cout << "successful getHistory"<< "\n";
		return putUserMessagesInQueueAndReturnToClient(selectedMsgs);
	}
}
queue<Message> ServerController::putUserMessagesInQueueAndReturnToClient(vector<UserMessage>& selectedMsgs) {
	queue<Message> msgToClientInQueue;
	for (int p = 0; p < selectedMsgs.size(); p++) {
		msgToClientInQueue.push( messageCreator.createUserMessageDataMessage( selectedMsgs[p] ) );
	}
	msgToClientInQueue.push( messageCreator.createEndOfDataMessage() );
	//msgToClientInQueue.push( messageCreator.createEndOfDataMessage() );
	return msgToClientInQueue;
}
queue<Message> ServerController::clarifyClientMessageAsUserMessageHistoryAllMessage(Message& msgFromClient) {
	UserMessageHistoryAllMessage userMessageHistoryAllMessage = messageConverter.toUserMessageHistoryAllMessage(msgFromClient);
	return putSingleMessageInQueue(userMessageHistoryAllMessage);
}
queue<Message> ServerController::specifyClientMessageAsPostingMessage(Message& msgFromClient) {
	CreatePostingMessage postingMsgFromClient = messageConverter.toCreatePostingMessage(msgFromClient);
	unsigned long int specialMessageCode = postDatabase.addNewPostAndReturnSpecialMessageCode(postingMsgFromClient);
	if (specialMessageCode == SERVERMESSAGECODE_ERRORBOARDNOTFOUND) {
		return putSingleMessageInQueue( messageCreator.createErrorBoardNotFoundMessage() );
	}
	else if (specialMessageCode == SERVERMESSAGECODE_WRITESUCCESSFUL) {
		return putSingleMessageInQueue( messageCreator.createWriteSuccessfulMessage() );
	}
	else {
		return putSingleMessageInQueue( messageCreator.createErrorWriteFailedMessage() );
	}
}
queue<Message> ServerController::specifyClientMessageAsBoardSearchMessage(Message& msgFromClient) {
	vector<Posting> selectedPosts;
	cout << "board search method" << "\n";
	BoardSearchMessage boardSearchMessage = messageConverter.toBoardSearchMessage(msgFromClient);
	unsigned long int specialMessageCode = postDatabase.searchBoardAndPlaceResultsInVector(boardSearchMessage, boardSearchMessage.getSearchKeyword(), selectedPosts);
	cout << "Looking for " << boardSearchMessage.getSearchKeyword() << " in " << boardSearchMessage.getBoardID() << "\n";
	if (specialMessageCode == SERVERMESSAGECODE_ERRORBOARDNOTFOUND) {
		cout << "boardNotFound" << "\n";
		return putSingleMessageInQueue( messageCreator.createErrorBoardNotFoundMessage() );
	}
	else {
		cout << "BoardSearch" << "\n";
		unsigned long int boardIDTheUserWantsSearchedPostsFrom = boardSearchMessage.getBoardID();
		return putPostingsInQueueAndReturnToClient(selectedPosts, boardIDTheUserWantsSearchedPostsFrom);
	}
}
queue<Message> ServerController::specifyClientMessageAsBoardHistoryMessage(Message& msgFromClient) {
	vector<Posting> selectedPosts;
	BoardHistoryMessage boardHistoryMessage = messageConverter.toBoardHistoryMessage( msgFromClient);
	cout << "In specifyClientMessageAsBoardHistory, desired board id= " << boardHistoryMessage.getBoardID() << "\n";
	unsigned long int specialMessageCode = postDatabase.getBoardHistoryAndPlaceInVector(boardHistoryMessage, selectedPosts);
	if (specialMessageCode == SERVERMESSAGECODE_ERRORBOARDNOTFOUND) {
		return putSingleMessageInQueue( messageCreator.createErrorBoardNotFoundMessage() );
	}
	else {
		cout << "successful getHistory"<< "\n";
		unsigned long int boardIDTheUserWantsHistoryOf = boardHistoryMessage.getBoardID();
		return putPostingsInQueueAndReturnToClient(selectedPosts, boardIDTheUserWantsHistoryOf);
	}
}


queue<Message> ServerController::putPostingsInQueueAndReturnToClient(vector<Posting> selectedPosts, unsigned long int boardIDTheUserWantsHistoryOf) {
	queue<Message> msgToClientInQueue;
	for (int p = selectedPosts.size() - 1; p >= 0; p--) {
		msgToClientInQueue.push( messageCreator.createPostingDataMessage(selectedPosts[p], boardIDTheUserWantsHistoryOf) );
	}
	msgToClientInQueue.push( messageCreator.createEndOfDataMessage() );
	//msgToClientInQueue.push( messageCreator.createEndOfDataMessage() );
	return msgToClientInQueue;
}








void waitBeforeSendingLastMessage(queue<Message>& msgQueueToClient) {
	long int loopsToWait = 100000;
	long int waitingArray[10];
	cout << "bisy" << "\n";
	for (long int i = 0L, z = 0L; i < loopsToWait; i++)
	{
		waitingArray[z] = i;
		z = (z+1)%10;
		cout << "";
	}
	cout << "\n";
}

void ServerController::popQueueAndSendDataToClient(int sock, queue<Message> msgQueueToClient) {
	cout << "-----------------------------sending data ------------------\n";
	while (msgQueueToClient.empty() == false) {
		sendData(sock, msgQueueToClient.front());
		waitBeforeSendingLastMessage(msgQueueToClient);
		msgQueueToClient.pop();
	}
	cout << "-----------------------------end sending data ------------------\n\n";
}
void ServerController::sendData(int sock, Message msgToClient) {
	int bytesSent = 0;

	msgToClient.printMessageToStdOut();
	const unsigned char* outGoingMsg = msgToClient.getMessageAsCharArray();

	cout << "outgoingmsg" << "\n";
	// Sent the data
	bytesSent = send(sock, outGoingMsg, msgToClient.getLength(), 0);
	
	if (bytesSent < 0){
		cout << "tcp error in sending. Bytes sent = " << bytesSent << endl;
		FD_CLR(sock, &recvSockSet);

		// Update the max descriptor
		while (FD_ISSET(maxDesc, &recvSockSet) == false)
			maxDesc -= 1;

		return;
	}
	else {
		cout << "sent " << bytesSent << " of " << msgToClient.getLength() << endl;
	}
	cout << "endOfSend" << "\n";

}

void ServerController::listFiles(string& data) {
	// Execute the "ls" command and save the output to /tmp/temp.txt.
    // /tmp is a special directory storing temporate files in Linux.
    system("ls > /tmp/temp.txt");

    // Open the file
    ifstream infile;
    infile.open("/tmp/temp.txt");

    // Store the file content into a string
    string line;
    //string data = "";
    while (getline(infile, line))
    {
        data += line + "\n";
    }

    // Close the file
    infile.close();

    //cout << data;
}

void ServerController::closeAllConnections() {
	for (int sockIndex = 0; sockIndex <= maxDesc; sockIndex++) {
		if (FD_ISSET(sockIndex, &recvSockSet))
			close(sockIndex);
	}
	close(serverSock);
}
