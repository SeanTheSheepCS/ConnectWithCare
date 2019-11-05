#ifndef POSTING_H
#define POSTING_H

#include "Date.h"
#include <string>
#include <ctime>

using namespace std;

class Posting
{
	private:
		string postText; //the contents of the post
		Date* dateTimePosted;//date;
	public:
		Posting(std::string postText, Date datePosted);
		~Posting();
		void setPostText(string text);
		string getPostText();
		void setDateTimePosted(time_t dateTime);
		string getDateTimePosted();
};

#endif
