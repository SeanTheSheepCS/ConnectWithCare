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
#include "../CommonFiles/Postings/Posting.h"
#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/AllMessageTypes.h"

using namespace std;

class PostDatabaseController {
private:
	map<unsigned long int, set<Posting>> bulletinBoardsDatabase;
	set<Posting> masterBulletinBoard;

	void populateMapWithHardCodedEntries();
public:
	PostDatabaseController();
	virtual ~PostDatabaseController();

	unsigned long int addNewPostAndReturnSpecialMessageCode(CreatePostingMessage postingMsgFromClient);
		unsigned long int checkIfDesiredBoardExists(unsigned long int boardIDTheUserWantsToPostTo);
		unsigned long int writePostToDatabase(CreatePostingMessage postingMsgFromClient);
};

#endif /* POSTDATABASECONTROLLER_H_ */
