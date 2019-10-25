#include "Message.h"
#include <string.h>

Message::Message(long int lengthArg, char* messageAsCharArrayArg)
{
  length = lengthArg;
  strcpy(messageAsCharArray, messageAsCharArrayArg);
}
public long int getLength()
{
  return length
}

public const char* getMessageAsCharArray()
{
  return messageAsCharArray;
}
