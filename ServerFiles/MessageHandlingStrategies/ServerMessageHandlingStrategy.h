/*
 * ServerMessageHandlingStrategy.h
 *
 *  Created on: Nov 7, 2019
 *      Author: QCepl
 */

#ifndef SERVERMESSAGEHANDLINGSTRATEGY_H_
#define SERVERMESSAGEHANDLINGSTRATEGY_H_

class ServerMessageHandlingStrategy {
public:
	virtual Message handle(Message msgFromClient) = 0;
protected:
	ServerMessageCreator messageCreator;
};

#endif /* SERVERMESSAGEHANDLINGSTRATEGY_H_ */
