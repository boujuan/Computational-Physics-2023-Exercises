/*******************************************************************/
/*** Solves the N-queen problem and prints all solutions         ***/
/***                                                             ***/
/*** Sample programs from the book:                              ***/
/*** A.K. Hartmann                                               ***/
/*** A practical guide to computer simulation                    ***/
/*** World Scientific, Singapore 2008                            ***/
/***                                                             ***/
/*** Chapter: Algorithms and data structures                     ***/
/*** Section: Backtracking                                       ***/
/*******************************************************************/




#include <stdio.h>
#include <stdlib.h>

/******************************* queen() ***************************/
/** Places a queen in different rows of column                    **/
/** 'n' of checker board of size 'size'x'size'                    **/
/** Calls itself recursively to search for                        **/
/** solutions. If solution found, it is printed.                  **/
/**                                                               **/
/** PARAMETERS: (*)= return-paramter                              **/
/**          c: current column                                    **/
/**          N: size of board                                     **/
/**        pos: positions of queens in different columns          **/
/**        row: is there a queen in row y?                        **/
/**    diag_up: is there a queen in up diagonal ?                 **/
/**  diag-down: is there a queen in down diagonal ?               **/
/**                                                               **/
/** RETURNS:                                                      **/
/**    nothing                                                    **/
/*******************************************************************/
void queens(int c, int N, int *pos, int *row, 
            int *diag_up, int *diag_down)
{
  int r, c2;                                      /* loop counters */
  if(c == -1)                                  /* solution found ? */
  {
    for(c2=0; c2<N; c2++)               /* print solution "nicely" */
    {
      for(r=0; r<pos[c2]; r++)
	printf("*");
      printf("X");
      while((++r)<N)
	printf("*");
      printf("\n");
    }
    printf("----------------------\n");
    return;
  }
  for(r=N-1; r>=0; r--)        /* place queen in all rows of column c */
  {
    if(!row[r]&&!diag_up[c-r+(N-1)]&&!diag_down[c+r])  /*  place ? */
    {
      row[r] = 1; diag_up[c-r+(N-1)] = 1; diag_down[c+r] = 1;
      pos[c] = r;
      queens(c-1, N, pos, row, diag_up, diag_down);
      row[r] = 0; diag_up[c-r+(N-1)] = 0; diag_down[c+r] = 0;      
    }
  }
  pos[c] = 0;
}

int main(int argc, char *argv[])
{
  int N;                      /* size of checker board = parameter */
  int *pos;                   /* position of a queen in the column */
  int *row;                /* row[y] = is there a queen in row y ? */
  int *diag_up;  /* d[x-y+(N-1)] = a queen in diagonal x-y=const ? */
  int *diag_down;   /* d[x+y] = is a queen in diagonal x+y=const ? */
  int t;                                           /* loop counter */

  N = atoi(argv[1]);               /* size = command line argument */

  pos = (int *) malloc(N*sizeof(int));             /* alloc memory */
  row = (int *) malloc(N*sizeof(int));
  diag_up = (int *) malloc((2*N-1)*sizeof(int));
  diag_down = (int *) malloc((2*N-1)*sizeof(int));

  for(t=0; t<N; t++)                  /* initialise arrays = empty */
  {
    pos[t] = 0; row[t] = 0;
  }
  for(t=0; t<2*N-1; t++)
  {
    diag_up[t] = 0; diag_down[t] = 0;
  }

  queens(N-1, N, pos, row, diag_up, diag_down);         /* do work */

  free(row); free(pos); free(diag_up); free(diag_down);
  return(0);
}
