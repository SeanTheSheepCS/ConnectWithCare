/*
 * MessageDatabaseController.h
 *
 *  Created on: Nov 28, 2019
 *      Author: QCepl
 */

#ifndef MESSAGEDATABASECONTROLLER_H_
#define MESSAGEDATABASECONTROLLER_H_

#include <map>
#include <set>
#include <string>
#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"
#include "../CommonFiles/MessageCodes.h"

#define TAG_NOT_FOUND 0
#define TAG1 1
#define TAG2 2

class MessageDatabaseController {
public:
	MessageDatabaseController();
	virtual ~MessageDatabaseController();

	void startNewConversation(string user1, string user2);

	int checkIfDesiredConvoExists(string tag1, string tag2);
	unsigned long int getAllConversationHistoryAndPlaceInVector(UserMessageHistoryAllMessage allHistoryMessage, vector<UserMessage>& selectedMsgs);
		unsigned long int iterateThroughDatabaseToGetPublicChannelHistory(UserMessageHistoryAllMessage& historyMessage, vector<UserMessage>& selectedMsgs);
	unsigned long int getConversationHistoryAndPlaceInVector(UserMessageHistoryMessage historyMessage, string userWhoAskedForHistory, vector<UserMessage>& selectedMsgs);
		unsigned long int iterateThroughDatabaseToGetHistory(UserMessageHistoryMessage historyMessage, string& tag, vector<UserMessage>& selectedMsgs);

private:
	map<string, set<UserMessage>> conversationsDatabase;
	set<UserMessage> publicChannel;

	void hardcode();
};

#endif /* MESSAGEDATABASECONTROLLER_H_ */
