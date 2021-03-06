#ifndef CLIENT_MESSAGE_CREATOR_H
#define CLIENT_MESSAGE_CREATOR_H

#include <iostream>
#include "../CommonFiles/MessageCodes.h"
#include "../CommonFiles/Message.h"
#include "../CommonFiles/UserMessages/UserMessage.h"
#include "../CommonFiles/AllMessageTypes.h"
#include "../CommonFiles/Postings/Posting.h"
#include "../CommonFiles/MultimediaComponentLibrary/MultimediaComponents/AllMultimediaComponents.h"
#include "../CommonFiles/Utilities/VariableLengthQuantityLibrary.h"

class ClientMessageCreator
{
  public:
    ClientMessageCreator();
    LoginMessage createLoginMessage(std::string username, std::string password);
    LogoutMessage createLogoutMessage();
    CreatePostingMessage createCreatePostingMessage(unsigned long int boardIDToPostTo, Posting postToConvertToMessage);
#if 0
    Message createCreatePostingImageMessage(PostingImage postToConvertToMessage);
#endif
    SendUserMessageMessage createSendUserMessageMessage(UserMessage userMessageToConvertToMessage);
    SendUserMessageJPEGImageMessage createSendUserMessageJPEGImageMessage(UserMessage userMessageToConvertToUserMessageWithAJPEGImage, std::vector<MultimediaComponent> multimediaComponents);
    UserMessageHistoryMessage createUserMessageHistoryMessage(Date startDate, Date endDate, std::string usernameWhoseHistoryWithYouYouWantToGet);
    UserMessageHistoryAllMessage createUserMessageHistoryAllMessage(Date startDate, Date endDate);
    BoardHistoryMessage createBoardHistoryMessage(Date startDate, Date endDate, unsigned long int boardID);
    BoardSearchMessage createBoardSearchMessage(Date startDate, Date endDate, long int boardID, std::string searchKeyWord);
  protected:
    //
  private:
    VariableLengthQuantityConverter vlqConverter;
};

#endif
