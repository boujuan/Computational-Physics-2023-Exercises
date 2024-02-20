/*******************************************************************/
/*** Examples for how to read in a file:                        ***/
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
  char line[1000];    /* string where one line of file is stored */
  double val1, val2, val3, val4;             /* values from file */
  int num_got;     /* how many where obtained from current line? */
  FILE *file_p;                                  /* file pointer */

  file_p = fopen("funcs.dat", "r");     /* open file for reading */

  while(!feof(file_p))      /* read until end of file is reached */
  {
    if(fgets(line, 999, file_p) == NULL)         /* read in line */
      continue;                           /* nothing was read in */
    if(line[0] == '#')                          /* comment line? */ 
      continue;                                        /* ignore */
    num_got = sscanf(line, "%lf %lf %lf %lf",      /* get values */ 
		      &val1, &val2, &val3, &val4);
    if(num_got != 4)                          /* everything OK ? */
    {
      fprintf(stderr, "wrong line format in line: %s ", line);
      continue;
    }
    printf("%f result= %f\n", val1, 
	   val2+val3+val4); /* process */
  }
  fclose(file_p);                                  /* close file */

  return(0);
}
