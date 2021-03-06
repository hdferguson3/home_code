#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>

char sys_time[6];
char *wake_time = "5:0"; // time to open door
char *sleep_time = "21:30"; // time to close door
int w;
int s;

void get_time()
{
	time_t rawtime;
	struct tm* time_;

	time(&rawtime);
	time_ = localtime(&rawtime);

	sprintf (sys_time, "%i:%i", time_->tm_hour, time_->tm_min); // contruct time as hour:minute wo seconds
}

int main(void)
{
	wiringPiSetup ();
	pinMode (4, OUTPUT); pinMode (5, OUTPUT); //Sets pins to output
	digitalWrite (4, LOW); digitalWrite (5, LOW); //initializes to off

	while(1)
	{
		get_time(); //execute subroutine 
		w = strcmp(sys_time,wake_time); // see if time equals wake time
		s = strcmp(sys_time,sleep_time); // see if time equals sleep time
		;
		if (w == 0) //do if wake time
		{
			printf ("Door opened at %s\n", sys_time);
			digitalWrite (4, HIGH); digitalWrite (5, LOW); // Sets forward motion
			sleep (30);
			digitalWrite (4, LOW); digitalWrite (5, LOW);; //sets motor to off
			sleep (30); //sleep an additional amount of time to not trigger twice on the minute
		}
		if (s == 0) //do if sleep time
		{
			digitalWrite (4, HIGH); digitalWrite (5, HIGH); // Sets reverse motion
			printf ("Door closed at %s\n", sys_time);
			sleep (30);
			digitalWrite (4, LOW); digitalWrite (5, LOW); // Sets motor off
			sleep (30); //sleep an additional amount of time to not trigger twice on the minute
		}
		else // wait until next minute to check time
		{
			sleep (60);
		}
	}
	return (0);
}
