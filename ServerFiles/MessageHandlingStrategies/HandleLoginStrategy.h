/*
 * HandleLoginStrategy.h
 *
 *  Created on: Nov 7, 2019
 *      Author: QCepl
 */

#ifndef HANDLELOGINSTRATEGY_H_
#define HANDLELOGINSTRATEGY_H_

#include "../../CommonFiles/Message.h"
#include "../../CommonFiles/AllMessageTypes.h"

class HandleLoginStrategy : public ServerMessageHandlingStrategy
{
public:
	HandleLoginStrategy();
	virtual ~HandleLoginStrategy();

	Message handle(Message msgFromClient);
};

#endif /* HANDLELOGINSTRATEGY_H_ */
