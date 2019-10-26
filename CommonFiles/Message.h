#ifndef MESSAGE_H
#define MESSAGE_H

class Message
{
  public:
    Message(unsigned long int lengthArg, unsigned char* messageAsCharArrayArg);
    Message(const Message& other);
    Message& operator=(const Message& rhs);
    ~Message();
    unsigned long int getLength();
    const unsigned char* getMessageAsCharArray();
  protected:
    //
  private:
    unsigned long int length;
    unsigned char* messageAsCharArray;
};

#endif
