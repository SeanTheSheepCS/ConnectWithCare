#ifndef SERVER_MESSAGE_CONVERTER_H
#define SERVER_MESSAGE_CONVERTER_H

#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"

class ServerMessageConverter
{
  public:
    ServerMessageConverter();
  protected:
    //
  private:
    Message convertToPostingDataMessage(Posting postingToConvertToMessage);
}

#endif
