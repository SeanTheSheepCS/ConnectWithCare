#include "Posting.h"
#include <ctime>
#include <cstdlib>
#include <iostream>

using namespace std;

void main()
{
  Posting post = Posting();
  Date date = Date(2019, 11, 05, 8978);

  post.setPostText("Hello this is the text in the post.");
  string text = getPostText();
  printf("test 1 (text): " + text);

  string date = date.Print();
  printf("test 2 (date): " + date);
}
