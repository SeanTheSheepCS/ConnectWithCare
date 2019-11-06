/*
 * ConnectWithCare
 * "ClientController.h"
 * 
 * TCP type client.
 * 
 * Last updated by: Daryl
 */


#ifndef CLIENT_CONTROLLER
#define CLIENT_CONTROLLER

//#include "ClientMessageConverter.h" // Using converted to send messages over.
#include <sys/socket.h> // for socket(), connect(), send(), and recv()
#include <arpa/inet.h>  // for sockaddr_in and inet_addr()
#include <stdlib.h>     // for atoi() and exit()
#include <string.h>     // for memset()
#include <unistd.h>     // for close()
#include "../View/GUI.h"
#include "../View/GUI.cpp"
#define BUFFERSIZE 32


class ClientController
{
    public:
        ClientController(int portNumber, char* serverIP);
        // Constructs ClientController.

        void communicate();
        // Communicates functionalities with clients.
        
    private:
        int sock; // Socket descriptor
        struct sockaddr_in serverAddr; // Address of the server
        GUI app;

        //char inBuffer[BUFFERSIZE]; // Buffer for the message from the server
        //int bytesRecv; // Number of bytes received

        //char outBuffer[BUFFERSIZE]; // Buffer for message to the server
        //int msgLength; // Length of the outgoing message
        //int bytesSent; // Number of bytes sent

        void createSocket();
        // Helper function for creating the socket.
};

#endif
