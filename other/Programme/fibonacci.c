/****************************************************************/
/*** Caluclates Fibonacci numbers                             ***/
/*** Rechnergestütztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>

/** calculates Fibonacci number of 'n' dynamically **/
double fib_dynamic(int n)
{
  double *fib, result;
  int t;
  if(n<=2)                                  /* simple case ? */
    return(1);                     /* return result directly */
  fib = (double *) malloc(n*sizeof(double));
  fib[1] = 1.0;                  /* initialise known results */
  fib[2] = 1.0;

  for(t=3; t<n; t++)       /* calculate intermediate results */
    fib[t]=fib[t-1]+fib[t-2];

  result = fib[n-1]+fib[n-2];
  free(fib);
  return(result);
}

int main(int argc, char *argv[])
{
  int n;

  n = atoi(argv[1]);
  printf("fib(%d)=%e\n", n, fib_dynamic(n)); 
  return(0);
}
