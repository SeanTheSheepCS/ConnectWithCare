/*
 * ConnectWithCare
 * "MainListener.cpp"
 * 
 * Last updated by: Daryl
 */

#include "MainListener.h"
#include <iostream>
using namespace std;

MainListener::MainListener(GUI m)
{
    main = m;
}

void MainListener::run()
{
    main.buildWelcomeMessage();

    /*** LOGIN VALIDATION HERE ***/

    main.buildMenu(0, 0, 0); // have to be able to get notification numbers here
    char option;
    cin >> option;
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

int main()
{  
    GUI demo;
    MainListener clientListener(demo);
    clientListener.run();
}
