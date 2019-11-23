#ifndef SERVER_MESSAGE_CREATOR_H
#define SERVER_MESSAGE_CREATOR_H

#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/UserMessages/UserMessage.h"
#include "../CommonFiles/AllMessageTypes.h"
#include "../CommonFiles/Postings/Posting.h"

class ServerMessageCreator
{
  public:
    ServerMessageCreator();
    LoginAuthMessage createLoginAuthMessage(bool whetherTheLoginWasAccepted);
    LogoutConfirmMessage createLogoutConfirmMessage(bool whetherTheLogoutWasSuccessful);
    UserMessageDataMessage createUserMessageDataMessage(UserMessage userMessageToConvertToMessage);
#if 0
    Message createUserMessageImageDataMessage(UserMessageImage messageImageToConvertToMessage);
#endif
    PostingDataMessage createPostingDataMessage(Posting postingToConvertToMessage, unsigned long int boardIDThatThePostBelongsTo);
#if 0
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
