#include <stdio.h>

int main(void)
{
	int i, numberOfNums=0, total=0, valuesRead, value;
	float average;

	valuesRead = scanf("%d",&value);
	while(valuesRead > 0) {
		if(value < 0) {
			valuesRead = scanf("%d",&value);
			continue;
		}
		numberOfNums++;
		total += value; // equivalent to total = total + value
		printf("Read %d\n",value);
		valuesRead = scanf("%d",&value);
	}

	average = (float)total / (float)numberOfNums;
	printf("You read %d values. Average = %f.\n", numberOfNums, average);

return(0);
}
