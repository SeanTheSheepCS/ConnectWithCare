#ifndef MESSAGE_H
#define MESSAGE_H

#include "Utilities/VariableLengthQuantityLibrary.h"
#include <string>

class Message
{
  public:
	Message(const unsigned long int lengthArg, const unsigned char* messageAsCharArrayArg);
    Message(const Message& other);
    virtual Message& operator=(const Message& rhs);
    virtual ~Message();
    unsigned long int getLength() const;
    const unsigned char* getMessageAsCharArray() const;
    void printMessageToStdOut() const;
  protected:
    VariableLengthQuantityConverter vlqConverter;
  private:
    unsigned long int length;
    unsigned char* messageAsCharArray;
};

#endif
