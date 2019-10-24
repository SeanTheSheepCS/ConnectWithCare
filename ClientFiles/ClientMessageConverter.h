#ifndef CLIENT_MESSAGE_CONVERTER_H
#define CLIENT_MESSAGE_CONVERTER_H

#include "../CommonFiles/MessageCodes.h"

class ClientMessageConverter
{
  public:
    ClientMessageConverter();
    bool isLoginAuthMessage(Message messageToDetermineTypeOf);
    bool isLogoutConfirmMessage(Message messageToDetermineTypeOf);
    bool isMessageDataMessage(Message messageToDetermineTypeOf);
    bool isMessageImageDataMessage(Message messageToDetermineTypeOf);
    bool isPostingDataMessage(Message messageToDetermineTypeOf);
    bool isPostingImageDataMessage(Message messageToDetermineTypeOf);
    bool isErrorNoAuthMessage(Message messageToDetermineTypeOf);
    bool isErrorUserNotFoundMessage(Message messageToDetermineTypeOf);
    bool isErrorBoardNotFoundMessage(Message messageToDetermineTypeOf);
    bool isErrorWriteFailedMessage(Message messageToDetermineTypeOf);
    bool isWriteSuccessfulMessage(Message messageToDetermineTypeOf);
    bool isEndOfDataMessage(Message messageToDetermineTypeOf);
  protected:
    //
  private:
}

#endif
