#ifndef MESSAGE_CODES_H
#define MESSAGE_CODES_H

enum ServerMessageCode = {SERVERMESSAGECODE_LOGINAUTH = 0x00,
                          SERVERMESSAGECODE_LOGOUTCONFIRM = 0x01,
                          SERVERMESSAGECODE_LOGOUTCONFIRM_MESSAGEDATA = 0x10,
                          SERVERMESSAGECODE_LOGOUTCONFIRM_MESSAGEIMGDATA = 0x11,
                          SERVERMESSAGECODE_LOGOUTCONFIRM_POSTINGDATA = 0x12,
                          SERVERMESSAGECODE_POSTINGIMGDATA = 0x13,
                          SERVERMESSAGECODE_ERRORNOAUTH = 0xF0,
                          SERVERMESSAGECODE_ERRORUSERNOTFOUND = 0xF1,
                          SERVERMESSAGECODE_ERRORBOARDNOTFOUND = 0xF2,
                          SERVERMESSAGECODE_ERRORWRITEFAILED = 0xF4,
                          SERVERMESSAGECODE_WRITESUCCESSFUL = 0xFE,
                          SERVERMESSAGECODE_ENDOFDATA = 0xFF
                        }

enum ClientMessageCode = {}

#endif
