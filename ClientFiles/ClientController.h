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
#include "ClientMessageConverter.h"
#include "ClientMessageCreator.h"
#define BUFFERSIZE 32
#define MAXLINE 32 


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
        GUI app; // Apllication that the client runs
        ClientMessageCreator theCreator; // Creates specific client messages to send over to server
        ClientMessageConverter theConvertor; // Converts messages from server so the client understands

        void createSocket();
        // Helper function for creating the socket.
};

#endif
