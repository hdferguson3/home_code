#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <wiringPi.h>
#include "sunrise.h"
#include <syslog.h>

char sys_time[6];
char wake_time[6]; // time to open door
char sleep_time[6]; // time to close door
int w;
int s;

void get_time()
{
	time_t rawtime;
	struct tm* time_;

	time(&rawtime);
	time_ = localtime(&rawtime);

	// construct time as hour:minute wo seconds

	sprintf (sys_time, "%02d:%02d", time_->tm_hour, time_->tm_min);
	//printf("System time is %s\n\n", sys_time);

	get_sunrise_sunset();
	strcpy(wake_time,wake_open);
	strcpy(sleep_time,sleep_close);
	//printf("Wake time is %s, Sleep time is %s\n", wake_time, sleep_time);
	//openlog ("Coup Door", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	//syslog (LOG_INFO, "Systime %s, Wake Time %s, Sleep Time %s", sys_time,wake_time,sleep_time);
	//closelog();
}

int main(void)
{
	printf ("Starting door_main\n");
	openlog ("Coup Door", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
	syslog (LOG_INFO, "Coup Door program start...");
	closelog ();
	wiringPiSetup ();
	pinMode (4, OUTPUT); pinMode (5, OUTPUT); //Sets pins to output
	digitalWrite (4, LOW); digitalWrite (5, LOW); //initializes to off

	while(1)
	{
		get_time(); //execute subroutine 
		w = strcmp(sys_time,wake_time); // see if time equals wake time
		s = strcmp(sys_time,sleep_time); // see if time equals sleep time

		if (w == 0) //do if wake time
		{
			printf ("Door opened at %s\n", sys_time);
			openlog ("Coup Door", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
        		syslog (LOG_INFO, "Door Open");
        		closelog ();
			digitalWrite (4, HIGH); digitalWrite (5, HIGH); // Sets forward motion
			sleep (30);
			digitalWrite (4, LOW); digitalWrite (5, LOW);; //sets motor to off
			sleep (30); //sleep an additional amount of time to not trigger twice on the minute
		}
		if (s == 0) //do if sleep time
		{
			digitalWrite (4, HIGH); digitalWrite (5, LOW); // Sets reverse motion
			printf ("Door closed at %s\n", sys_time);
			openlog ("Coup Door", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
        		syslog (LOG_INFO, "Door Close");
        		closelog ();
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
