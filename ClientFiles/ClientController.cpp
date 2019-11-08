/*
 * ConnectWithCare
 * "ClientController.cpp"
 * 
 * TCP type client.
 * 
 * NOTE:
 * - have to differentiate appropriate members of class and just normal variables.
 * - add notifications to the menu later on for more advanced features
 * - have to check the length of messages sent and receive, could give errors here later on with creating messages.
 * 
 * Last updated by: Daryl
 */
#include "ClientController.h"
#include <iostream>

using namespace std;

ClientController::ClientController(int portNumber, char* serverIP)
{
    app = GUI();
    theCreator = ClientMessageCreator();
    theConvertor = ClientMessageConverter();

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
    /*** PROCESS OF LOGGING IN ***/
    loginCase();

    /*** LOGIN WAS SUCCESSFUL ***/
    accountType = "individual(testing)"; // TODO Remove later
    nameTag = "user(testing)"; // TODO Remove later
    app.buildWelcomeMessage();
    char option;
    
    while(1)
    {
        app.buildMenu(0, 0, 0); // TODO Need to add notifciation numbers later.
        cin >> option;
        switch(option)
        {
            case '1':
                cout << "bb selected" << endl;
                //TODO need to figure out what to pass inside bb
                app.buildBulletinBoard();
                bulletinBoardCase();
                break; 
            case '2':
                cout << "chats selected" << endl;
                app.buildChatsMenu(0,0,0); // TODO add notifications later
                chatsCase();
                break;    
            case '3':
                cout << "my posts selected" << endl;
                app.buildPostsMenu(0 ,0); // TODO add notifications later
                postsCase();
                break;
            case '4':
                cout << "public channel selected, NOT WORKING YET" << endl;
                app.buildPublicChannel();
                break;
            case '5':
                cout << "friends selected" << endl;
                //app.buildFriendList(); // TODO need to figure out what to pass here to display friends.
                break;
            case '6':
                cout << "my account selected" << endl;
                app.buildAccountMenu(username, nameTag, accountType);
                break;
            case 'q':
                userQuit();
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
        cerr << "Error, socket() failed" << endl;
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
        cerr << "Error, setsockopt() failed" << endl;
        exit(1);
    }
    cout << "\tCreated Socket!" << endl;
}

void ClientController::checkSending(int bytes, int msgLength)
{
    if (bytes < 0 || bytes != msgLength)
    {
        cerr << "Error in sending..." << endl;
        exit(1); 
    }
}

void ClientController::checkRecv(int bytes, int msgLength)
{
    if (bytes <= 0 || bytes != msgLength)
    {
        cerr << "Error in receiving (or the connection closed)... " << endl;
        exit(1); 
    }
}

void ClientController::clearBuffer(unsigned char* buffer)
{
    memset(buffer, 0, MAXLINE);
}

void ClientController::userQuit()
{
    cout << "Terminating Program..." << endl;
    close(sock);
    exit(0);
}

void ClientController::bulletinBoardCase()
{
    char bbOption; // Options within Bulletin Board
    cin >> bbOption;

    switch(bbOption)
    {
        case '1':
            cout << "add post selected" << endl;
            break;
        case '2':
            cout << "send message selected" << endl;
            break;
        case 'b':
            cout << "go back selected" << endl;
            /* DO NOTING */
            break;
        case 'q':
            cout << "quit selected" << endl;
            userQuit();
            break;
        default:
            cout << "invalid choice (bb)" << endl;
    }
}

void ClientController::chatsCase()
{
    char chatsOption;
    cin >> chatsOption;
    //TODO figure out how to display different chats by different friends (most recent 5)
    switch(chatsOption)
    {
        case '1':
            cout << "display chat 1" << endl;
            break;
        case '2':
            cout << "display chat 2" << endl;
            break;
        case '3':
            cout << "display chat 3" << endl;
            break;
        case '4':
            cout << "display chat 4" << endl;
            break;
        case '5':
            cout << "display chat 5" << endl;
            break;
        case 'b':
            cout << "go back selected" << endl;
            /* DO  NOTHING */
            break;
        case 'q':
            cout << "quit selected" << endl;
            userQuit();
            break;
        default:
            cout << "invalid choice (chats)" << endl;
    }
}

void ClientController::postsCase()
{
    char postsOption;
    cin >> postsOption;
    // TODO need to figure out how to display most recent posts (recent 5)
    switch(postsOption)
    {
        case '1':
            cout << "post 1" << endl;
            break;
        case '2':
            cout << "post 2" << endl;
            break;
        case '3':
            cout << "post 3" << endl;
            break;
        case '4':
            cout << "post 4" << endl;
            break;
        case '5':
            cout << "post 5" << endl;
            break;
        case 'b':
            cout << "go back selected" << endl;
            /* DO  NOTHING */
            break;
        case 'q':
            cout << "quit selected" << endl;
            userQuit();
            break;
        default:
            cout << "invalid choice (posts)" << endl;
    }
}

void ClientController::publicChannelCase()
{
   // TODO SEND MESSAGE to server (advanced)
}

void ClientController::friendsCase()
{
    char friendsOption;
    cin >> friendsOption;

    switch(friendsOption)
    {
        case '1':
        {
            cout << "add friend selected" << endl;
            string friendUser;
            cout << "Enter friend's username:";
            cin >> friendUser;
            // TODO PASS FRIEND REQUEST TO SERVER
            break;
        }
        case 'b':
        {
            cout << "go back selected" << endl;
            /* DO  NOTHING */
            break;
        }
        case 'q':
        {
            cout << "quit selected" << endl;
            userQuit();
            break;
        }
        default:
            cout << "invalid choice (posts)" << endl;
    }
}

void ClientController::accountCase()
{
    char accountOption;
    cin >> accountOption;
    //TODO finish adding functionalities to the account menu
    switch(accountOption)
    {
        case '1':
            cout << "change username selected" << endl;
            break;
        case '2':
            cout << "change password selected" << endl;
            break;
        case '3':
            cout << "update status" << endl;
            break;
        case '4':
            if(accountType == "charity")
            {
                cout << "change org informaiton selected" << endl;
            }
            else
            {
                cout << "Only available for account types Charity" << endl;
            }
            break;
        case '5':
            cout << "Change account type selected" << endl;
            break;
        case '6':
            cout << "delete account type selected" << endl;
            app.deleteAccountMenu();
            char deleteAccount;
            cin >> deleteAccount;
            if(deleteAccount == 'Y')
            {
                cout << "deleting account" << endl;
                //TODO tell server to delete account
                userQuit();
            }
            else if(deleteAccount == 'b')
            {
                cout << "going back" ;
                break;
            }
            else
            {
                cout << "invalid option, going back anayways" << endl;
                break;
            }
            break;
        case 'b':
            cout << "go back selected" << endl;
            /* DO  NOTHING */
            break;
        case 'q':
            cout << "quit selected" << endl;
            userQuit();
            break;
        default:
            cout << "invalid choice (posts)" << endl;
    }
}

void ClientController::loginCase()
{
    while(1)
    {
        app.buildUsernameField();
        cin >> username;
        app.buildPasswordField();
        cin >> password;
        LoginMessage userAttempt = theCreator.createLoginMessage(username, password); // Turn login properties into proper message

        strcpy((char*)outBuffer, (char*)userAttempt.getMessageAsCharArray()); 
        msgLength = userAttempt.getLength();

        // Send login info to server
        bytesSent = send(sock, (char *) &outBuffer, msgLength, 0);
        checkSending(bytesSent, msgLength); 

        // Receive login info from server
        bytesRecv = recv(sock, (char *) &inBuffer, msgLength, 0); // *** Could spawn error here if the length is not correct
        checkRecv(bytesRecv, msgLength);
        
        Message msgFromServer(strlen((char*)inBuffer), inBuffer);
        if(theConvertor.isLoginAuthMessage(msgFromServer))
        {
            LoginAuthMessage userLogin = theConvertor.toLoginAuthMessage(msgFromServer);
            if(userLogin.getValidBit())
            {
                break;
            }
        }
        else
        {
            cout << "Error" << endl;
        }
        
        // Clears buffer
        clearBuffer(outBuffer);
        clearBuffer(inBuffer);
    }
    // Clear buffer
	clearBuffer(outBuffer);
	clearBuffer(inBuffer);
}

int mainClientController(int argc, char *argv[])
{
    if(argc != 3)
    {
        cout << "Invalid input (<Server IP> <Server Port>)." << endl;
        exit(1); // Exits program, failure.
    }
    ClientController theClient(atoi(argv[2]), argv[1]); // Just an example right now.
    theClient.communicate();
}
