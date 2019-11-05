#include "Posting.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

Posting::Posting(std::string postText, Date datePosted)
{
	this->postText = postText;
	this->dateTimePosted = new Date(datePosted.getYear(), datePosted.getMonth(), datePosted.getDay(), datePosted.getSeconds());
}

void Posting::setPostText(string text)
{
	postText = text;
}

string Posting::getPostText()
{
	return postText;
}

Posting::~Posting()
{
	delete dateTimePosted;
}

//void Posting::setDateTimePosted(time_t now) //pass in current time. Gets converted to a string.
//{
//	char* dt = ctime(&now);
//	dateTimePosted = dt;
//}
