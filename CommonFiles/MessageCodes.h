#ifndef MESSAGE_CODES_H
#define MESSAGE_CODES_H

enum ServerMessageCode = {SERVERMESSAGECODE_LOGINAUTH = 0x00,
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

enum ClientMessageCode = {CLIENTMESSAGECODE_LOGIN = 0x00,
                          CLIENTMESSAGECODE_LOGOUT = 0x01,
                          CLIENTMESSAGECODE_CREATEPOST = 0x02,
                          CLIENTMESSAGECODE_CREATEPOSTIMG = 0x03,
                          CLIENTMESSAGECODE_SENDMESSAGE = 0x04,
                          CLIENTMESSAGECODE_SENDMESSAGEIMG = 0x05,
                          CLIENTMESSAGECODE_MESSAGEHISTORY = 0x10,
                          CLIENTMESSAGECODE_MESSAGEHISTALL = 0x11,
                          CLIENTMESSAGECODE_BOARDHISTORY = 0x12,
                          CLIENTMESSAGECODE_BOARDSEARCH = 0x13,
                        };

#endif
