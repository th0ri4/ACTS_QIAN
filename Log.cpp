#include <stdarg.h>
#include <stdio.h>
#include "Log.h"

void CLog::Open()
{
	openlog("ACTS", LOG_CONS, 0);
	CLog::Debug("Open debug log");
	CLog::TransAction("Open transaction log"); 
}


void CLog::Close()
{
	CLog::Debug("Close debug log");
	CLog::TransAction("Close transaction log"); 
	closelog();
}


void CLog::TransAction(const char *format, ...)
{
	va_list ap;
	char szLogMsg[1024];

	if (!format) return; 
	va_start(ap, format);
	vsprintf(szLogMsg, format, ap);
	va_end(ap);

	syslog(LOG_TRANSACTION, szLogMsg);
}


void CLog::Debug(const char *format, ...)
{
	va_list ap;
	char szLogMsg[1024];

	if (!format) return; 
	va_start(ap, format);
	vsprintf(szLogMsg, format, ap);
	va_end(ap);

	syslog(LOG_ACTS_DEBUG, szLogMsg);
}
