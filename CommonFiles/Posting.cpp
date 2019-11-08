#include "Posting.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

Posting::Posting(std::string postText, string usernameOfTheUserWhoCreatedThisPost, Date datePosted)
{
	this->postText = postText;
	this->usernameOfTheUserWhoCreatedThisPost = usernameOfTheUserWhoCreatedThisPost;
	this->dateTimePosted = new Date(datePosted.getYear(), datePosted.getMonth(), datePosted.getDay(), datePosted.getSeconds());
}

Posting::Posting(const Posting& other)
{
	this->postText = other.postText;
	this->usernameOfTheUserWhoCreatedThisPost = other.usernameOfTheUserWhoCreatedThisPost;
	this->dateTimePosted = new Date(other.dateTimePosted->getYear(), other.dateTimePosted->getMonth(), other.dateTimePosted->getDay(), other.dateTimePosted->getSeconds());
}

Posting& Posting::operator=(const Posting& rhs)
{
	if(this != &rhs)
	{
		this->postText = rhs.postText;
		this->usernameOfTheUserWhoCreatedThisPost = rhs.usernameOfTheUserWhoCreatedThisPost;
		this->dateTimePosted = new Date(rhs.dateTimePosted->getYear(), rhs.dateTimePosted->getMonth(), rhs.dateTimePosted->getDay(), rhs.dateTimePosted->getSeconds());
	}
	return *this;
}

void Posting::setPostText(string text)
{
	postText = text;
}

string Posting::getPostText() const
{
	return postText;
}

string Posting::getUsernameOfUserWhoCreatedThisPost() const
{
	return usernameOfTheUserWhoCreatedThisPost;
}

Posting::~Posting()
{
	delete dateTimePosted;
}

Date Posting::getDateTimePosted() const
{
	return *dateTimePosted;
}

//void Posting::setDateTimePosted(time_t now) //pass in current time. Gets converted to a string.
//{
//	char* dt = ctime(&now);
//	dateTimePosted = dt;
//}
