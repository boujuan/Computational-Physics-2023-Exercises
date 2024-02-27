/****************************************************************/
/*** Simulates d-dim percolation                              ***/
/*** A.K. Hartmann June 2004                                  ***/
/*** Rechnergest�tztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "stacks.h"
#include "percol.h"

// TODO: 3 .function, checks whether a cluster spans the system
/******************* percol_spanning() *******************/
/** Determines whether cluster ’cluster_ID’ occupies    **/
/** for each x ordinate at least one site.              **/
/** For each site, in ’cluster[i]’ the ID of the        **/
/** cluster (starting at 0) is stored                   **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             N: number of sites                      **/
/**       cluster: ID of clusters sites are contained in**/
/**    cluster_ID: ID of the cluster which is tested    **/
/**       x_length: length of system in x direction     **/
/** RETURNS:                                            **/
/**1 if all x values are occpied (<->spanning)          **/
/********************************************************/
int percol_spanning(int N, int* cluster, int cluster_ID, int x_length) {
  int* x_occupied = (int*) malloc(x_length * sizeof(int)); // Array to store if x is occupied by cluster
  int i, x;

  // Initialize the array to zero (no x is occupied by default)
  for (i = 0; i < x_length; i++) {
    x_occupied[i] = 0;
  }

  for (i = 1; i <= N; i++) { // Check if site is in cluster, N is the number of sites (Cluster ID starts at 1)
    if (cluster[i] == cluster_ID) { // Does the site belong to the cluster?
      x = (i - 1) % x_length; // If it does, calculate the x coordinate
      x_occupied[x] = 1; // And set it to occupied
    }
  }

  for (x = 0; x < x_length; x++) { // Check if all x values are occupied
    if (x_occupied[x] == 0) { // If x is not occupied, free memory and return 0
      free(x_occupied);
      return 0;
    }
  }

  free(x_occupied);
  return 1;
}

int main(int argc, char *argv[]) // arguments: L (size of system), p (probability of occupation), num_runs (number of independent runs)
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
    /* TODO: 2 UNCOMMENT NEXT LINE FOR SPANNING PROBABILITY EXERCISE */
    value[run] = (double) percol_spanning(N, cluster, id_largest, l[0]);

    // Testing output
    // if (value[run] == 1.0) {
    // printf("The cluster with ID %d is spanning.\n", id_largest);
    // } else {
    //     printf("The cluster with ID %d is not spanning.\n", id_largest);
    // }

    /* UNCOMMENT NEXT LINE FOR SURFACE SIZE EXERCISE */
    // TODO: 1 Comment this unused function
    // value[run] = (double) percol_surface(num_n, N, next, num_clusters,
    //   cluster, id_largest);

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
  printf("%f %f %d \n", prob, mean, l[0]); // Prints the probability, the P and the size of the system

  free(value);
  free(cluster);
  free(site);
  free(next);
  free(l);
  return(0);
}
