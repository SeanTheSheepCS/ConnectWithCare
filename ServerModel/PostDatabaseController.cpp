/*
 * PostDatabaseController.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: QCepl
 */

#include "PostDatabaseController.h"
#include <map>
#include <set>
#include <vector>
#include "../ServerFiles/ServerMessageCreator.h"
#include "../CommonFiles/Postings/Posting.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"

PostDatabaseController::PostDatabaseController() {
	masterBulletinBoard = set<Posting>();
	bulletinBoardsDatabase = map<unsigned long int, set<Posting>>();

	populateMapWithHardCodedEntries();
}

PostDatabaseController::~PostDatabaseController() {
	// TODO Auto-generated destructor stub
}
unsigned long int PostDatabaseController::addNewPostAndReturnSpecialMessageCode(CreatePostingMessage postingMsgFromClient) {
	unsigned long int specialMessageCode = ORIGINAL_MESSAGE_CODE;
	unsigned long int boardIDTheUserWantsToPostTo = postingMsgFromClient.getBoardIDThatThePostingBelongsTo();
	if ( (specialMessageCode = checkIfDesiredBoardExists(boardIDTheUserWantsToPostTo)) != ORIGINAL_MESSAGE_CODE ) {
		return specialMessageCode;
	}
	specialMessageCode = writePostToDatabase(postingMsgFromClient);
	return specialMessageCode;
}

unsigned long int PostDatabaseController::checkIfDesiredBoardExists(unsigned long int boardIDTheUserWantsToPostTo) {
	map<unsigned long int, set<Posting>>::iterator it;
	it = bulletinBoardsDatabase.find(boardIDTheUserWantsToPostTo);
	if (it == bulletinBoardsDatabase.end())
		return SERVERMESSAGECODE_ERRORBOARDNOTFOUND;
	else
		return ORIGINAL_MESSAGE_CODE;
}

unsigned long int PostDatabaseController::writePostToDatabase(CreatePostingMessage postingMsgFromClient) {
	unsigned long int boardIDTheUserWantsToPostTo = postingMsgFromClient.getBoardIDThatThePostingBelongsTo();
	bool postAlreadyExists = bulletinBoardsDatabase[boardIDTheUserWantsToPostTo].find( postingMsgFromClient.getPosting() ) != bulletinBoardsDatabase[boardIDTheUserWantsToPostTo].end();
	if ( postAlreadyExists )
		return SERVERMESSAGECODE_ERRORWRITEFAILED;
	else {
		bulletinBoardsDatabase[boardIDTheUserWantsToPostTo].insert( postingMsgFromClient.getPosting() );
		masterBulletinBoard.insert( postingMsgFromClient.getPosting() );
		return SERVERMESSAGECODE_WRITESUCCESSFUL;
	}

}

vector<Posting> PostDatabaseController::getBoardHistory(BoardHistoryMessage boardHistoryMessage) {
	vector<Posting> selectedPostings;
	unsigned long int boardIDTheUserWantsHistoryOf = boardHistoryMessage.getBoardID();
	if ( checkIfDesiredBoardExists(boardIDTheUserWantsHistoryOf) != ORIGINAL_MESSAGE_CODE ) {
		return selectedPostings; // size of queue is zero, indicating error
	}

	return selectedPostings;
}

void PostDatabaseController::populateMapWithHardCodedEntries() {
	// need to decide how board IDs are set up
}
