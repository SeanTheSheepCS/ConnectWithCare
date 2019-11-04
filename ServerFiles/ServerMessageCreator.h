#ifndef SERVER_MESSAGE_CREATOR_H
#define SERVER_MESSAGE_CREATOR_H

#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/UserMessage.h"
#include "../CommonFiles/AllMessageTypes.h"

class ServerMessageCreator
{
  public:
    ServerMessageCreator();
    LoginAuthMessage createLoginAuthMessage(bool whetherTheLoginWasAccepted);
    LogoutConfirmMessage createLogoutConfirmMessage(bool whetherTheLogoutWasSuccessful);
#if 0
    Message createUserMessageDataMessage(UserMessage userMessageToConvertToMessage);
    Message createUserMessageImageDataMessage(UserMessageImage messageImageToConvertToMessage);
    Message createPostingDataMessage(Posting postingToConvertToMessage);
    Message createPostingImageDataMessage(PostingImage postingImageToConvertToMessage);
    //TWO MESSAGES TO IMPLEMENT LATER...
    //ASKCLIENTTOREQEUSTMESSAGEINFO FUNCTION GOES HERE
    //ASKCLIENTTOREQUESTBOARDINFO FUNCTION GOES HERE
#endif
    ErrorNoAuthMessage createErrorNoAuthMessage();
    ErrorUserNotFoundMessage createErrorUserNotFoundMessage();
    ErrorBoardNotFoundMessage createErrorBoardNotFoundMessage();
    ErrorWriteFailedMessage createErrorWriteFailedMessage();
    WriteSuccessfulMessage createWriteSuccessfulMessage();
    EndOfDataMessage createEndOfDataMessage();
  protected:
    //
  private:
    VariableLengthQuantityConverter vlqConverter;
};

#endif
