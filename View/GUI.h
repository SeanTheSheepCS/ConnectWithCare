/*
 * ConnectWithCare
 * "GUI.h"
 * 
 */
#ifndef GUI_CLASS
#define GUI_CLASS

#include <string.h>
#include <string>
#include <vector>

using namespace std;

class GUI
{
    public:
        GUI ();
        void buildWelcomeMessage();
        // Builds a welcome message.
        void buildUsernameField();
        // Builds username field query.
        void buildPasswordField();
        // Builds password field query.
        void buildMenu(unsigned int bbNotifications, unsigned int chatNotifications, unsigned int publicNotifications);
        // Builds the menu and returns the option selected by the user (as a char).

        void buildBulletinBoard(vector<string> bulletinBoard);
        // Builds bulletin board and returns the option selected by the user (as a char).
        void buildSearchResults(vector<string> searchResults);
        // Builds the search results inquired from the bulletin board.
        void addPostMenu();
        // Builds adding post menu.
        void buildChatsMenu(unsigned int pcNotifications, char** friends, int friendsLength);
        // Builds Chats menu given the public chat notifications and an array of friends
        //    with their name and notifications. Returns a char for the option selected
        //    by the user.
        void buildPostsMenu(char** posts, int postsLength);
        // Builds Posts menu given the posts via a string array, which provides details on 
        //    title and date of the post. Returns a char for the option selected by the user.
        void buildPublicChannel();

        void buildFriendList(char** onlineFriends, int onlineLength, char** offlineFriends, int offlineLength);
        // Builds Friends list menu given online and offline friends via string arrays.
        //    Returns a char for the option selected by the user.
        void buildAccountMenu(string username, string nameTag, string accountType);
        // Builds Account menu given the user's username, name tag and account type. Returns
        //    a char for the option selected by the user.
        void deleteAccountMenu();
        // Builds the delete account interface.
    
    private:
        //ClientController client;
};

#endif
