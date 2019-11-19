/*
 * LoginDatabaseController.cpp
 *
 *  Created on: Nov 8, 2019
 *      Author: QCepl
 */

#include "LoginDatabaseController.h"
#include <map>
#include <string>
#include <iostream>

using namespace std;


LoginDatabaseController::LoginDatabaseController() {
	loginDatabase = map<string,string>();
	populateMapWithHardCodedEntries();
}

void LoginDatabaseController::populateMapWithHardCodedEntries() {
	loginDatabase.insert(pair<string,string>("QuinnC","314") );
	loginDatabase.insert(pair<string,string>("BiancaC","159") );
	loginDatabase.insert(pair<string,string>("DarylD","265") );
	loginDatabase.insert(pair<string,string>("SeanK","358") );
}

LoginDatabaseController::~LoginDatabaseController() {
}

bool LoginDatabaseController::validateUser(string username, string password) {
	cout << endl << username << endl << password << endl;
	map<string,string>::iterator it = loginDatabase.begin();
	for ( ; it != loginDatabase.end(); it++) {
		cout << endl << it->first << endl << it->second <<endl;
		if (it->first.compare(username) == 0 && it->second.compare(password) == 0)
		{
			cout << "GOOD";
			return true;
		}
	}
	cout <<"BAD";
	return false;
}

bool LoginDatabaseController::confirmLogout() {
		return true;
}


