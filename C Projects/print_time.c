#include <stdio.h>
#include <time.h>

int main(void)
{

	time_t rawtime;
	struct tm * timeinfo;

	time ( &rawtime );
	timeinfo = localtime ( &rawtime );

	printf("Current time is %s\n", asctime (timeinfo) );

return(0);
}
