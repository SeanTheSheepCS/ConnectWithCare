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

HandleLoginStrategy::HandleLoginStrategy() {
}

HandleLoginStrategy::~HandleLoginStrategy() {
}

Message HandleLoginStrategy::handle(Message msgFromClient) {
	return messageCreator.createLoginAuthMessage(true);
}

