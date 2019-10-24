#ifndef SERVER_MESSAGE_CREATOR_H
#define SERVER_MESSAGE_CREATOR_H

#include "../CommonFiles/MessageCodes.h"

public class ServerMessageCreator
{
  public:
    ServerMessageCreator();
  protected:
    //
  private:
    Message convertToLoginMessage(std::string username, std::string password);
    Message convertTo
}

#endif
