#ifndef CLIENT_BASIC_MESSAGES_H
#define CLIENT_BASIC_MESSAGES_H

#include "../../Message.h"

class ClientBasicMessage: public Message
{
  public:
    ClientBasicMessage(Message messageToTurnIntoClientBasicMessage);
    ClientBasicMessage(const ClientBasicMessage& other);
    ClientBasicMessage& operator=(const ClientBasicMessage& rhs);
    virtual ~ClientBasicMessage();
  protected:
    unsigned char getMessageCode();
    unsigned long int getDataLengthInBytes();
    unsigned long int getIndexOfFirstData();
  private:
    unsigned char messageCode;
    unsigned long int dataLengthInBytes;
    unsigned long int indexOfFirstData
}

#include "ClientBasicMessages/CreatePostingImageMessage.h"
#include "ClientBasicMessages/CreatePostingMessage.h"
#include "ClientBasicMessages/LoginMessage.h"
#include "ClientBasicMessages/LogoutMessage.h"
#include "ClientBasicMessages/SendUserMessageImageMessage.h"
#include "ClientBasicMessages/SendUserMessageMessage.h"

#endif
