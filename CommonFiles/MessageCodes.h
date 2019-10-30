#ifndef MESSAGE_CODES_H
#define MESSAGE_CODES_H

enum ServerMessageCode   {SERVERMESSAGECODE_LOGINAUTH = 0x00,
                          SERVERMESSAGECODE_LOGOUTCONFIRM = 0x01,
                          SERVERMESSAGECODE_MESSAGEDATA = 0x10,
                          SERVERMESSAGECODE_MESSAGEIMGDATA = 0x11,
                          SERVERMESSAGECODE_POSTINGDATA = 0x12,
                          SERVERMESSAGECODE_POSTINGIMGDATA = 0x13,
                          SERVERMESSAGECODE_ASKCLIENTTOREQUESTMESSAGEINFO = 0x20, //TWO REALLY COOL MESSAGES TO IMPLEMENT IF
                          SERVERMESSAGECODE_ASKCLIENTTOREQUESTBOARDINFO = 0x21,   //WE HAVE SOME EXTRA TIME    - Sean
                          SERVERMESSAGECODE_ERRORNOAUTH = 0xF0,
                          SERVERMESSAGECODE_ERRORUSERNOTFOUND = 0xF1,
                          SERVERMESSAGECODE_ERRORBOARDNOTFOUND = 0xF2,
                          SERVERMESSAGECODE_ERRORWRITEFAILED = 0xF4,
                          SERVERMESSAGECODE_WRITESUCCESSFUL = 0xFE,
                          SERVERMESSAGECODE_ENDOFDATA = 0xFF
                        };

enum ClientMessageCode   {CLIENTMESSAGECODE_LOGIN = 0xB0,
                          CLIENTMESSAGECODE_LOGOUT = 0xB1,
                          CLIENTMESSAGECODE_CREATEPOST = 0xB2,
                          CLIENTMESSAGECODE_CREATEPOSTIMG = 0xB3,
                          CLIENTMESSAGECODE_SENDMESSAGE = 0xB4,
                          CLIENTMESSAGECODE_SENDMESSAGEIMG = 0xB5,
                          CLIENTMESSAGECODE_MESSAGEHISTORY = 0xC0,
                          CLIENTMESSAGECODE_MESSAGEHISTALL = 0xC1,
                          CLIENTMESSAGECODE_BOARDHISTORY = 0xC2,
                          CLIENTMESSAGECODE_BOARDSEARCH = 0xC3,
                        };

#endif
