#if !defined(LOG_H)
#define LOG_H

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <syslog.h>

namespace acts
{

#define LOG_TRANSACTION		(LOG_LOCAL2|LOG_INFO)
#define LOG_DEBUG			(LOG_LOCAL2|LOG_DEBUG)

class CLog
{
public:
    static void Open();
    static void Close();
    static void TransAction(const char *format, ...);
    static void Debug(const char *format, ...);
};


}
#endif
