#include "Posting.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

Posting::Posting()
{
	postText = "";
	dateTimePosted = "";
}

string Posting::getPostText()
{
	return dateTimePosted;
}

void Posting::setPostText(string text)
{
	postText = text;
}

string Posting::getPostText()
{
	return postText;
}

void Posting::setDateTimePosted(time_t now) //pass in current time. Gets converted to a string.
{
	char* dt = ctime(&now);
	dateTimePosted = dt;
}

