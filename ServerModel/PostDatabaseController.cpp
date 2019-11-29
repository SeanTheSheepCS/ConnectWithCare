/*
 * PostDatabaseController.cpp
 *
 *  Created on: Nov 20, 2019
 *      Author: QCepl
 */

#include "PostDatabaseController.h"
#include <string>
#include <locale> // for toupper()
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

unsigned long int PostDatabaseController::searchBoardAndPlaceResultsInVector(BoardSearchMessage boardSearchMessage, vector<Posting>& selectedPosts) {
	unsigned long int boardIDTheUserWantsHistoryOf = boardSearchMessage.getBoardID();
	if ( checkIfDesiredBoardExists(boardIDTheUserWantsHistoryOf) != ORIGINAL_MESSAGE_CODE ) {
		return SERVERMESSAGECODE_ERRORBOARDNOTFOUND;
	}
	return iterateThroughDatabaseToFindSearchKeywords(boardSearchMessage, boardIDTheUserWantsHistoryOf, selectedPosts);
}
unsigned long int PostDatabaseController::iterateThroughDatabaseToFindSearchKeywords(BoardSearchMessage boardSearchMessage, unsigned long int boardIDTheUserWantsHistoryOf, vector<Posting>& selectedPosts) {
	// could potentially take too long computationally
	for (Posting p : bulletinBoardsDatabase[boardIDTheUserWantsHistoryOf]) {
		string postText = p.getPostText();
		string keyword = boardSearchMessage.getSearchKeyword();
		if ( postText.find(keyword) != string::npos
			|| postText.find( capitalizeWord(keyword) ) != string::npos
			|| postText.find( allCapsWord(keyword) ) != string::npos )
		{
			selectedPosts.push_back(p);
		}
	}
	return SERVERMESSAGECODE_ENDOFDATA;
}
string PostDatabaseController::allCapsWord(string word) {
	string allCapsWord = "";
	for (string::size_type i = 0; i < word.length(); ++i)
		allCapsWord += toupper(word[i]);
	return allCapsWord;
}
string PostDatabaseController::capitalizeWord(string word) {
	string capitalizedWord = "";
	if (word.length() != 0) {
		capitalizedWord += toupper(word[0]);
		for (string::size_type i = 1; i < word.length(); ++i)
			capitalizedWord += word[i];
	}
	return capitalizedWord;
}
unsigned long int PostDatabaseController::getBoardHistoryAndPlaceInVector(BoardHistoryMessage boardHistoryMessage, vector<Posting>& selectedPosts) {
	unsigned long int boardIDTheUserWantsHistoryOf = boardHistoryMessage.getBoardID();
	if ( checkIfDesiredBoardExists(boardIDTheUserWantsHistoryOf) != ORIGINAL_MESSAGE_CODE ) {
		return SERVERMESSAGECODE_ERRORBOARDNOTFOUND;
	}
	return iterateThroughDatabaseToGetHistory(boardHistoryMessage, boardIDTheUserWantsHistoryOf, selectedPosts);
}

unsigned long int PostDatabaseController::iterateThroughDatabaseToGetHistory(BoardHistoryMessage& boardHistoryMessage, unsigned long int boardIDTheUserWantsHistoryOf, vector<Posting>& selectedPosts) {
	Date startDate = boardHistoryMessage.getStartDate();
	Date endDate   = boardHistoryMessage.getEndDate();
	for (Posting p : bulletinBoardsDatabase[boardIDTheUserWantsHistoryOf]) {
		if ( (p.getDateTimePosted().equals(startDate) || p.getDateTimePosted().isAfter(startDate))
				&& (p.getDateTimePosted().equals(endDate) || p.getDateTimePosted().isBefore(endDate)) )
		{
			selectedPosts.push_back(p);
		}
	}
	return SERVERMESSAGECODE_ENDOFDATA;
}

void PostDatabaseController::populateMapWithHardCodedEntries() {
	// need to decide how board IDs are set up
	unsigned long int boardIDTheUserWantsToPostTo = DEFAULT_BOARD_ID;
	bulletinBoardsDatabase[boardIDTheUserWantsToPostTo].insert(
			Posting("Hello! I'm stuck in the past and my time machine broke.\n If you find this message please tell my children I love them.\n", "IMissThePresent", Date(1262, 1, 29, 1200)) );
	bulletinBoardsDatabase[boardIDTheUserWantsToPostTo].insert(
			Posting("Hey, my fridge broken. If anyone could help me fix it that'd be so helpful.", "QuincyShelinger", Date(2019, 7, 12, 1200)) );
	bulletinBoardsDatabase[boardIDTheUserWantsToPostTo].insert(
			Posting("Hey, there's some extra food at the Central Library. Come pick it up in room 301!", "JohnSmith", Date(2019, 11, 22, 1200)) );
}



















