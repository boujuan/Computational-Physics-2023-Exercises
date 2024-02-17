/*******************************************************************/
/*** Examples for how compiler optimization affects the          ***/
/*** running time of a program.                                  ***/
/*** For an array of numbers, all possible combinations of sums  ***/
/*** of these numbers are calculated.                            ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: exercises                                          ***/
/*******************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/****************** calc_sum() *******************/
/** Calculates sum of those value[i], where     **/
/** flag[i]=1                                   **/
/**                                             **/
/** Parameters: (*) = return parameter          **/
/**       num: number of values                 **/
/**      flag: which number to include          **/
/**     value: array of values                  **/
/** Returns:                                    **/
/**       sum                                   **/
/*************************************************/
double calc_sum(int num, short int *flag, double *value)
{ 
  int t;
  double sum = 0.0;

  for(t=0; t<num; t++)
    if(flag[t])
      sum += value[t];
  
  return(sum);
}


int main(int argc, char *argv[])
{
  int num=24;                                          /* number of values */
  double value[num];                       /* values to be added partially */
  int counter, counter2;                                  /* for main loop */
  int i;                            /* counter of different flag positions */ 
  short int flag[num];   /* tells whether a value should be (not) included */

  for(i=0; i<num; i++)
    value[i] = pow( i, 1.0);

  for(counter=0; counter<pow(2, num); counter++)  
  {                                /* loop over all possibles combinations */
    counter2=counter;
    for(i=0; i<num; i++)   /* translate counter into binary representation */
    {
      if(counter2%2 == 1)
	flag[i] = 1;
      else
	flag[i] = 0;
      counter2 /= 2;
    }
    
    calc_sum(num, flag, value);      /* perform sum over subset of numbers */
    /*printf("%d %f\n", counter, calc_sum(num, flag, value));*/

  }
  return(0);
}
