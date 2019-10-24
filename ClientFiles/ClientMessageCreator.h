#ifndef CLIENT_MESSAGE_CONVERTER_H
#define CLIENT_MESSAGE_CONVERTER_H

#include <iostream>
#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Posting.h"
#include "../CommonFiles/Message.h"

class ClientMessageCreator
{
  public:
    ClientMessageCreator();
    Message createLoginMessage(std::string username, std::string password);
    Message createLogoutMessage();
    Message createCreatePostMessage(Post postToConvertToMessage);
    Message createCreatePostImageMessage(PostImage postToConvertToMessage);
    Message createSendUserMessageMessage(UserMessage userMessageToConvertToMessage);
    Message createSendUserMessageImageMessage(UserImageMessage userImageMessageToConvertToMessage);
    Message createUserMessageHistoryMessage(Date startDate, Date endDate, std::string usernameWhoseHistoryWithYouYouWantToGet);
    Message createUserMessageHistoryAllMessage(Date startDate, Date endDate);
    Message createBoardHistoryMessage(Date startDate, Date endDate, long int boardID);
    Message createBoardSearchMessage(Date startDate, Date endDate, long int boardID, std::string searchKeyWord);
  protected:
    //
  private:
    //
}

#endif