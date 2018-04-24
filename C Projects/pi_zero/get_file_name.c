#include <stdio.h>
#include <time.h>
#include <sys/stat.h>
#include <unistd.h>
#include "get_file_name.h"

char filepath[80];

int get_file_name(void)

{
	time_t rawtime;
	struct tm *info;
	char buffer[80];
	FILE *fp;

	time( &rawtime );

	info = localtime ( &rawtime );

	strftime(buffer,80,"%B_%Y", info);
	sprintf(filepath,"/mnt/temp_humidity_data/Metrology_Data/%s_DSC_environmental_data.csv", buffer );
	//printf("%s\n",filepath);

	fp = fopen(filepath, "a");
	if (fp){
		printf("%s\n", filepath);
		fclose(fp);
	}else{
		sprintf(filepath,"/home/pi/temp_humidity/data/%s_DSC_environmental_data.csv", buffer );
		fp = fopen(filepath, "a");
		if (fp){
			//chmod(filepath, S_IRWXU|S_IRWXG|S_IRWXO);
			printf("%s\n", filepath);
			fclose(fp);
		}else{
			printf("File crash\n");
		}
	}
}
