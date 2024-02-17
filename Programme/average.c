#include <stdio.h>

/** calculate average of numbers given in array **/
double calc_average(int number, double value[])
{
	int counter;
	double sum;
	sum = 0.0;
	for(counter=0; counter<number; counter++)
		sum += value[counter];
	return(sum/number);
}

int main()
{
	int counter;
	double value[10];
	double average;
	
	for(counter=0; counter<10; counter++)
		value[counter]=counter*counter;
	
	average = calc_average(9, value);
	printf("average=%f\n", average);
}