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
 * Last updated by: Daryl
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

void GUI::buildLogin()
{
    cout << "---Enter username and password---" << endl;
   
    cout << "Username:";
    string userN;
    cin >> userN;
    while(/*validate login(userN)*/0)
    {
        cout << "Invalid, try again.";
        cin >> userN;
    }

    cout << "Password:";
    string passN;
    cin >> passN;
    while(/*validate login(passN)*/0)
    {
        cout << "Invalid, try again.";
        cin >> passN;
    }
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

char GUI::buildBulletinBoard()
{
    cout << divider << "BULLETIN-BOARD" << divider << endl;

    // NEED TO FIGURE OUT REST OF IMPLEMENTATION HERE

    cout << divider << "--------------" << divider << endl;
    cout << "  (1) Add Post  (2) Send Message  (b) Go Back  (q) Quit Program" << endl;
    char option;
    cin >> option;
    if(option == 'q')
    {
        cout << "Program terminating..." << endl;
        exit(0);
    }
    return option;
}

char GUI::buildChatsMenu(unsigned int pcNotifications, char** friends, int friendsLength)
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
    if(option == 'q')
    {
        cout << "Program terminating..." << endl;
        exit(0);
    }
    return option;
}

char GUI::buildPostsMenu(char** posts, int postsLength)
{
    cout << divider << "YOUR-POSTS" << divider << endl;

    for(int i = 0; i < postsLength; i++)
    {
        /***** PRINT POST NAME AND DATE HERE *****/
    }

    cout << divider << "----------" << divider << endl;
    cout << " (1) Add Post  (2) Search  (b) Go Back  (q) Quit program" << endl;
    char option;
    cin >> option;
    if(option == 'q')
    {
        cout << "Program terminating..." << endl;
        exit(0);
    }
    return option;
}

char GUI::buildFriendList(char** onlineFriends, int onlineLength, char** offlineFriends, int offlineLength)
{
    cout << divider << "FRIENDS" << divider << endl;

    cout << "Online:\n";
    for(int i = 0; i < onlineLength; i++)
    {
        cout << "\t";
        /***** PRINT FRIEND NAME HERE *****/
        cout << endl;
    }

    cout << "Offline:\n";
    for(int i = 0; i < offlineLength; i++)
    {
        cout << "\t";
        /***** PRINT FRIEND NAME HERE *****/
        cout << endl;
    }
    cout << divider << "-------" << divider << endl;
    cout << " (1) Add Friend  (b) Go Back  (q) Quit program" << endl;
    char option;
    cin >> option;
    if(option == 'q')
    {
        cout << "Program terminating..." << endl;
        exit(0);
    }
    return option;
}

char GUI::buildAccountMenu(string username, string nameTag, string accountType)
{
    cout << divider << "ACCOUNT-MENU" << divider << endl;

    cout << "   Username: <" << username << ">" << endl;
    cout << "   Nametag: <" << nameTag << ">" << endl;
    cout << "   Account Type: <" << accountType << ">" << endl;
    cout << "\n[1] Change Username" << endl;
    cout << "[2] Change Password" << endl;
    cout << "[3] Update Status" << endl;
    cout << "[4] Update Orginization Information (Charity Only)" << endl;
    cout << "[5] Change Account Type (Individual or Charity)" << endl;
    cout << "[6] Delete Account" << endl;
    cout << "[b] Go Back" << endl;
    cout << "[q] Quit Program" << endl;
    cout << divider << "------------" << divider << endl;
    cout << "Enter Option: ";
    char option;
    cin >> option;
    if(option == 'q')
    {
        cout << "Program terminating..." << endl;
        exit(0);
    }
    return option;
}
/*
int main() // Testing how it looks.
{
    cout << "testing GUI" << endl;
    GUI theView;
    theView.buildLogin();
    char opt = theView.buildMenu(2, 27, 121);
    cout << opt << endl;
    return 0;
}
*/