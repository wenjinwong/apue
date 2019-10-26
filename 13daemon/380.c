#include<syslog.h>
#include<stdarg.h>

int 
main(void)
{
	openlog("lpd", LOG_PID, LOG_LPR);
	syslog(LOG_ERR, "open error for %s : %m",filename);
	syslog(LOG_ERR | LOG_LPR, "open error for %s: %m", filename);
#ifdef _USE_BSD
	vsyslog(LOG_URGE, "error for %s: %m", file);
}

