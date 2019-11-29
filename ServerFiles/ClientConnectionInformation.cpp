/*
 * ClientConnectionInformation.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: QCepl
 */

#include "ClientConnectionInformation.h"
#include <iostream>

ClientConnectionInformation::ClientConnectionInformation(struct sockaddr_in clientAddr, int currentClientSocket) {
	this->clientAddr = clientAddr;
	this->currentClientSocket = currentClientSocket;
}

struct sockaddr_in ClientConnectionInformation::getClientAddr() {
	return clientAddr;
}
int ClientConnectionInformation::getCurrentClientSocket() {
	return currentClientSocket;
}
string ClientConnectionInformation::getUsername() {
	return username;
}

void ClientConnectionInformation::setUsername(string UN) {
	this->username = UN;
}

void ClientConnectionInformation::display() {
	cout << clientAddr.sin_addr << ":" << clientAddr.sin_port << " -- socket: " << currentClientSocket;
	cout << endl;
}

