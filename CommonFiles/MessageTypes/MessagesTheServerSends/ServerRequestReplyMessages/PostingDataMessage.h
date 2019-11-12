#ifndef POSTING_DATA_MESSAGE_H
#define POSTING_DATA_MESSAGE_H

#include "../ServerRequestReplyMessages.h"
#include "../../../Posting.h"

class PostingDataMessage : public ServerRequestReplyMessage
{
	public:
		PostingDataMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		PostingDataMessage(const PostingDataMessage& other);
	    virtual PostingDataMessage& operator=(const PostingDataMessage& rhs);
	    virtual ~PostingDataMessage();
	    unsigned long int getBoardIDThatThePostingBelongsTo();
	    Posting getPosting();
	protected:
	    //
	private:
	    unsigned long int boardIDThatThePostingBelongsTo;
	    Posting* thePosting;
};

#endif
