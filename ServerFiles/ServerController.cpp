#include <iostream>             // for listFiles, openFile
#include <fstream>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "ServerController.h"
#include "ServerMessageConverter.h"
#include "ServerMessageCreator.h"

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
	server.runServer();
	
	return 0;
}

ServerController::ServerController(int port) {
	maxDesc = 0;
	terminated = false;
	this->port = port;
	
	messageConverter = ServerMessageConverter();
	messageHandler   = ServerMessageHandler();
	
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
}

void ServerController::runServer() {
	int clientSock;
	fd_set tempRecvSockSet;
	
	
	// Clear the socket sets
	FD_ZERO(&recvSockSet);
	
	// Add the listening socket to the set
	addConnectionToReceiveSocketSet(serverSock);
	
	// Run the server until a "terminate" command is received)
	while (!terminated) {
		// copy the receive descriptors to the working set
		memcpy(&tempRecvSockSet, &recvSockSet, sizeof(recvSockSet));
		
		selectIncomingConnection_AddToTempRecvSockSet(tempRecvSockSet);
		
		// First, process new connection request, if any.
		if (FD_ISSET(serverSock, &tempRecvSockSet) ) {
			clientSock = establishConnectionWithClient();
			addConnectionToReceiveSocketSet(clientSock);
		}
		else {
			processSockets(tempRecvSockSet);
		}
	}
	
	closeAllClientConnections();
	close(serverSock);
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
	return clientSock;
}
void ServerController::addConnectionToReceiveSocketSet(int& sock) {
	FD_SET(sock, &recvSockSet);
	maxDesc = max(maxDesc, sock);
}

void ServerController::processSockets (fd_set readySocks) {
	Message msgFromClient;
	Message msgToClient;

	//string msgFromClient;
	// Loop through the descriptors and process
	for (int clientSock = 0; clientSock <= maxDesc; clientSock++) {
		if (!FD_ISSET(clientSock, &readySocks))
			continue;
		
		// Receive data from the TCP client
		msgFromClient = messageFromDataReceivedFromClient(clientSock);
		specifyTypeOfClientMessage(msgFromClient);

		msgToClient = messageHandler.handleMessageFromClient();
		///configureMessageSend(clientSock, msgFromClient);
	}
}

string ServerController::receiveData(int clientSock) {
	char inBuffer[BUFFERSIZE];
	string msgBuilder = "";
	int bytesRecv = 0, totalBytesRecv = 0;
	
	do {
		memset(&inBuffer, 0, BUFFERSIZE);
		
		bytesRecv = recv(clientSock, (char *) &inBuffer, BUFFERSIZE, 0);
		totalBytesRecv += bytesRecv;
		
		if (bytesRecv < 0) {
			cout << "tcp recv() failed." << endl;
			FD_CLR(clientSock, &recvSockSet);
	
			// Update the max descriptor
			while (FD_ISSET(maxDesc, &recvSockSet) == false)
				maxDesc -= 1;
		}
		else if (bytesRecv == 0) {
			cout << "tcp connection is closed." << endl;
			FD_CLR(clientSock, &recvSockSet);
			
			// Update the max descriptor
			while (FD_ISSET(maxDesc, &recvSockSet) == false) 
				maxDesc -= 1;
		}
		else if (bytesRecv < BUFFERSIZE) {
			// Finish receive
			bytesRecv = 0;
		}
		msgBuilder += inBuffer;
	} while(bytesRecv > 0);
	
	cout << "tcp Received message size: " << totalBytesRecv << endl;

	cout << "Client: " << msgBuilder;
	
	return msgBuilder;
}

Message ServerController::messageFromDataReceivedFromClient (int clientSock) {
	string msgFromClient = receiveData(clientSock);
	return Message(msgFromClient.size(), msgFromClient.c_str());
}

void ServerController::specifyTypeOfClientMessage(Message& msgFromClient) {
	ServerMessageHandlingStrategy& tempStrategy;
	if (messageConverter.isLoginMessage(msgFromClient) ) {
		msgFromClient = messageConverter.toLoginMessage(msgFromClient);
		messageHandler.setMessage(msgFromClient);
		tempStrategy = new HandleLoginStrategy();
		messageHandler.setStrategy(tempStrategy);
	}
}

void ServerController::configureMessageSend(int sock, string& msgFromClient) {
	string outgoingMsg = "";
	if (strncmp( msgFromClient.c_str(), "logout", 6) == 0) {
		outgoingMsg = "logout complete";
	}
	else if (strncmp( msgFromClient.c_str(), "list", 4) == 0) {
		listFiles( outgoingMsg );
		cout << "server does list" << endl;
	}
	else if (msgFromClient.rfind("echo ", 0) == 0) {
		// echo <message>
		msgFromClient.erase(0,5);
		outgoingMsg = msgFromClient;
		cout << "server does echo" << endl;
	}
	else {
		// Improper command
		outgoingMsg = "Unknown command " + msgFromClient;
	}
	sendData(sock, outgoingMsg);
}

void ServerController::sendData(int sock, string outgoingMsg) {
	int bytesSent = 0;
	
	// Sent the data
	bytesSent = send(sock, outgoingMsg.c_str(), outgoingMsg.size(), 0);
	
	if (bytesSent < 0){
		cout << "tcp error in sending. Bytes sent = " << bytesSent << endl;
		return;
	}
	else {
		cout << "sent " << bytesSent << " of " << outgoingMsg.size() << endl;
	}
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

void ServerController::closeAllClientConnections() {
	for (int sockIndex = 0; sockIndex <= maxDesc; sockIndex++) {
		if (FD_ISSET(sockIndex, &recvSockSet))
			close(sockIndex);
	}
}
