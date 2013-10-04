#if !defined(ACTSMESSAGE_H)
#define ACTSMESSAGE_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

namespace acts
{

#define MAGIC     = 0x41435453	// ACTS
#define VERSION   = 0x1;

#define MSG_REVERSED		= 0
#define MSG_LOGON			= 1
#define MSG_LOGON_RESPONSE	= 2
#define MSG_LOGOUT			= 3
#define MSG_LOGOUT_RESPONSE	= 4


#define MSG_DELIMITER		= "_ACTS_DELIMITER";

typedef struct CMsgHeader
{
    int magic;
    int version;
    int length;
    int msg_type;
}__attribute__((packed));

struct CMsgLogin
{
	///ÓÃ»§´úÂë
    char user_id[13];
    union
    {
        struct
        {
            char password[41];
            char _unused[10];
        }reqest;
        char response[51];
    }un;
	char delimiter[16];
}__attribute__((packed));

struct CMsgLogout
{
    char user_id[13];
    union
    {
        char _unused[51];
        char response[51];
    }un;
	char delimiter[16];
}__attribute__((packed));

}
#endif
