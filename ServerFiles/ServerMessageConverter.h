#ifndef SERVER_MESSAGE_CONVERTER_H
#define SERVER_MESSAGE_CONVERTER_H

#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"

class ServerMessageConverter
{
  public:
    ServerMessageConverter();
    bool isALoginMessage(Message messageToDetermineTypeOf);
    bool isALogoutMessage(Message messageToDetermineTypeOf);
    bool isACreatePostingMessage(Message messageToDetermineTypeOf);
    bool isACreatePostingImageMessage(Message messageToDetermineTypeOf);
    bool isASendUserMessageMessage(Message messageToDetermineTypeOf);
    bool isASendUserMessageImageMessage(Message messageToDetermineTypeOf);
    bool isAMessageHistoryMessage(Message messageToDetermineTypeOf);
    bool isAMessageHistoryAllMessage(Message messageToDetermineTypeOf);
    bool isABoardHistoryAllMessage(Message messageToDetermineTypeOf);
    bool isABoardSearchMessage(Message messageToDetermineTypeOf);
  protected:
    //
  private:
    //
}

#endif
