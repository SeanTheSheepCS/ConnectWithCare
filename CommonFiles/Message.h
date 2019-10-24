#ifndef MESSAGE_H
#define MESSAGE_H

class Message
{
  public:
    public Message(long int length, char* messageAsCharArray);
    public long int getLength();
    public const char* getMessageAsCharArray();
  protected:
    //
  private:
    private long int length;
    private messageAsCharArray;
}

#endif
