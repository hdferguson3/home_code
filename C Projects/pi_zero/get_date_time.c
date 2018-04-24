#include <stdio.h>
#include <time.h>
#include "get_date_time.h"

char current_time[80];

int get_date_time ()
{
        time_t rawtime;
        struct tm *info;
        time( &rawtime );
        info = localtime ( &rawtime );
        strftime(current_time,80, "%x %X", info);;
}

