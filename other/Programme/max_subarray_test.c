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

/****************************************************************/
/** calculates for array 'a' in the range [from'..'to']        **/
/** the largest subarray (sum of elements)                     **/
/****************************************************************/
sub_array_t max_subarray(int *a, int from, int to)
{
  sub_array_t sa1, sa2, sa3, final;
  int middle;
  
  middle = floor((from+to)/2);

  /** COMPLETE FUNCTION */

  if(to == from)                                     /* just one element */
  {
	  final.left = from;
	  final.right = to;
	  final.sum = a[from];
  }
  else
  {
	  int *a1, *a2, t;
	  a1 = (int *) malloc((middle-from+1)*sizeof(int));
	  a2 = (int *) malloc((to-middle)*sizeof(int));
	  for(t=0; t<(middle-from+1); t++)                           /* copy data */
	      a1[t] = a[t];   
	  for(t=0; t<(to-middle); t++)
	      a2[t] = a[t+(middle-from+1)];
	  sa1 = max_subarray(a1, from, middle);
	  sa2 = max_subarray(a2, middle+1, to);
	  sa1 = max_crossing_subarray(a, from, middle, to);
  }

  if ((sa1.sum >= sa2.sum) && (sa1.sum >= sa3.sum))
  {
	  final.left = sa1.left;
	  final.right = sa1.right;
	  final.sum = sa1.sum;
  }
  if ((sa2.sum >= sa1.sum) && (sa2.sum >= sa3.sum))
  {
	  final.left = sa1.left;
	  final.right = sa1.right;
	  final.sum = sa1.sum;
  }
  if ((sa3.sum >= sa2.sum) && (sa3.sum >= sa2.sum))
  {
	  final.left = sa1.left;
	  final.right = sa1.right;
	  final.sum = sa1.sum;
  }
  
  return(final);

}

int main(int argc, char **argv)
{
  int length = 7;                                     /* length of array */
  int a[7] = {1,2,3,4,1,2,-3};                       /* array with numbers */                          
  sub_array_t best;                                   /* best subarray */

  best = max_subarray(a, 0, length-1);
  printf("%d\n", best.left);
  printf("%d\n", best.right);
  printf("%d\n", best.sum);
}
