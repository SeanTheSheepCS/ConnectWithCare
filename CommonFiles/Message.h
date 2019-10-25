#ifndef MESSAGE_H
#define MESSAGE_H

class Message
{
  public:
    Message(long int lengthArg, char* messageAsCharArrayArg);
    Message(const Message& other);
    Message& operator=(const Message& rhs);
    ~Message();
    long int getLength();
    const char* getMessageAsCharArray();
  protected:
    //
  private:
    long int length;
    char* messageAsCharArray;
};

#endif
