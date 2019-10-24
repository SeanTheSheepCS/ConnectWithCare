#ifndef CLIENT_MESSAGE_CONVERTER_H
#define CLIENT_MESSAGE_CONVERTER_H

#include <iostream>
#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"

class ClientMessageCreator
{
  public:
    ClientMessageCreator();
  protected:
    //
  private:
    Message createLoginMessage(std::string username, std::string password);
    Message createCreatePostMessage(Post postToConvertToMessage);
}

#endif
