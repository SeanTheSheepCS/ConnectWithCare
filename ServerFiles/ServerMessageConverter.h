#ifndef SERVER_MESSAGE_CONVERTER_H
#define SERVER_MESSAGE_CONVERTER_H

#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/UserMessage.h"
#include "../CommonFiles/AllMessageTypes.h"

class ServerMessageConverter
{
  public:
    ServerMessageConverter();

    bool isALoginMessage(Message messageToDetermineTypeOf);
    LoginMessage toLoginMessage(Message messageToTurnIntoALoginMessage); //ONLY CALL ME IF ISALOGINMESSAGE WAS TRUE!
#if 0
    bool isALogoutMessage(Message messageToDetermineTypeOf);
    LogoutMessage toLogoutMessage(Message messageToTurnIntoALogoutMessage); //ONLY CALL ME IF ISALOGOUTMESSAGE WAS TRUE!

    bool isACreatePostingMessage(Message messageToDetermineTypeOf);
    CreatePostingMessage toCreatePostingMessage(Message messageToTurnIntoACreatePostingMessage); //ONLY CALL ME IF IS A CREATEPOSTINGMESSAGE WAS TRUE!

    bool isACreatePostingImageMessage(Message messageToDetermineTypeOf);
    CreatePostingImageMessage toCreatePostingImageMessage(Message messageToTurnIntoACreatePostingImageMessage); //THIS AND ALL BELOW FOLLOW ABOVE RULES.

    bool isASendUserMessageMessage(Message messageToDetermineTypeOf);
    SendUserMessageMessage toSendUserMessageMessage(Message messageToTurnIntoASendUserMessageMessage);

    bool isASendUserMessageImageMessage(Message messageToDetermineTypeOf);
    SendUserMessageImageMessage toSendUserMessageImageMessage(Message messageToTurnIntoASendUserMessageImageMessage);

    bool isAUserMessageHistoryMessage(Message messageToDetermineTypeOf);
    UserMessageHistoryMessage toUserMessageHistoryMessage(Message messageToTurnIntoAUserMessageHistoryMessage);

    bool isAMessageHistoryAllMessage(Message messageToDetermineTypeOf);
    UserMessageHistoryAllMessage toUserMessageHistoryAllMessage(Message messageToTurnIntoAUserMessageHistoryAllMessage);

    bool isABoardHistoryMessage(Message messageToDetermineTypeOf);
    BoardHistoryMessage toBoardHistoryMessage(Message messageToTurnIntoABoardHistoryMessage);

    bool isABoardSearchMessage(Message messageToDetermineTypeOf);
    BoardSearchMessage toBoardSearchMessage(Message messageToTurnIntoABoardSearchMessage);
#endif
  protected:
    //
  private:
    //
};

#endif
