#ifndef POSTING_H
#define POSTING_H

#include "../Date.h"
#include <string>
#include <ctime>

using namespace std;

class Posting
{
	private:
		string postText; //the contents of the post
		string usernameOfTheUserWhoCreatedThisPost;
		Date* dateTimePosted;//date;
	public:
		Posting(std::string postText, std::string usernameOfTheUserWhoCreatedThisPost, Date datePosted);
		Posting(const Posting& other);
		virtual Posting& operator=(const Posting& rhs);
		virtual ~Posting();
		void setPostText(string text);
		string getPostText() const;
		Date getDateTimePosted() const;
		string getUsernameOfUserWhoCreatedThisPost() const;

		bool operator<(const Posting& rhs) const;
};

#endif
