#ifndef CLIENT_BASIC_MESSAGES_H
#define CLIENT_BASIC_MESSAGES_H

#include "../../Message.h"

class ClientBasicMessage: public Message
{
  public:
    ClientBasicMessage();
  protected:
    //
  private:
    //
}

#include "ClientBasicMessages/CreatePostingImageMessage.h"
#include "ClientBasicMessages/CreatePostingMessage.h"
#include "ClientBasicMessages/LoginMessage.h"
#include "ClientBasicMessages/LogoutMessage.h"
#include "ClientBasicMessages/SendUserMessageImageMessage.h"
#include "ClientBasicMessages/SendUserMessageMessage.h"

#endif
