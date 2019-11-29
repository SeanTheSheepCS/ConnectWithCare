/*
 * ClientConnectionInformation.h
 *
 *  Created on: Nov 28, 2019
 *      Author: QCepl
 */

#ifndef CLIENTCONNECTIONINFORMATION_H_
#define CLIENTCONNECTIONINFORMATION_H_

#include <string>

using namespace std;

class ClientConnectionInformation {
public:
	ClientConnectionInformation(struct 	sockaddr_in clientAddr, int currentClientSocket);
	virtual ~ClientConnectionInformation();

	struct sockaddr_in getClientAddr();
	int getCurrentClientSocket();
	string getUsername();


	void setUsername(string UN);
	void display();
private:
	struct 	sockaddr_in clientAddr;
	int 	currentClientSocket;
	string	username;
};

#endif /* CLIENTCONNECTIONINFORMATION_H_ */
