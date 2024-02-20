/************************************************************************/
/** max subset                                                         **/
/** A.K. Hartmann, University of Oldenburg February 2017               **/
/** Version 1.0.0.0                                                    **/
/** compile:  cc -o max_subarray max_subarray.c -Wall                  **/
/************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

/** a sub array ['left'...'right'] with value 'sum' **/
typedef struct
{
  int left;
  int right;
  int sum;
}
sub_array_t;

/****************************************************************/
/** calculates for array 'a' in the range [from'..'to']        **/
/** the largest subarray (sum of elements) CROSSING a[middle], **/
/** i.e.,which involves at least a[middle] and a[middle+1]     **/
/****************************************************************/
sub_array_t max_crossing_subarray(int *a, int from, int middle, int to)
{
  sub_array_t best;
  int left_sum = INT_MIN;                          /* best sum so far */
  int right_sum = INT_MIN;                         /* best sum so far */
  int sum;                                             /* current sum */
  int t;                                              /* loop counter */

  sum = 0;                                     /* treat left subarray */
  for(t=middle; t>= from; t--)
  {
    ;   /* COMPLETE HERE */
  }

  sum = 0;                                    /* treat right subarray */

  /* COMPLETE HERE */

  best.sum = left_sum+right_sum;
  return(best);
}


/****************************************************************/
/** calculates for array 'a' in the range [from'..'to']        **/
/** the largest subarray (sum of elements)                     **/
/****************************************************************/
sub_array_t max_subarray(int *a, int from, int to)
{
  sub_array_t sa1, sa2, sa3, final;
  int middle;

  /** COMPLETE FUNCTION */


  if(to == from)                                     /* just one element */
  {
     ;
  }



}

int main(int argc, char **argv)
{
  int length;                                       /* length of array */
  int *a;                                        /* array with numbers */
  int t;                                               /* loop counter */
  sub_array_t best;                                   /* best subarray */
  int run, num_runs;                    /* for averaging over disorder */
  double stat[3], avg[3], stat2[3], avg2[3];         /* for statistics */
         
  num_runs = 1000;

  if(argc == 2)
    length = atoi(argv[1]);   /* read length from arguments */
  else
    length = 20;
  a = malloc(length*sizeof(int));

  stat[0] = 0; stat[1] = 0; stat[2] = 0;
  stat2[0] = 0; stat2[1] = 0; stat2[2] = 0;
  for(run=0; run<num_runs; run++)    /* perform many independent simulations */
  {
    for(t=0; t<length; t++)                              /* initialize array */
      a[t] = (int) floor(40*drand48()) - 20;

    best = max_subarray(a, 0, length-1);
    /*for(t=0; t<length; t++)
      printf("%d:%d  ", t, a[t]);
    printf("\n");
    printf("Best [%d,%d] with sum=%d\n", best.left, best.right, best.sum); */
    stat[0]++;
    stat[1] += best.sum;
    stat[2] += best.sum*best.sum;
    stat2[0]++;
    stat2[1] += best.right-best.left+1;
    stat2[2] += (best.right-best.left+1)*(best.right-best.left+1);
  }


  avg[1] = stat[1] / stat[0];   /* print statistics */
  avg[2] = stat[2] / stat[0];
  avg2[1] = stat2[1] / stat2[0];
  avg2[2] = stat2[2] / stat2[0];
  printf("%d %f %f  %f %f \n", length, avg[1], 
	 sqrt( (avg[2]-avg[1]*avg[1])/(stat[0]-1) ),
	 avg2[1],  sqrt( (avg2[2]-avg2[1]*avg2[1])/(stat2[0]-1) ) );

  free(a);
  return(0);
}
