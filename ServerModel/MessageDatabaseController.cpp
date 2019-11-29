/*
 * MessageDatabaseController.cpp
 *
 *  Created on: Nov 28, 2019
 *      Author: QCepl
 */

#include "MessageDatabaseController.h"
#include <map>
#include <set>
#include <string>
#include <iostream>
#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"
#include "../CommonFiles/MessageCodes.h"

using namespace std;

MessageDatabaseController::MessageDatabaseController() {
	// TODO Auto-generated constructor stub
	conversationsDatabase = map<string, set<UserMessage>>();
	publicChannel = set<UserMessage>();
}

MessageDatabaseController::~MessageDatabaseController() {
	// TODO Auto-generated destructor stub
}

void MessageDatabaseController::startNewConversation(string user1, string user2) {
	string conversationTag = user1 + "++" + user2;
	set<UserMessage> conversation;
	conversationsDatabase.insert(pair<string, set<UserMessage>>(conversationTag, conversation) );
}
unsigned long int MessageDatabaseController::getAllConversationHistoryAndPlaceInVector(UserMessageHistoryAllMessage allHistoryMessage, vector<UserMessage>& selectedMsgs) {
	return iterateThroughDatabaseToGetPublicChannelHistory(allHistoryMessage, selectedMsgs);
}
unsigned long int MessageDatabaseController::iterateThroughDatabaseToGetPublicChannelHistory(UserMessageHistoryAllMessage& historyMessage, vector<UserMessage>& selectedMsgs) {
	Date startDate = historyMessage.getStartDate();
	Date endDate   = historyMessage.getEndDate();
	for (UserMessage um : publicChannel) {
		if ( (um.getDateCreated().equals(startDate) || um.getDateCreated().isAfter(startDate))
				&& (um.getDateCreated().equals(endDate) || um.getDateCreated().isBefore(endDate)) )
		{
			selectedMsgs.push_back(um);
		}
	}
	return SERVERMESSAGECODE_ENDOFDATA;
}
int MessageDatabaseController::checkIfDesiredConvoExists(string tag1, string tag2) {
	map<string, set<UserMessage>>::iterator it1, it2;
	it1 = conversationsDatabase.find(tag1);
	it2 = conversationsDatabase.find(tag2);
	if (it1 == conversationsDatabase.end() && it2 == conversationsDatabase.end() )
		return TAG_NOT_FOUND;
	else if (it1 != conversationsDatabase.end() )
		return TAG1;
	else
		return TAG2;
}
unsigned long int MessageDatabaseController::getConversationHistoryAndPlaceInVector(UserMessageHistoryMessage historyMessage, string userWhoAskedForHistory, vector<UserMessage>& selectedMsgs) {
	int whichTag;
	string convoTag1 = historyMessage.getUsernameToGetHistoryWith() + "++" + userWhoAskedForHistory;
	string convoTag2 = userWhoAskedForHistory + "++" + historyMessage.getUsernameToGetHistoryWith();
	cout << "in convo controller getHistory, client wants to access tag" << convoTag1 << "\n";
	if ( (whichTag = checkIfDesiredConvoExists(convoTag1, convoTag2) ) == TAG_NOT_FOUND ) {
		return SERVERMESSAGECODE_ERRORUSERNOTFOUND;
	}
	string useThisConvoTag = (whichTag == 1) ? convoTag1 : convoTag2;
	return iterateThroughDatabaseToGetHistory(historyMessage, useThisConvoTag, selectedMsgs);
}
unsigned long int MessageDatabaseController::iterateThroughDatabaseToGetHistory(UserMessageHistoryMessage historyMessage, string& tag, vector<UserMessage>& selectedMsgs) {
	Date startDate = historyMessage.getStartDate();
	Date endDate   = historyMessage.getEndDate();
	for (UserMessage um : conversationsDatabase[tag]) {
		if ( (um.getDateCreated().equals(startDate) || um.getDateCreated().isAfter(startDate))
				&& (um.getDateCreated().equals(endDate) || um.getDateCreated().isBefore(endDate)) )
		{
			selectedMsgs.push_back(um);
		}
	}
	return SERVERMESSAGECODE_ENDOFDATA;
}

