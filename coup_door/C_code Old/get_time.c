#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

char sys_time[6];
char *wake_time = "5:0";
char *sleep_time = "21:30";
int w;
int s;

void get_time()
{
	time_t rawtime;
	struct tm* time_;

	time(&rawtime);
	time_ = localtime(&rawtime);

	sprintf (sys_time, "%i:%i", time_->tm_hour, time_->tm_min);
	//printf ("%s\n", sys_time);
}

int main(void)
{
	while(1)
	{
		get_time();
		w = strcmp(sys_time,wake_time);
		s = strcmp(sys_time,sleep_time);
		;
		if (w == 0)
		{
			printf ("Door opened at %s\n", sys_time);
			sleep (60);
		}
		if (s == 0)
		{
			printf ("Door closed at %s\n", sys_time);
			sleep (60);
		}
		else
		{
			sleep (60);
		}
	}
	return (0);
}
