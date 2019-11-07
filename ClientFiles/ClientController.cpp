/*
 * ConnectWithCare
 * "ClientController.cpp"
 * 
 * TCP type client.
 * 
 * NOTE:
 * - have to differentiate appropriate members of class and just normal variables.
 * 
 * Last updated by: Daryl
 */
#include "ClientController.h"
#include <iostream>

using namespace std;

ClientController::ClientController(int portNumber, char* serverIP)
{
    app = GUI();

    createSocket();
    cout << "...Attempting to connect to the server..." << endl;
    /* Initialize the server information. Server ports less than 1023 are not allowable unless granted privileges. */ 
    memset(&serverAddr, 0, sizeof(serverAddr)); // Zero out the structure
    serverAddr.sin_family = AF_INET; // Use Internet address family
    serverAddr.sin_port = htons(portNumber); // Server port number
    serverAddr.sin_addr.s_addr = inet_addr(serverIP); // Server IP address

    /* Connect to the server
     * sock: the socket for this connection.
     * serverAddr: the server address.
     * sizeof(*): the size fo the rserver address
     */
    if (connect(sock, (struct sockaddr *) &serverAddr, sizeof(serverAddr)) < 0)
    {
        cout << "connect() failed" << endl;
        exit(1);
    }
    cout << "\tConnected to server!" << endl;
}

void ClientController::communicate()
{
    char inBuffer[BUFFERSIZE]; // Buffer for the message from the server
    int bytesRecv; // Number of bytes received

    char outBuffer[BUFFERSIZE]; // Buffer for message to the server
    int msgLength; // Length of the outgoing message
    int bytesSent; // Number of bytes sent
    
    app.buildWelcomeMessage();
    app.buildMenu(0, 0, 0); // Need to add notifciation numbers later.
    char option;
    
    while(1)
    {
        switch(option)
        {
            case '1':
                cout << "bb selected" << endl;
                break; 
            case '2':
                cout << "chats selected" << endl;
                break;    
            case '3':
                cout << "my posts selected" << endl;
                break;
            case '4':
                cout << "public channel selected" << endl;
                break;
            case '5':
                cout << "friends selected" << endl;
                break;
            case '6':
                cout << "my account selected" << endl;
                break;
            case 'q':
                cout << "terminating program" << endl;
                exit(0);
                break;
        default:
            cout << "Invalid Input, try again." << endl;
    }
    }
}

void ClientController::createSocket()
{
    cout << "...Attempting to create socket..." << endl;
    /* Create a TCP socket
     * AF_INET: using address family "Internet Protocol address"
     * SOCK_STREAM: Provides sequenced, reliable, bidirectional, connection-mode byte streams.
     * IPPROTO_TCP: TCP protocol
     */
    if ((sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0)
    {
        cout << "socket() failed" << endl;
        exit(1);
    }

    /* Free up the port before binding
     * sock: the socket just created
     * SOL_SOCKET: set the protocol level at the socket level
     * SO_REUSEADDR: allow reuse of local addresses
     * &yes: set SO_REUSEADDR on a socket to true (1)
     * sizeof(int): size of the value pointed by "yes"
     */
    int yes = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0)
    {
        cout << "setsockopt() failed" << endl;
        exit(1);
    }
    cout << "\tCreated Socket!" << endl;
}

int main(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "Invalid input (<Server IP> <Server Port>)." << endl;
        exit(1); // Exits program, failure.
    }
    ClientController theClient(atoi(argv[2]), argv[1]); // Just an example right now.
    theClient.communicate();
}
