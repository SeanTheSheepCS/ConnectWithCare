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
     * sizeof(*): the size of the server address
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
    accountType = "individual(testing)"; // TODO Remove later, get information from server
    nameTag = "user(testing)"; // TODO Remove later, get information from server

    app.buildWelcomeMessage();
    char option;

    Date startDate = Date(2018, 11, 27, 40000); // todo hard-coded start and end dates, might want to make this userfriendly and selectable
    Date endDate = Date(2020, 11 , 27, 40000);

    while(1)
    {
        app.buildMenu(0, 0, 0); // TODO Need to add notifciation numbers later.
        cin >> option;
        switch(option)
        {
            case '1':
            {
                cout << "\tBulletin board selected..." << endl;

                BoardHistoryMessage theBoard = theCreator.createBoardHistoryMessage(startDate, endDate, BOARD_ID);
                // Send board createBoardHistoryMessage to server.
                sendMessageToServer(theBoard);

				// Receive message from server.
                vector<PostingDataMessage> bulletinBoardPosts; // Create bulletin board posts. (passing this to GUI)

                Message post (recvMessageFromServer());
                //post.printMessageToStdOut();
                //PostingDataMessage post2 = theConvertor.toPostingDataMessage(post);
                //string post3 = post2.getPosting().getPostText();
                //cout << post3 << endl;
/*
                Message post1 (recvMessageFromServer());
                post1.printMessageToStdOut();
                post2 = theConvertor.toPostingDataMessage(post1);
                post3 = post2.getPosting().getPostText();
                cout << post3 << endl;

                Message POST1 (recvMessageFromServer());
                //post = Message(recvMessageFromServer());
                POST1.printMessageToStdOut();
				post2 = theConvertor.toPostingDataMessage(POST1);
				post3 = post2.getPosting().getPostText();
				cout << post3 << endl;

				Message POST2 (recvMessageFromServer());
				//post = Message(recvMessageFromServer());
				POST2.printMessageToStdOut();
				post2 = theConvertor.toPostingDataMessage(POST2);
				post3 = post2.getPosting().getPostText();
				cout << post3 << endl;
*/

                if(theConvertor.isErrorBoardNotFoundMessage(post))
                {
                	cout << "\tError with receiving the bulletin board." << endl;
                	break;
                }
				while(!theConvertor.isEndOfDataMessage(post))
				{
					if(!theConvertor.isPostingDataMessage(post))
					{
						cout << "\tError has occured when receiving posts from bulletin board.\n";
						exit(1);
					}
					bulletinBoardPosts.push_back(theConvertor.toPostingDataMessage(post));
					Message post = Message(recvMessageFromServer());
					//post.printMessageToStdOut();
				}

                /*
                while(!theConvertor.isEndOfDataMessage(post))
                {
                	post.printMessageToStdOut();
                	cout << "TEST" << endl;
                	if(!theConvertor.isPostingDataMessage(post))
					{
						cout << "\tError has occured when receiving posts from bulletin board.\n";
						exit(1);
					}
					bulletinBoardPosts.push_back(theConvertor.toPostingDataMessage(post));
					post = PostingDateMessage(recvMessageFromServer()); // Keep checking from server.
                }*/
                //cout << "TEST1" << endl;
                vector<string> bulletinBoardPostsString;
                for(unsigned int i = 0; i < bulletinBoardPosts.size(); i++)
                {
                	cout << "TEST2" << endl;
                	bulletinBoardPostsString.push_back(bulletinBoardPosts[i].getPosting().getPostText()); // Convert the posts to char array.
                }

                app.buildBulletinBoard(bulletinBoardPostsString);
                bulletinBoardCase();
                break; 
            }
            case '2':
            {
                cout << "chats selected" << endl;
                app.buildChatsMenu(0,0,0); // TODO add notifications later
                chatsCase();
                break;    
            }
            case '3':
            {
                cout << "my posts selected" << endl;
                app.buildPostsMenu(0 ,0); // TODO add notifications later
                postsCase();
                break;
            }
            case '4':
            {
                cout << "public channel selected, NOT WORKING YET" << endl;
                app.buildPublicChannel();
                break;
            }
            case '5':
            {
                cout << "friends selected" << endl;
                //app.buildFriendList(); // TODO need to figure out what to pass here to display friends.
                break;
            }
            case '6':
            {
                cout << "my account selected" << endl;
                app.buildAccountMenu(username, nameTag, accountType);
                break;
            }
            case 'q':
            {
                userQuit();
                break;
            }
            default:
            {
                cout << "Invalid Input, please try again.\n " << endl;
            }
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
    cout << "\tTerminating Program..." << endl;
    close(sock);
    exit(0);
}

void ClientController::userBack()
{
    cout << "\tGoing back..." << endl;
}

void ClientController::sendMessageToServer(Message m)
{
	memset(outBuffer, 0, MAXLINE);
	//m.printMessageToStdOut();

	strcpy((char*)outBuffer,(char*)m.getMessageAsCharArray());
	msgLength = m.getLength();

	//cout<< std::dec << msgLength << endl;


	bytesSent = send(sock, (char*) &outBuffer, msgLength, 0);
	//checkSending(bytesSent, msgLength);
	clearBuffer(outBuffer);
}

Message ClientController::recvMessageFromServer()
{
	cout << "------------------------------------------------------------------" << endl;
	clearBuffer(inBuffer);
	bytesRecv = recv(sock, (char*) &inBuffer, BUFFERSIZE, 0);
	cout << "********BYTES RECV: "<< std::dec <<bytesRecv << endl;
	Message msgFromServer(bytesRecv, inBuffer);
	clearBuffer(inBuffer);
	return msgFromServer;
}

Date ClientController::createCurrentDate()
{
	time_t now = time(0);
	tm *ltm = localtime(&now);
	Date date(ltm->tm_year, ltm->tm_mon, ltm->tm_mday, ltm->tm_sec);
	return date;
}

void ClientController::bulletinBoardCase()
{
    char bbOption; // Options within Bulletin Board
    cin >> bbOption;

    switch(bbOption)
    {
        case '1':
        {
            cout << "\tAdd post selected." << endl;
            app.addPostMenu();
            string postContent;
            cin >> postContent;

            Date postDate = createCurrentDate(); // Get current date.
            Posting toPost(postContent, username, postDate); // Create post
            CreatePostingMessage postCreated = theCreator.createCreatePostingMessage(BOARD_ID, toPost); // Create CreatePostingMessage to send to server.
            sendMessageToServer(postCreated);
            Message msg = recvMessageFromServer();
            if(theConvertor.isWriteSuccessfulMessage(recvMessageFromServer()))
            {
            	cout << "\tPost has been added." << endl;
            }
            else
            {
            	cout << "\tPost was NOT able to be added." << endl;
            }
            break;
        }
        case '2':
        {
            cout << "\tSend Message selected" << endl;
            cout << "Please enter a username of who you want to send a message to: " << endl;
            string usernameToSend;
            cin >> usernameToSend;
            // MIGHT HAVE TO VALIDATE USERNAME IS CORRECT first?
            cout << "Please enter your message: " << endl;
            string messageToUser;
            cin >> messageToUser;

            UserMessage messageToSend(username, usernameToSend, createCurrentDate(), messageToUser);
            SendUserMessageMessage messageMessageToSend = theCreator.createSendUserMessageMessage(messageToSend); // Create message notifying a user message is going to send to server.
            sendMessageToServer(messageMessageToSend);
            //recvMessageToServer (want to recv a success or failure);s
            break;
        }
        case '3':
		{
        	unsigned int year;
        	unsigned int month;
        	unsigned int day;
        	string searchKeyword;
        	cout << "\tSearch selected" << endl;
        	cout << "Please enter start year: ";
        	cin >> year;
        	cout << "\nEnter start month: ";
        	cin >> month;
        	cout << "\nEnter start day: ";
        	cin >> day;
        	cout << "\nPlease enter search keyword: ";
        	cin >> searchKeyword;

        	Date startDate(year, month, day, 0);
        	BoardSearchMessage bsm = theCreator.createBoardSearchMessage(startDate, createCurrentDate(), BOARD_ID, searchKeyword);
        	sendMessageToServer(bsm);

        	cout << "\tSearch results will be generated below..." << endl;
        	Message post = recvMessageFromServer();
        	if(theConvertor.isErrorBoardNotFoundMessage(post))
        	{
        		cout << "\tNo results found or error in searching..." << endl;
        		break;
        	}

        	vector<PostingDataMessage> searchResultsFromBulletin;

        	while(theConvertor.isEndOfDataMessage(post))
        	{
        		if(!theConvertor.isPostingDataMessage(post))
        		{
        			cout << "\tError in receiving search results..." << endl;
        			break;
        		}
        		searchResultsFromBulletin.push_back(theConvertor.toPostingDataMessage(post));
        		post = recvMessageFromServer(); // Keep checking from server.
        	}

        	vector<string> searchedPosts;
			for(int i = 0; i < searchResultsFromBulletin.size(); i++)
			{
				searchedPosts.push_back(searchResultsFromBulletin[i].getPosting().getPostText()); // Convert the posts to char array.
			}

			app.buildSearchResults(searchedPosts);
        	break;
		}
        case 'b':
        {
        	userBack();
            break;
        }
        case 'q':
        {
            userQuit();
            break;
        }
        default:
        {
            cout << "invalid choice (bb)" << endl;
        }
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
        {
            cout << "display chat 1" << endl;
            break;
        }
        case '2':
        {
            cout << "display chat 2" << endl;
            break;
        }
        case '3':
        {
            cout << "display chat 3" << endl;
            break;
        }
        case '4':
        {
            cout << "display chat 4" << endl;
            break;
        }
        case '5':
        {
            cout << "display chat 5" << endl;
            break;
        }
        case 'b':
        {
        	userBack();
            break;
        }
        case 'q':
        {
            userQuit();
            break;
        }
        default:
        {
            cout << "invalid choice (chats)" << endl;
        }
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
        {
            cout << "post 1" << endl;
            break;
        }
        case '2':
        {
            cout << "post 2" << endl;
            break;
        }
        case '3':
        {
            cout << "post 3" << endl;
            break;
        }
        case '4':
        {
            cout << "post 4" << endl;
            break;
        }
        case '5':
        {
            cout << "post 5" << endl;
            break;
        }
        case 'b':
        {
        	userBack();
            break;
        }
        case 'q':
        {
            userQuit();
            break;
        }
        default:
        {
            cout << "invalid choice (posts)" << endl;
        }
    }
}

void ClientController::publicChannelCase()
{
	string userMessageInPublic;
	while(1)
	{
		cin >> userMessageInPublic;
		if(userMessageInPublic.compare("leave") == 0)
		{
			break;
		}
		else if(userMessageInPublic.compare("quit") == 0)
		{
			userQuit();
		}

		// TODO SEND MESSAGE to server (advanced)
	}
	cout << "\tLeaving Public Channel..." << endl;
}

void ClientController::friendsCase()
{
    char friendsOption;
    cin >> friendsOption;

    switch(friendsOption)
    {
        case '1':
        {
            cout << "\tAdd friend selected." << endl;
            string friendUser;
            cout << "Enter friend's username: ";
            cin >> friendUser;
            // TODO PASS FRIEND REQUEST TO SERVER
            break;
        }
        case 'b':
        {
        	userBack();
            break;
        }
        case 'q':
        {
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
        {
            cout << "\tChange username selected." << endl;
            // todo
            break;
        }
        case '2':
        {
            cout << "\tChange password selected." << endl;
            // todo
            break;
        }
        case '3':
        {
            cout << "\tUpdate status selected." << endl;
            // todo
            break;
        }
        case '4':
        {
            if(accountType == "charity")
            {
                cout << "\tChange organization option selected." << endl;
                //todo
            }
            else
            {
                cout << "\t Operation unavailable. Only available for account types 'charity'." << endl;
            }
            break;
        }
        case '5':
        {
            cout << "\tChange account type selected." << endl;
            break;
        }
        case '6':
        {
            cout << "\tDelete account type selected" << endl;
            app.deleteAccountMenu();
            char deleteAccount;
            cin >> deleteAccount;
            if(deleteAccount == 'Y')
            {
                cout << "\tDeleting Account..." << endl;
                //TODO tell server to delete account
                userQuit();
            }
            else if(deleteAccount == 'b')
            {
               	userBack();
                break;
            }
            else
            {
                cout << "invalid option, going back anayways" << endl;
                break;
            }
            break;
        }
        case 'b':
        {
        	userBack();
            break;
        }
        case 'q':
        {
            userQuit();
            break;
        }
        default:
        {
            cout << "invalid choice (posts)" << endl;
        }
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
        sendMessageToServer(userAttempt);
        /*
        bytesSent = send(sock, (char *) &outBuffer, msgLength, 0);
        checkSending(bytesSent, msgLength); 
*/
        // Receive login info from server
        Message msgFromServer = recvMessageFromServer();
        /*
        bytesRecv = recv(sock, (char *) &inBuffer, msgLength, 0); // *** Could spawn error here if the length is not correct

        //checkRecv(bytesRecv, msgLength);

        Message msgFromServer(bytesRecv, inBuffer);
*/
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
            cout << "Invalid username/password, please try again.\n " << endl;
        }
    }
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
