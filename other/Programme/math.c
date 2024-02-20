#include <stdio.h>
#include <math.h>

int main()
{
	double argument;
	
	argument = 0.0;
	
	while(argument<2*M_PI)
	{
		printf("sin[%f]=%3.2f\n", argument, sin(argument));
		argument+= 0.1;
	}
	
	return(0);
}