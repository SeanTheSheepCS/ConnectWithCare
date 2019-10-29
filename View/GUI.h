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

class GUI
{
    public:
        GUI ();
        void buildLogin();
        // Builds login menu, makes sure that entry is correct by calling "validate" from UserDB.
        char buildMenu(unsigned int bbNotifications, unsigned int chatNotifications, unsigned int publicNotifications);
        // Builds the menu and returns the option selected by the user (as a char).

};

#endif