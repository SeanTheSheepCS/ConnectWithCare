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

#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"

using namespace std;


LoginDatabaseController::LoginDatabaseController() {
	loginDatabase = map<string,string>();
	accountTypes = map<string, string>();
	populateMapWithHardCodedEntries();
}

void LoginDatabaseController::populateMapWithHardCodedEntries() {
	loginDatabase.insert(pair<string,string>("QuinnC", "314") );
	accountTypes.insert(pair<string,string>("QuinnC","Individual") );
	loginDatabase.insert(pair<string,string>("BiancaC", "159") );
	accountTypes.insert(pair<string,string>("BiancaC","Individual") );
	loginDatabase.insert(pair<string,string>("DarylD", "265") );
	accountTypes.insert(pair<string,string>("DarylD","Individual") );
	loginDatabase.insert(pair<string,string>("SeanK", "358") );
	accountTypes.insert(pair<string,string>("SeanK","Individual") );
	loginDatabase.insert(pair<string,string>("TheAlex", "123") );
	accountTypes.insert(pair<string,string>("TheAlex","Charity") );
	loginDatabase.insert(pair<string,string>("CalgaryFoodBank", "456") );
	accountTypes.insert(pair<string,string>("CalgaryFoodBank","Charity") );
}

LoginDatabaseController::~LoginDatabaseController() {
}

bool LoginDatabaseController::validateUser(string username, string password) {
	//cout << endl << username << endl << password << endl;
	map<string,string>::iterator it = loginDatabase.begin();
	for ( ; it != loginDatabase.end(); it++) {
		//cout << endl << it->first << endl << it->second <<endl;
		if (it->first.compare(username) == 0 && it->first.compare(password) == 0)
		{
			//cout << "GOOD";
			return true;
		}
	}
	//cout <<"BAD";
	return false;
}

unsigned long int LoginDatabaseController::xx(LoginMessage& loginMessageFromClient, unsigned char** accountType) {
	map<string,string>::iterator it = accountTypes.begin();
	it = accountTypes.find(loginMessageFromClient.getUsername());
	*accountType = (unsigned char*)it->second.c_str();
	return (unsigned long int)it->second.length();
}

bool LoginDatabaseController::confirmLogout() {
		return true;
}


