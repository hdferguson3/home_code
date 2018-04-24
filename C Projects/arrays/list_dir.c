#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
	char path[255] = "/home/pi/Documents/C\040Projects/arrays/Metrology_Data/";
	char list_array[20][255];  //declare array for file list, arbitrary used size of [20]
	int i = 0;
	DIR	*d;
	struct dirent *dir;
	d = opendir(path);

	if (d)
	{
		while ((dir = readdir(d)) !=NULL)
		{
			if( dir->d_name[0] == '.' )
   			{
				continue;
			}
			else
			{
				strcpy(list_array[i], dir->d_name);
				printf("%s\n", list_array[i]);
			}	i++;
		}
		closedir(d);
	}
	else
	{
		printf("Open error\n");
	}
	char buffer[1024] ;
   	char *record,*line;
   	int j=0,k=0;
   	int mat[100][100];
	strcat(path,list_array[0]);
   	FILE *fstream = fopen(path,"r");
   	if(fstream == NULL)
   	{
		printf("file opening failed \n");
      		return -1 ;
   	}
   	while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
   	{
     		record = strtok(line,",");
     		while(record != NULL)
     		{
     			printf("record : %s",record) ;    //here you can put the record into the array as per your requirement.
     			mat[j][k++] = atoi(record) ;
     			record = strtok(NULL,",");
     		}
      		++j ;
	}
	return(0);
}
