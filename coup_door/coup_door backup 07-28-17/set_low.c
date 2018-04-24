#include <stdio.h>
#include <wiringPi.h>

int main (void)
{
	wiringPiSetup ();
	pinMode (4, OUTPUT);
	pinMode (5, OUTPUT);
	digitalWrite (4, LOW);
	digitalWrite (5, LOW);
	return (0);
}
