/*
 * HandleLoginStrategy.cpp
 *
 *  Created on: Nov 7, 2019
 *      Author: QCepl
 */

#include "HandleLoginStrategy.h"
#include "../../CommonFiles/Message.h"
#include "../../CommonFiles/AllMessageTypes.h"
#include "../ServerMessageCreator.h"

/*
HandleLoginStrategy::HandleLoginStrategy(LoginDatabaseController& loginDB)
: ServerMessageHandlingStrategy() {
	loginDatabase = loginDB;
}

Message HandleLoginStrategy::handle(LoginAuthMessage msgFromClient) {
	bool validated = loginDatabase.validate(msgFromClient.getUsername(), msgFromClient.getPassword());
	returnmessageCreator.createLoginAuthMessage(true);
}
*/

