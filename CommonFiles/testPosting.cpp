#include "Posting.h"
#include "Date.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

int mainTP()
{
  Date date = Date(2019, 11, 05, 8978);
  Posting post = Posting(string("HI"), date);

  post.setPostText("Hello this is the text in the post.");
  string text = post.getPostText();
  cout << "test 1 (text): " << text << endl;

  string dateToPrint = date.toString();
  cout <<"test 2 (date): " << dateToPrint << endl;
  
  return 0;
}
