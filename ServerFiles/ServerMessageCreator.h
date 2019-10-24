#ifndef SERVER_MESSAGE_CREATOR_H
#define SERVER_MESSAGE_CREATOR_H

#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"

class ServerMessageCreator
{
  public:
    ServerMessageCreator();
  protected:
    //
  private:
    Message createPostingDataMessage(Posting postingToConvertToMessage);
}

#endif
