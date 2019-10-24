#ifndef CLIENT_MESSAGE_CONVERTER_H
#define CLIENT_MESSAGE_CONVERTER_H

#include "../CommonFiles/MessageCodes.h"

public class ClientMessageConverter
{
  public:
    ClientMessageConverter();
  protected:
    //
  private:
    Message convertToLoginMessage(std::string username, std::string password);
}

#endif
