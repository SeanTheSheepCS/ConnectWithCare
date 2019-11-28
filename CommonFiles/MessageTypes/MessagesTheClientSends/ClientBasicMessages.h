#ifndef CLIENT_BASIC_MESSAGES_H
#define CLIENT_BASIC_MESSAGES_H

#include "../../Message.h"

class ClientBasicMessage: public Message
{
  public:
    ClientBasicMessage(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
    ClientBasicMessage(const ClientBasicMessage& other);
    virtual ClientBasicMessage& operator=(const ClientBasicMessage& rhs);
    virtual ~ClientBasicMessage();
  protected:
    unsigned char getMessageCode();
    unsigned long int getDataLengthInBytes();
    unsigned long int getIndexOfFirstData();
  private:
    unsigned char messageCode;
    unsigned long int dataLengthInBytes;
    unsigned long int indexOfFirstData;
};

#include "ClientBasicMessages/CreatePostingJPEGImageMessage.h"
#include "ClientBasicMessages/CreatePostingMessage.h"
#include "ClientBasicMessages/LoginMessage.h"
#include "ClientBasicMessages/LogoutMessage.h"
#include "ClientBasicMessages/SendUserMessageJPEGImageMessage.h"
#include "ClientBasicMessages/SendUserMessageMessage.h"

#endif
