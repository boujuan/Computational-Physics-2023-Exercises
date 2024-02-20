/*******************************************************************/
/*** Sets up a simple data structure and calculates it size      ***/
/*** (solution to exercise)                                      ***/
/***                                                             ***/
/*** Compile: cc -o struct_size struct_size.c                    ***/
/*** Run: struct_size                                            ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Exercises                                          ***/
/*******************************************************************/

#include <stdio.h>

typedef struct
{
  char          type;     /* type of amino acid, e.g., 'A' */
  int         charge;     /* in units of electrons         */
  double position[3];     /* in space */
  double velocity[3];     /* in space */
} amino_acid_t;

int main()
{
  printf("size of amino acid data structure: %lu bytes\n", 
	 sizeof(amino_acid_t));
  printf("sum of single variable sizes: %lu bytes\n", 
	 sizeof(char) + sizeof(int) + 6*sizeof(double) );

  return(0);
}


