
#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include "/home/pi/temp_humidity/get_file_name.h"
#include "/home/pi/temp_humidity/check_time.h"
#include "/home/pi/temp_humidity/get_date_time.h"
#define MAXTIMINGS	85
#define DHTPIN		7

int dht11_dat[5] = { 0, 0, 0, 0, 0 };
int data_state = 0;	//Keep track of failed data reads
 
void read_dht11_dat()
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	float	f;

	FILE *fp; // File Pointer

 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	pinMode( DHTPIN, INPUT );
 
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
 
		if ( counter == 255 )
			break;
 
		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
 
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		f = dht11_dat[2] * 9. / 5. + 32;
		get_date_time();
		printf( "%s -- Humidity = %d.%d %% Temperature = %d.%d C (%.1f F)\n", current_time, dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3], f );
		get_file_name();
		if (NULL == (fp = fopen(filepath, "a")));
		fprintf(fp, "%s,%d.%d,%d.%d\n", current_time, dht11_dat[0], dht11_dat[1], dht11_dat[2], dht11_dat[3]);
		fclose(fp);
		data_state = 0;
	}else  {
		data_state = 1;
	}
}
 
int main( void )
{
	printf( "Raspberry Pi wiringPi DHT11 Temperature test program\n" );
 
	if ( wiringPiSetup() == -1 )
		printf("Exiting due to WiringPi failure....\n");
		//exit( 1 );
 
	while ( 1 )
	{
		read_dht11_dat();
		//printf("data state is %d\n", data_state);
		if (data_state == 0)
		{
			//printf("Checking timer function...\n");
			check_timer();
		}
		else
		{
			//printf("Delay for 2 seconds...\n");
			delay ( 2000 );
		}
	}
 
	return(0);
}
