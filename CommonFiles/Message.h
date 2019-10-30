#ifndef MESSAGE_H
#define MESSAGE_H

class Message
{
  public:
    Message(unsigned long int lengthArg, unsigned char* messageAsCharArrayArg);
    Message(const Message& other);
    virtual Message& operator=(const Message& rhs);
    virtual ~Message();
    unsigned long int getLength();
    const unsigned char* getMessageAsCharArray();
  protected:
    //
  private:
    unsigned long int length;
    const unsigned char* messageAsCharArray;
};

#endif
