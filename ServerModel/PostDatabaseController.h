/*
 * PostDatabaseController.h
 *
 *  Created on: Nov 20, 2019
 *      Author: QCepl
 */

#ifndef POSTDATABASECONTROLLER_H_
#define POSTDATABASECONTROLLER_H_


#include <map>
#include <set>
#include <vector>
#include <string>
#include "../CommonFiles/Postings/Posting.h"
#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"

using namespace std;

#define ORIGINAL_MESSAGE_CODE 0
#define DEFAULT_BOARD_ID 69

class PostDatabaseController {
private:
	map<unsigned long int, set<Posting>> bulletinBoardsDatabase;
	set<Posting> masterBulletinBoard;

	string allCapsWord(string word);
	string capitalizeWord(string word);
	void populateMapWithHardCodedEntries();
public:
	PostDatabaseController();
	virtual ~PostDatabaseController();

	unsigned long int addNewPostAndReturnSpecialMessageCode(CreatePostingMessage postingMsgFromClient);
		unsigned long int checkIfDesiredBoardExists(unsigned long int boardIDTheUserWantsToPostTo);
		unsigned long int writePostToDatabase(CreatePostingMessage postingMsgFromClient);
	unsigned long int searchBoardAndPlaceResultsInVector(BoardSearchMessage boardSearchMessage, vector<Posting>& selectedPosts);
		unsigned long int iterateThroughDatabaseToFindSearchKeywords(BoardSearchMessage boardSearchMessage, unsigned long int boardIDTheUserWantsHistoryOf, vector<Posting>& selectedPosts);
	unsigned long int getBoardHistoryAndPlaceInVector(BoardHistoryMessage boardHistoryMessage, vector<Posting>& selectedPostings);
		unsigned long int iterateThroughDatabaseToGetHistory(BoardHistoryMessage& boardHistoryMessage, unsigned long int boardIDTheUserWantsHistoryOf, vector<Posting>& selectedPosts);
};

#endif /* POSTDATABASECONTROLLER_H_ */
