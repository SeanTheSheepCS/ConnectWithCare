/*
 * ConnectWithCare
 * "GUI.h"
 * 
 * Last updated by: Daryl
 */
#ifndef GUI_CLASS
#define GUI_CLASS

#include <string.h>
#include <string>

using namespace std;

class GUI
{
    public:
        GUI ();
        void buildWelcomeMessage();
        // Builds a welcome message.
        void buildLogin();
        // Builds login menu, makes sure that entry is correct by calling "validate" from UserDB.
        void buildMenu(unsigned int bbNotifications, unsigned int chatNotifications, unsigned int publicNotifications);
        // Builds the menu and returns the option selected by the user (as a char).
        char buildBulletinBoard();
        // Builds bulletin board and returns the option seleceted by the user (as a char).
        char buildChatsMenu(unsigned int pcNotifications, char** friends, int friendsLength);
        // Builds Chats menu given the public chat notifications and an array of friends
        //    with their name and notifications. Returns a char for the option selected
        //    by the user.
        char buildPostsMenu(char** posts, int postsLength);
        // Builds Posts menu given the posts via a string array, which provides details on 
        //    title and date of the post. Returns a char for the option selected by the user.
        char buildFriendList(char** onlineFriends, int onlineLength, char** offlineFriends, int offlineLength);
        // Builds Friends list menu given online and offline friends via string arrays.
        //    Returns a char for the option selected by the user.
        char buildAccountMenu(string username, string nameTag, string accountType);
        // Builds Account menu given the user's username, name tag and account type. Returns
        //    a char for the option selected by the user.


};

#endif