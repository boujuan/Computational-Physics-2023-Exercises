/****************************************************************/
/*** Mergsort                                                 ***/
/*** Introduction to Computational Physics                    ***/
/*** A.K. Hartmann                                            ***/
/*** Compile with cc -o mergesort mergesort.c                 ***/
/*** run with: mergesort <# of numbers>                       ***/
/*** Universities of Goettingen and Oldenburg, Germany 2004++ ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>

/** sorts 'n' integer numbers in the array 'a' in ascending **/
/** order using the mergsort algorithm                      **/
void my_mergesort(int n, int *a)
{
  int *b,*c;                                   /* two arrays */
  int n1, n2;                     /* sizes of the two arrays */
  int t, t1, t2;                          /* (loop) counters */

  if(n<=1)                          /* at most one element ? */
    return;                                 /* nothing to do */
  n1 = n/2; n2 = n-n1;               /* calculate half sizes */

  /* array a is distributed to b,c. Note: one could do it   */
  /* using one array alone, but yields less clear algorithm */
  b = (int *) malloc(n1*sizeof(int));
  c = (int *) malloc(n2*sizeof(int));
  for(t=0; t<n1; t++)                           /* copy data */
      b[t] = a[t];   
  for(t=0; t<n2; t++)
      c[t] = a[t+n1];

  my_mergesort(n1, b);               /* sort two smaller arrays */
  my_mergesort(n2, c); 

  t1 = 0; t2 = 0;     /* assemble solution from subsolutions */
  for(t=0; t<n; t++)
    if( ((t1<n1)&&(t2<n2)&&(b[t1]<c[t2]))||
	(t2==n2))
      a[t] = b[t1++];
    else
      a[t] = c[t2++];


  free(b); free(c);
}

int main(int argc, char *argv[])
{
  int n;                               /* number of elements */
  int t;                                     /* loop counter */
  int *a;                                /* array of numbers */

  n = atoi(argv[1]);         /* read from calling parameters */
  a = (int *) malloc(n*sizeof(int));

  for(t=0; t<n; t++)   /* assign random numbers + print them */
  {
    a[t] = (int) 10000*drand48();
    printf("%5d ", a[t]);
    if( (((t+1)%10)==0) || (t==n-1))
	printf("\n");
  }
  my_mergesort(n, a);                              /* sort them */
  for(t=0; t<n; t++)                           /* print them */
  {
    printf("%5d ", a[t]);
    if( (((t+1)%10)==0) || (t==n-1))
	printf("\n");
  }

  free(a);
  return(0);
}
