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
#include "ServerMessageHandlingStrategy.h"
#include "../../ServerModel/LoginDatabaseController.h"

//class ServerMessageHandlingStrategy;

/*
class HandleLoginStrategy : public ServerMessageHandlingStrategy
{
public:
	HandleLoginStrategy(LoginDatabaseController& loginDB);

	~HandleLoginStrategy() {}

	Message handle(Message msgFromClient);
private:
	LoginDatabaseController& loginDatabase;
};
*/

#endif /* HANDLELOGINSTRATEGY_H_ */
