#include <string>
# include <ctime>

using namespace std;

class Posting
{
	private:
		string postText; //the contents of the post
		string dateTimePosted;//date;
	public:
		void setPostText(string text);
		string getPostText();
		void set dateTimePosted(string dateTime);
`		string getDateTimePosted();
};
