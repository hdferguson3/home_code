#include <stdio.h>
#include <wiringPi.h>


// Set Output A High, Output B Low - 24VDC Positive Polarity

int main (void)
{
	wiringPiSetup ();
	pinMode (4, OUTPUT);
	pinMode (5, OUTPUT);
	digitalWrite (4, HIGH); //Pin 2 (PWM HIGH)
	digitalWrite (5, LOW); //Pin 3 (DIR LOW)

	return (0);
}
