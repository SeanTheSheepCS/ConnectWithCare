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

using namespace std;

class LoginDatabaseController {
public:
	LoginDatabaseController();
	virtual ~LoginDatabaseController();

	bool validateUser(string username, string password);
private:
	map<string, string> loginDatabase;

	void populateMapWithHardCodedEntries();

};

#endif /* LOGINDATABASECONTROLLER_H_ */
