#ifndef POSTING_H
#define POSTING_H

#include <string>
#include <ctime>

using namespace std;

class Posting
{
	private:
		string postText; //the contents of the post
		string dateTimePosted;//date;
	public:
		Posting();
		void setPostText(string text);
		string getPostText();
		void setDateTimePosted(time_t dateTime);
		string getDateTimePosted();
};

#endif
