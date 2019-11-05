/*
 * ConnectWithCare
 * "MainListener.h"
 * 
 * Last updated by: Daryl
 */
#ifndef MAIN_LISTENER
#define MAIN_LISTENER

#include "GUI.h"

class MainListener
{
    public:
        MainListener(GUI m);
        // Constructs MainListener with a GUI.
        void run();
        // Runs GUI and listens to the users responses to display the correct GUI.

    private:
        GUI main;
};
#endif