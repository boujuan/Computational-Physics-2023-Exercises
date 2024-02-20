#include <stdio.h>
#include <stdlib.h>

struct employee
{
	int id;
	char name;
	int position[3]; /* Gebäude, Stockwerk, Zimmer */	
};

void give_position(struct employee *employees, int num_employees)
{
	int counter;
		
	for(counter=0; counter<num_employees; counter++)
	{
		employees[counter].position[0] = counter*1;
		employees[counter].position[1] = counter*2;
		employees[counter].position[2] = counter*3;
	}
	
}

int main()
{
	// struct employee *employees;
	struct employee employees[10];
	int num_employees;
	int size_array;
	
	num_employees = 10;
	
	// employees = (struct employee *) malloc(num_employees*sizeof(struct employee));
	give_position(employees, num_employees);
	
	size_array = sizeof(employees)/sizeof(employees[0]);
	printf("Size: %d, Position: %d\n", size_array, employees[1].position[0]);
	
	// free(employees);
	return(0);
}