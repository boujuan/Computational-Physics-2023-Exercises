#include <stdio.h>

int main()
{
	int counter;
	double value[10];
	
	for(counter=0; counter<10; counter++)
	{
		value[counter]=3*counter+0.2;
		printf("value[%d]=%f\n", counter, value[counter]);
	}
	
	return(0);
}