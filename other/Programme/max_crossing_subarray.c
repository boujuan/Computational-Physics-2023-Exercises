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
    sum += a[t];   /* COMPLETE HERE */
	if (sum > left_sum)
	{
		left_sum = sum;
		best.left = t;
	}
  }

  sum = 0;                                    /* treat right subarray */
  for(t=middle+1; t<= to; t++)
  {
    sum += a[t];   /* COMPLETE HERE */
	if (sum > right_sum)
	{
		right_sum = sum;
		best.right = t;
	}
  }

  /* COMPLETE HERE */

  best.sum = left_sum+right_sum;
  return(best);
}

int main(int argc, char **argv)
{
  int length = 7;                                     /* length of array */
  int a[7] = {1,2,3,4,1,-2,-3};                       /* array with numbers */                          
  sub_array_t best;                                   /* best subarray */

  best = max_crossing_subarray(a, 0, floor(length/2), length-1);
  printf("%d\n", best.left);
  printf("%d\n", best.right);
  printf("%d\n", best.sum);
}
