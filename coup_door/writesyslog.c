#include <syslog.h>

int main(void)
{
	
	syslog (LOG_NOTICE, "door open");
	syslog (LOG_NOTICE, "door close");

	closelog ();

	return (0);
}
