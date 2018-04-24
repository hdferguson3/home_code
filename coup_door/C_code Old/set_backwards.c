#include <stdio.h>
#include <wiringPi.h>

int main (void)
{
	wiringPiSetup ();
	pinMode (4, OUTPUT); pinMode (5, OUTPUT); // Sets mode to output
	digitalWrite (4, HIGH); digitalWrite (5, HIGH); //Sets to backwards rotation or negative polarity

	return (0);
}
