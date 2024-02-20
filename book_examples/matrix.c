/*******************************************************************/
/*** Generates one permutation matrix, a test matrix, an         ***/
/*** multiplies both                                             ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Programming in C                                   ***/
/*** Section: Basic C programs                                   ***/
/*******************************************************************/

#include <stdio.h>

int main()
{
  int n=6,                    /* permutation matrix has size n x n */
    m=5;                             /* test matrix has size n x m */
  double perm[n][n], test[n][m], result[n][m];         /* matrices */
  int i, j, k;                  /* loop counters for rows, columns */
  


  for(i=0; i<n; i++)                        /* initialize matrices */
    {
      for(j=0; j<n; j++)
	if( j == (i+ 1-2*(i%2)) )  
	  perm[i][j] = 1.0;
	else
	  perm[i][j] = 0.0;
      for(k=0; k<m; k++)
	test[i][k] = (double) i;
    }

  for(i=0; i<n; i++)                          /* multiply matrices */
    for(k=0; k<m; k++)
    {
      result[i][k] = 0.0;
      for(j=0; j<n; j++)
	result[i][k] += perm[i][j]*test[j][k];
    }


  for(i=0; i<n; i++)                               /* print matrix */
  {
    for(k=0; k<m; k++)
      printf("%f ", result[i][k]);
    printf("\n");
  }

  return(0);
}
