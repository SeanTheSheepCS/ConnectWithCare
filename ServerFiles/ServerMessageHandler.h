/*
 * ServerMessageHandler.h
 *
 *  Created on: Nov 7, 2019
 *      Author: QCepl
 */

#ifndef SERVERMESSAGEHANDLER_H_
#define SERVERMESSAGEHANDLER_H_

class ServerMessageHandler {
public:
	ServerMessageHandler();
	virtual ~ServerMessageHandler();

	Message handleMessageFromClient();

	void setMessage(Message msg);

	void setStrategy(ServerMessageHandlingStrategy& strat);
private:
	Message msgFromClient;
	ServerMessageHandlingStrategy& handlingStrategy;
};

#endif /* SERVERMESSAGEHANDLER_H_ */
