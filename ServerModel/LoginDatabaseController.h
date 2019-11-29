/*
 * LoginDatabaseController.h
 *
 *  Created on: Nov 8, 2019
 *      Author: QCepl
 */

#ifndef LOGINDATABASECONTROLLER_H_
#define LOGINDATABASECONTROLLER_H_

#include <map>
#include <string>

#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"

using namespace std;

class LoginDatabaseController {
public:
	LoginDatabaseController();
	virtual ~LoginDatabaseController();

	bool validateUser(string username, string password);
	unsigned char* getAccountType(string username);
	bool confirmLogout();
private:
	map<string, string> loginDatabase;
	map<string, string> accountTypes;

	void populateMapWithHardCodedEntries();

};

#endif /* LOGINDATABASECONTROLLER_H_ */
