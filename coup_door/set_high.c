#include <stdio.h>
#include <wiringPi.h>

int main (void)
{
	wiringPiSetup ();
	pinMode (4, OUTPUT);
	pinMode (5, OUTPUT);
	digitalWrite (4, HIGH);
	digitalWrite (5, HIGH);
	return (0);
}
