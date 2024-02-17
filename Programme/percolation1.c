/****************************************************************/
/*** Simulates d-dim percolation                              ***/
/*** A.K. Hartmann June 2004                                  ***/
/*** Rechnergestütztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stacks.h"
#include "percol.h"


int main(int argc, char *argv[])
{
  int dim;                    /* dimension of system */
  int num_n;    /* number of neighbours of each site */
  int *l;                         /* sizes of system */
  int *next;           /* stores neighbours of sites */
  int t, r;                         /* loop counters */
  int N;                          /* number of sites */
  double prob;           /* probability of occ. site */
  short int *site;     /* site is occupied or empty? */
  int *cluster;           /* cluster id of each site */
  int num_clusters;             /* numb. of clusters */
  double *value;                   /* stores results */
  double mean;                       /* final result */
  int run, num_runs; /* cur., max no. of indep. runs */
  int id_largest;           /* id of largest cluster */

  dim = 2;            /* initialization + parameters */
  num_n = 2*dim;                   /* simple lattice */
  l = (int *) malloc(dim*sizeof(int));

  if(argc<4)
  {
    printf("USAGE %s <L> <p> <num_runs>\n", argv[0]);
    printf("   (prints cluster if <num_runs>=1)\n");
    exit(1);
  }
  l[0] = atoi(argv[1]);
  for(r=1; r<dim; r++)
    l[r] = l[0];
  next = percol_init_next(dim, l, &N);

  /*for(t=1; t<=N; t++)
    for(r=0; r<2*dim; r++)
    printf("NEXT(%d,%d)=%d\n",t, r, NEXT(t,r));
  exit(1);*/
  site = (short int *) malloc((N+1)*sizeof(short int));
  cluster = (int *) malloc((N+1)*sizeof(int));
  sscanf(argv[2], "%lf", &prob); 
  num_runs = atoi(argv[3]);
  value = (double *) malloc(num_runs*sizeof(double));

  for(run=0; run<num_runs; run++)
  {
    for(t=1; t<=N; t++)
      if(drand48() < prob)
	site[t] = 1;
      else
	site[t] = 0;

    num_clusters = percol_cluster(num_n, N, next, site, cluster);
    value[run] = (double )percol_largest(N, num_clusters, cluster, 
      &id_largest)/N;
    /* UNCOMMENT NEXT LINE FOR SPANNING PROBABILITY EXERCISE */
    /*value[run] = (double) percol_spanning(N, cluster, id_largest, l[0]);*/

    /* UNCOMMENT NEXT LINE FOR SURFACE SIZE EXERCISE */
    value[run] = (double) percol_surface(num_n, N, next, num_clusters,
      cluster, id_largest);

    if(num_runs == 1)
      for(t=1; t<=N; t++)          
      {
	if(site[t] == 1)
	  printf("%3d", cluster[t]);
	else
	  printf("   ");
	if( ((t-1)%l[0]) == (l[0]-1) ) 
	  printf("\n");
      }

  }
  mean = percol_analysis(num_runs, value);
  printf("%f %f %d \n", prob, mean, l[0]);

  

  free(value);
  free(cluster);
  free(site);
  free(next);
  free(l);
  return(0);
}
