#include <stdio.h>
#include <time.h>

int main (void)
{
	char current_time[80];
	time_t rawtime;
	struct tm *info;
	time( &rawtime );
	info = localtime ( &rawtime );
	strftime(current_time,80, "%x %X", info);
	printf("Timestamp is %s\n", current_time);
	return(0);
}
