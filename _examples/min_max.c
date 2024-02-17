/*******************************************************************/
/*** Advanced example for using functions:                       ***/
/*** Calculate minimum and maximum of set of numbers             ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Functions                                          ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/** contains the minimum and maximum number of a set of numbers **/
typedef struct
{
  double min;
  double max;
} minmax_t;


/******************* min_max() *******************/
/** Calculates the minimum and maximum of an    **/
/** array of numbers                            **/
/**                                             **/
/** Parameters: (*) = return parameter          **/
/**         x: array of numbers                 **/
/**       num: number of elements in array      **/
/**                                             **/
/** Returns:                                    **/
/**       minimum and maximum                   **/
/*************************************************/
minmax_t minmax(double x[], int num)
{
  int i;
  minmax_t mm;

  mm.min = x[0];
  mm.max = x[0];

  for(i=1; i<num; i++)
  {
    if(x[i] < mm.min)
      mm.min = x[i];
    if(x[i] > mm.max)
      mm.max = x[i];
  }

  return(mm);
}

/******************* min_max() *******************/
/** Calculates the minimum and maximum of an    **/
/** array of numbers                            **/
/**                                             **/
/** Parameters: (*) = return parameter          **/
/**         x: array of numbers                 **/
/**       num: number of elements in array      **/
/** (*) p_min: pointer to variable for minimum  **/
/** (*) p_max: pointer to variable for maximum  **/
/** Returns:                                    **/
/**       (nothing)                             **/
/*************************************************/
void minmax2(double x[], int num, double *p_min, double *p_max)
{
  int i;
  double min_value, max_value;

  min_value = x[0];
  max_value = x[0];

  for(i=1; i<num; i++)
  {
    if(x[i] < min_value)
      min_value = x[i];
    if(x[i] > max_value)
      max_value = x[i];
  }
  *p_min = min_value;
  *p_max = max_value;
}




int main()
{
  int num = 100, i;
  double x[num];
  minmax_t mm;
  double x_min, x_max;

  for(i=0; i<100; i++)
    x[i] = sin(M_PI*(i+20.0)/100.0);

  /*mm = minmax(x, num);
    printf("min=%f, max=%f\n", mm.min, mm.max); */

  minmax2(x, num, &x_min, &x_max);
  printf("min=%f, max=%f\n", x_min, x_max); 


  return(0);
}

