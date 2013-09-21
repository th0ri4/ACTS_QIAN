#include <stdarg.h>
#include <stdio.h>
#include "Log.h"

static void Open()
{
	openlog("ACTS", LOG_CONS, 0);  
}


static void Close()
{
	closelog();
}


static void TransAction(const char *format, ...)
{
	va_list ap;
	char szLogMsg[1024];

	if (!format) return; 
	va_start(ap, format);
	vsprintf(szLogMsg, format, ap);
	va_end(ap);

	syslog(LOG_TRANSACTION, szLogMsg);
}


static void Debug(const char *format, ...)
{
	va_list ap;
	char szLogMsg[1024];

	if (!format) return; 
	va_start(ap, format);
	vsprintf(szLogMsg, format, ap);
	va_end(ap);

	syslog(LOG_ACTS_DEBUG, szLogMsg);
}
