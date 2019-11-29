/*
 * ConnectWithCare
 * "GUI.h"
 * 
 * NOTE: 
 * - Might add functionality later to make b and q global operations for the whole program.
 * - Possibly change passing multi char array 
 * - might have to attach specific client to each gui interface.
 * 
 * EXTRA STUFF FOR LATER:
 * - add number of friends to the top of friends list.
 * 
 */
#include "GUI.h"
#include <iostream>

using namespace std;
string divider = "-------------------------";

GUI::GUI()
{
    //client = c;
}

void GUI::buildWelcomeMessage()
{
    cout << "*** Welcome to Connect With Care! ****" << endl;
}

void GUI::buildUsernameField()
{
    cout << "Username:";
}

void GUI::buildPasswordField()
{
    cout << "Password:";
}

void GUI::buildMenu(unsigned int bbNotifications, unsigned int chatNotifications, unsigned int publicNotifications)
{
    cout << divider << "MAIN-MENU" << divider << endl;
    
    // Print Bulletin Board
    cout.setf(ios::left);
    cout.width(25);
    cout << "[1] Bulletin Board"; 
    cout.setf(ios::right);
    cout.width(3);
    cout << "(" << bbNotifications << ")" << endl;
    cout.unsetf(ios::right);

    // Print Chats
    cout.setf(ios::left);
    cout.width(25);
    cout << "[2] Chats"; 
    cout.setf(ios::right);
    cout.width(3);
    cout << "(" << chatNotifications << ")\n";
    cout.unsetf(ios::right);

    // Print My Posts
    cout << "[3] My Posts\n";

    // Print Public Channel
    cout.setf(ios::left);
    cout.width(25);
    cout << "[4] Public Channel";
    cout.setf(ios::right);
    cout.width(3);
    cout << "(" << publicNotifications << ")\n";
    cout.unsetf(ios::right);
    
    // Print Friends
    cout << "[5] Friends\n";

    // Print My Account
    cout << "[6] My Account\n";
    cout << divider << "---------" << divider << endl;

    cout << "Enter option (or type 'q' to exit):";
}

void GUI::buildBulletinBoard(vector<string> bulletinBoard)
{
    cout << divider << "BULLETIN-BOARD" << divider << endl;

    for(int i = 0; i < bulletinBoard.size(); i++)
    {
    	cout << "Post " << i << endl;
    	cout << bulletinBoard[i] << endl; // Adds posts to bulletin board.
    	cout << divider << "--------------" << divider << endl;
    }

    cout << "  (1) Add Post  (2) Send Message (3)Search (b) Go Back  (q) Quit Program" << endl;
}

void GUI::buildSearchResults(vector<string> searchResults)
{
	cout << endl;
	cout << divider << "SEARCH-RESULTS" << divider << endl;

	for(int i = 0; i < searchResults.size(); i++)
	{
		cout << searchResults[i] << endl;
	}

	cout << divider << "--------------" << divider << endl;
}
void GUI::addPostMenu()
{
	cout << divider << "ADDING-POST" << divider << endl;
	cout << "Please enter post (press enter once finished): " << endl;
}

void GUI::buildChatsMenu(unsigned int pcNotifications, char** friends, int friendsLength)
{
    cout << divider << "CHATS-MENU" << divider << endl;

    cout.setf(ios::left);
    cout.width(25);
    cout << "[0] PUBLIC CHAT";
    cout.setf(ios::right);
    cout.width(3);
    cout << "(" << pcNotifications << ")" << endl;
    cout.unsetf(ios::right);

    for(int i = 0; i < friendsLength; i++)
    {
        cout.setf(ios::left);
        cout.width(25);
        cout << "[" << (i + 1) << "]";
        /***** PRINT FRIEND NAME AND NOTIFICAITONS HERE *****/
        cout << endl;
    }

    cout << divider << "----------" << divider << endl;
    cout << " (#) Enter number to view chat history  (b) Go Back  (q) Quit program" << endl;
    char option;
    cin >> option;
}

void GUI::buildPostsMenu(char** posts, int postsLength)
{
    cout << divider << "YOUR-POSTS" << divider << endl;

    for(int i = 0; i < postsLength; i++)
    {
        /***** PRINT POST NAME AND DATE HERE *****/
    }

    cout << divider << "----------" << divider << endl;
    cout << " (1) Search  (b) Go Back  (q) Quit program" << endl;
}

void GUI::buildPublicChannel()
{
    cout << divider << "PUBLIC-CHANNEL" << divider << endl;
    cout << "Enter Message below! (Type 'leave' to go back or 'quit' to exit program)";
}

void GUI::buildFriendList(/*char** onlineFriends, int onlineLength, char** offlineFriends, int offlineLength*/)
{
    cout << divider << "FRIENDS" << divider << endl;

    cout << "Online:\n";
    for(int i = 0; i < 5; i++)
    {
        cout << "\t";
        cout << "Friend " << i;
        cout << endl;
    }

    cout << "Offline:\n";
    for(int i = 0; i < 3; i++)
    {
        cout << "\t";
        cout << "Friend " << i + 6;
        cout << endl;
    }
    cout << divider << "-------" << divider << endl;
    cout << " (1) Add Friend  (b) Go Back  (q) Quit program" << endl;
}

void GUI::buildAccountMenu(string username, string nameTag, string accountType)
{
    cout << divider << "ACCOUNT-MENU" << divider << endl;

    cout << "   Username: <" << username << ">" << endl;
    cout << "   Nametag: <" << nameTag << ">" << endl;
    cout << "   Account Type: <" << accountType << ">" << endl;
    cout << "\n[1] Change Username" << endl;
    cout << "[2] Change Password" << endl;
    cout << "[3] Change Account Type (Individual or Charity)" << endl;
    cout << "[4] Delete Account" << endl;
    cout << "[b] Go Back" << endl;
    cout << "[q] Quit Program" << endl;
    cout << divider << "------------" << divider << endl;
    cout << "Enter Option: ";
}

void GUI::deleteAccountMenu()
{
    cout << divider << endl;
    cout << "Are you sure you want to delete your account?\nType 'Y' to confirm or 'b' to go back." << endl;
    cout << divider << endl;
}
