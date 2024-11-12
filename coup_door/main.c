#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>
#include <syslog.h>
#include <wiringPi.h>
#include "sunrise.h"

int currentTime_seconds = 0;
int wakeTime_seconds = 0;
int sleepTime_seconds = 0;
bool doorState = false; // closed

int get_currentTime(void)
{
    // variables to store the date and time components
    int hours, minutes, seconds, day, month, year;

    // `time_t` is an arithmetic time type
    time_t now;

    // Obtain current time
    // `time()` returns the current time of the system as a `time_t` value
    time(&now);

    // Convert to local time format and print to stdout
    // localtime converts a `time_t` value to calendar time and
    // returns a pointer to a `tm` structure with its members
    // filled with the corresponding values
    struct tm *local = localtime(&now);

    hours = local->tm_hour;         // get hours since midnight (0-23)
    minutes = local->tm_min;        // get minutes passed after the hour (0-59)
    seconds = local->tm_sec;        // get seconds passed after a minute (0-59)

    day = local->tm_mday;            // get day of month (1 to 31)
    month = local->tm_mon + 1;      // get month of year (0 to 11)
    year = local->tm_year + 1900;   // get year since 1900

    // print local time
    if (hours < 12) {    // before midday
        printf("Time is %02d:%02d:%02d am, ", hours, minutes, seconds);
    }
    else {    // after midday
        printf("Time is %02d:%02d:%02d pm, ", hours - 12, minutes, seconds);
    }

    // print the current date
    printf("on %02d/%02d/%d.\n", day, month, year);

    return 0;
}


int main () {
   wiringPiSetup(); // Init wiringPi
   pinMode(4, OUTPUT); pinMode(5, OUTPUT); // Set pin modes
   printf("Starting Coup Door program.\n");
   printf("Close the door first, it might need to stay closed.\n");

   // Close the door first if open
   digitalWrite(4, HIGH); digitalWrite(5, LOW);
   sleep(30);
   digitalWrite(4, LOW); digitalWrite(5, LOW);
   doorState = false;

   printf("Let's get started...\n");
   if (doorState == false) {
      printf("Door state is closed.\n");
   }
   else {
      printf("Door state is open.\n");
   }
   openlog("Coup Door", LOG_CONS | LOG_PID | LOG_NDELAY, LOG_LOCAL1);
   syslog(LOG_INFO, "Coup Door program start...");
   closelog();

   while(1) {

      wakeTime_seconds = get_sunrise()-1800; //Offset to 30min before sunrise
      sleepTime_seconds = get_sunset()+2700; //Offset to 45min after sunset
      currentTime_seconds = get_current();
      if (currentTime_seconds-wakeTime_seconds >=0){
      printf("The last wake happend %d (seconds) ago. ", currentTime_seconds-wakeTime_seconds);
      }
      else {
         printf("The next wake is in %d (seconds). ", wakeTime_seconds-currentTime_seconds);
      }

      if (sleepTime_seconds-currentTime_seconds >=0){
      printf("The next sleep is in %d (seconds). ", sleepTime_seconds-currentTime_seconds);
      }
      else{
         printf("The last sleep happened %d (seconds) ago. ", -1*(sleepTime_seconds-currentTime_seconds));
      }
      get_currentTime();


      if (doorState == false && currentTime_seconds>wakeTime_seconds && (sleepTime_seconds-currentTime_seconds >= 0)) {
         // Open door
         printf("Opening door... ");
	 digitalWrite(4, HIGH); digitalWrite(5, HIGH); // Sets reverse mode to open door
         doorState = true; // Add feedback
         printf("Door is now open. ");
	 syslog(LOG_INFO, "Door opened");
	 closelog();
	 sleep(30); //delay to allow door to open
	 digitalWrite(4, LOW); digitalWrite(5, LOW); // sets motor off
         get_currentTime();
      }
      else if (doorState == true && currentTime_seconds>sleepTime_seconds) {
         // Close door
         printf("Closing door... ");
	 digitalWrite(4, HIGH); digitalWrite(5, LOW); // Sets forward mode to close door
         doorState = false; // Add feedback
         printf("Door is now closed. ");
	 syslog(LOG_INFO, "Door closed");
	 closelog();
	 sleep(30); // delay to allow door to close
	 digitalWrite(4, LOW); digitalWrite(5, LOW); // sets motor off
         get_currentTime();
      }
      else{
         sleep(600); // sleep for 10 minutes
      }
   }
   printf("Exiting of the program...\n");
   syslog(LOG_INFO, "Exiting Coup Door program...");

   return(0);
}
