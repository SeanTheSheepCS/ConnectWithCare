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
    bool isALoginMessage(Message messageToDetermineTypeOf);
    std::string getUsernameOfALoginMessage(Message loginMessageToGetUsernameFieldOf);
    std::string getPasswordOfALoginMessage(Message loginMessageToGetPasswordFieldOf);
    std::vector<std::string> getUsernameInFirstElementOfVectorAndPasswordInSecondElementOfVectorWhenYouPassInALoginMessage(Message loginMessageToGetUsernameAndPasswordFieldOf);

    bool isALogoutMessage(Message messageToDetermineTypeOf);

    bool isACreatePostingMessage(Message messageToDetermineTypeOf);
    Posting turnCreatePostingMessageIntoPosting(Message postingMessageToTurnIntoPosting);

    bool isACreatePostingImageMessage(Message messageToDetermineTypeOf);
    PostingImage turnCreatePostingImageMessageIntoPostingImage(Message postingImageMessageToTurnIntoPostingImage);

    bool isASendUserMessageMessage(Message messageToDetermineTypeOf);
    UserMessage turnSendUserMessageMessageIntoUserMessage(Message sendUserMessageToConvertToUserMessage);

    bool isASendUserMessageImageMessage(Message messageToDetermineTypeOf);
    UserMessageImage turnSendUserMessageImageMessageIntoUserMessageImage(Message sendUserMessageImageMessageToTurnIntoUserMessageImage);

    bool isAMessageHistoryMessage(Message messageToDetermineTypeOf);
    std::string getUsernamePortionOfTheMessageHistoryMessage(Message userHistoryMessageWhoseUsernameFieldWeWantToGet);

    bool isAMessageHistoryAllMessage(Message messageToDetermineTypeOf);

    bool isABoardHistoryAllMessage(Message messageToDetermineTypeOf);
    long int getTheBoardIDFieldOfABoardHistoryAllMessage(Message boardHistoryAllMessageToGetIDFieldFrom);

    bool isABoardSearchMessage(Message messageToDetermineTypeOf);
    std::string getKeywordOfBoardSearchMessage(Message boardSearchMessageToGetKeywordFieldOf);
    long int getTheBoardIDFieldOfABoardSearchMessage(Message boardSearchMessageToGetBoardIDFieldOf);
}

#endif
