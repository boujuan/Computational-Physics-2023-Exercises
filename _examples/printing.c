/*******************************************************************/
/*** Advanced examples for using printf():                       ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Input/Output                                       ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>


int main(int argc, char**argv)
{
  int counter = 777;
  double energy1 = 35678.99;
  void *pointer = &energy1;
  char name[100] = {"network"};

  printf("After %d (hex:%x) iterations an energy of %f \n"
         "(%e, stored at %p) was obtained for %s\n", 
	 counter, counter, energy1, energy1, pointer, name);
  printf("%06d, %4.3f, %-20s, %lf\n", 
	 45, 3.14159265358979, "Hello", 36.5);

  return(0);
}
