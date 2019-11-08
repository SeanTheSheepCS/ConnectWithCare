/*
 * LoginDatabaseController.cpp
 *
 *  Created on: Nov 8, 2019
 *      Author: QCepl
 */

#include "LoginDatabaseController.h"
#include <map>
#include <string>

using namespace std;


LoginDatabaseController::LoginDatabaseController() {
	loginDatabase = map<string,string>();
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
	map<string,string>::iterator it = loginDatabase.begin();
	for ( ; it != loginDatabase.end(); ++it) {
		if (it->first.compare(username) == 0 && it->second.compare(password) == 0)
			return true;
	}
	return false;
}


