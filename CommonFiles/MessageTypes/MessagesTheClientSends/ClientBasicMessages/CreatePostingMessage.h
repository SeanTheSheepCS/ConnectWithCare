#ifndef CREATE_POSTING_MESSAGE_H
#define CREATE_POSTING_MESSAGE_H

#include <string>
#include "../ClientBasicMessages.h"
#include "../../../Utilities/VariableLengthQuantityLibrary.h"
#include "../../../Posting.h"

class CreatePostingMessage : public ClientBasicMessage
{
	public:
		CreatePostingMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
		CreatePostingMessage(const CreatePostingMessage& other);
		virtual CreatePostingMessage& operator=(const CreatePostingMessage& rhs);
	    virtual ~CreatePostingMessage();
		unsigned long int getBoardIDThatThePostingBelongsTo();
		const Posting getPosting();
	protected:
		//
	private:
		unsigned long int boardIDThatThePostingBelongsTo;
		Posting* thePosting;
};

#endif
