#include <stdio.h>
#include <time.h>
#include "check_time.h"

int take_data=0;

int check_timer ()
{

	while (take_data == 0)
	{
		sleep (60);
		char current_time[4];
		time_t rawtime;
		struct tm *info;
		time( &rawtime );
		info = localtime ( &rawtime );
		strftime(current_time,4, "%M", info);
		int minutes = atoi(current_time);
		//printf("Take data? %d\n", take_data);
		if (minutes == 0)
		{
			break;
		}else
		{
			take_data = 0;
		}
	}
}
