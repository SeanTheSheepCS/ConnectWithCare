/*
 * ConnectWithCare
 * "GUI.h"
 * 
 * Last updated by: Daryl
 */
#include "GUI.h"
#include <iostream>

using namespace std;
string divider = "-------------------------";

GUI::GUI(){}

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

char GUI::buildMenu(unsigned int bbNotifications, unsigned int chatNotifications, unsigned int publicNotifications)
{
    cout << "\n\n\tMAIN MENU" << endl;

    cout.setf(ios::left);
    cout.width(25);
    cout << "[1] Bulletin Board";
    cout.setf(ios::right);
    cout.width(3);
    cout << "(" << bbNotifications << ")" << endl;
    cout.unsetf(ios::right);

    cout.setf(ios::left);
    cout.width(25);
    cout << "[2] Chats";
    cout.setf(ios::right);
    cout.width(3);
    cout << "(" << chatNotifications << ")\n";
    cout.unsetf(ios::right);

    cout << "[3] My Posts\n";

    cout.setf(ios::left);
    cout.width(25);
    cout << "[4] Public Channel";
    cout.setf(ios::right);
    cout.width(3);
    cout << "(" << publicNotifications << ")\n";
    cout.unsetf(ios::right);
    
    cout << "[5] Friends\n";
    cout << "[6] My Account\n";
    cout << divider << endl;

    cout << "Enter option (or type 'q' to exit):";
    char option;
    cin >> option;
    if(option == 'q')
    {
        cout << "Program terminating..." << endl;
        exit(0);
    }
    return option;
}

int main() // Testing how it looks.
{
    cout << "testing GUI" << endl;
    GUI theView;
    theView.buildLogin();
    char opt = theView.buildMenu(2, 27, 121);
    cout << opt << endl;
    return 0;
}