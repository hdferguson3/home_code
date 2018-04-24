#include <stdio.h>
#include <wiringPi.h>

int main (void)
{
	wiringPiSetup ();
	pinMode (0, OUTPUT) ;

	digitalWrite (0, HIGH) ;
	digitalWrite (1, LOW);
	delay (10000);
	digitalWrite (0, LOW);
	digitalWrite (1, LOW);

	return(0);
}
