#ifndef CLIENT_MESSAGE_CONVERTER_H
#define CLIENT_MESSAGE_CONVERTER_H

#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/UserMessage.h"
#include "../CommonFiles/AllMessageTypes.h"
#include "../CommonFiles/Utilities/VariableLengthQuantityLibrary.h"

class ClientMessageConverter
{
  public:
    ClientMessageConverter();

    bool isLoginAuthMessage(Message messageToDetermineTypeOf);
    LoginAuthMessage toLoginAuthMessage(Message messageToTurnIntoALoginAuthMessage); //ONLY TO BE CALLED IF ISLOGINAUTHMESSAGE RETURNED TRUE!

    bool isLogoutConfirmMessage(Message messageToDetermineTypeOf);
    LogoutConfirmMessage toLogoutConfirmMessage(Message messageToTurnIntoALogoutConfirmMessage); //ONLY TO BE CALLED IF ISLOGOUTCONFIRMMESSAGE RETURNED TRUE!
#if 0
    bool isUserMessageDataMessage(Message messageToDetermineTypeOf);
    UserMessageDataMessage toUserMessageDataMessage(Message messageToTurnIntoAUserMessageDataMessage); //ONLY TO BE CALLED IF ISUSERMESSAGEDATAMESSAGE RETURNED TRUE!

    bool isUserMessageImageDataMessage(Message messageToDetermineTypeOf);
    UserMessageImageDataMessage toUserMessageImageDataMessage(Message messageToTurnIntoAUserMessageImageDataMessage); //THIS AND ALL BELOW FOLLOW SAME RESTRICTION WITH THE FUNCTION ABOVE THEM.
#endif
    bool isPostingDataMessage(Message messageToDetermineTypeOf);
    PostingDataMessage toPostingDataMessage(Message messageToTurnIntoPostingDataMessage);
#if 0
    bool isPostingImageDataMessage(Message messageToDetermineTypeOf);
    PostingImageDataMessage toPostingImageDataMessage(Message messageToTurnIntoPostingImageDataMessage);
#endif
    bool isErrorNoAuthMessage(Message messageToDetermineTypeOf);
    ErrorNoAuthMessage toErrorNoAuthMessage(Message messageToTurnIntoAnErrorNoAuthMessage);

    bool isErrorUserNotFoundMessage(Message messageToDetermineTypeOf);
    ErrorUserNotFoundMessage toErrorUserNotFoundMessage(Message messageToTurnIntoAUserNotFoundMessage);

    bool isErrorBoardNotFoundMessage(Message messageToDetermineTypeOf);
    ErrorBoardNotFoundMessage toErrorBoardNotFoundMessage(Message messageToTurnIntoAnErrorBoardNotFoundMessage);

    bool isErrorWriteFailedMessage(Message messageToDetermineTypeOf);
    ErrorWriteFailedMessage toErrorWriteFailedMessage(Message messageToTurnIntoAnErrorWriteFailedMessage);

    bool isWriteSuccessfulMessage(Message messageToDetermineTypeOf);
    WriteSuccessfulMessage toWriteSuccessfulMessage(Message messageToTurnIntoAWriteSuccessfulMessage);

    bool isEndOfDataMessage(Message messageToDetermineTypeOf);
    EndOfDataMessage toEndOfDataMessage(Message messageToTurnIntoAnEndOfDataMessage);
  protected:
    //
  private:
    VariableLengthQuantityConverter vlqConverter;
};

#endif
