/*******************************************************************/
/*** Calculates all permutations of a given array of numbers     ***/
/*** using a recursive approach                                  ***/
/*** Makes a simple statistics of the permutations               ***/
/***                                                             ***/
/*** Based on sample programs from the book:                     ***/
/*** A.K. Hartmann                                               ***/
/*** Big practical guide to computer simulation                  ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Iteration and recursion                            ***/
/*******************************************************************/

#include <stdio.h>
#include <stdlib.h>


/********************** count_up() *************************/
/** Counts how often an array element is followed by a     **/
/** larger element.                                       **/
/**                                                       **/
/** Parameters: (*) = return parameter                    **/
/**        n_max: size of array                           **/
/**            a: array                                   **/
/** Returns:                                              **/
/**        number of 'up' pairs                           **/
/***********************************************************/
int count_up(int n_max, int *a)
{
  int t;
  int count = 0;

  /*** ADD CODE HERE ***/
  // Create a loop that goes through the array and counts the number of 'up' pairs
  for(t=0; t<n_max-1; t++)
    if(a[t] < a[t+1])
      count++;
    /*** END ***/
  
  return(count);
}


/******************* permutation() *************************/
/** Obtains all permutations of positions 0..n-1 of a     **/
/** given array 'a' of numbers and prints them if n==1,   **/
/** including the higher index entries (from 0..n_max-1). **/
/** Also a statistics on the permutations regarding       **/
/** 'up_count()' is performed                             **/
/**                                                       **/
/** Parameters: (*) = return parameter                    **/
/**            n: current range                           **/
/**        n_max: size of array                           **/
/**            a: array                                   **/
/**      (*)  up: pointer to total number of 'up' pairs   **/
/**      (*) num: pointer to number of permutations       **/
/** Returns:                                              **/
/**        (nothing)                                      **/
/***********************************************************/
void permutation(int n, int n_max, int *a, double *up, double *num)
{
  int t;
  int exch;

  if(n==1)                                       /* print solution */
  {

    /*** ADD CODE HERE ***/
    // When n==1 print permutation and update up and num.
    for(t=0; t<n_max; t++)
      printf("%d ", a[t]);
    printf("\n");
    
    *up += count_up(n_max, a);
    *num += 1;
  }
  else
    /*** ADD CODE HERE ***/
    // Create a loop that goes through the array and calls permutation() recursively
    for(t=0; t<n; t++)
    {
      // Swap
      exch = a[t];
      a[t] = a[n-1];
      a[n-1] = exch;

      permutation(n-1, n_max, a, up, num);

      // Swap back
      exch = a[t];
      a[t] = a[n-1];
      a[n-1] = exch;
    }
         
}

/*******************************************************************/
/**                m a i n    p r o g r a m                       **/
/*******************************************************************/
int main(int argc, char **argv)
{
  int n;            /* number of which factorial is to be computed */    
  int *a;                                     /* array for numbers */
  int t;                                           /* loop counter */
  double up;    /* number of 'up' pairs, summed over all sequences */
  double num;                            /* number of permutations */
  n = atoi(argv[1]);             /* n= first command line argument */
//   n = 3;
  a = malloc(n*sizeof(int));
  for(t=0; t<n; t++)
    a[t]=t+1;
  up = 0.0; num = 0.0;
  permutation(n, n, a, &up, &num);

  printf("n=%d, %f sequences <up>=%f\n", n, num, up/num);
  free(a);
  return(0);
}
