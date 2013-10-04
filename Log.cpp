#include <stdarg.h>
#include <stdio.h>
#include "Log.h"

namespace acts
{

void CLog::Open()
{
    openlog("ACTS", LOG_CONS, 0);
    Log::Debug("Open debug log");
    Log::TransAction("Open transaction log");
}


void CLog::Close()
{
    Log::Debug("Close debug log");
    Log::TransAction("Close transaction log");
    closelog();
}


void CLog::TransAction(const char *format, ...)
{
    va_list ap;
    char logmsg[1024];

    if (!format) return;
    va_start(ap, format);
    vsprintf(logmsg, format, ap);
    va_end(ap);

    syslog(LOG_TRANSACTION, logmsg);
}


void CLog::Debug(const char *format, ...)
{
    va_list ap;
    char logmsg[1024];

    if (!format) return;
    va_start(ap, format);
    vsprintf(logmsg, format, ap);
    va_end(ap);

    syslog(LOG_DEBUG, logmsg);
}

}
