/****************************************************************/
/*** Main program for undirected graphs                       ***/
/*** A.K. Hartmann January 2008                               ***/
/*** Forgeschrittene Computersimulationen                     ***/
/*** University of Oldenburg, Germany 2008                    ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"
#include "graphs_lists.h"


int main(int argc, char **argv)
{
  int num_nodes;                               /* number of nodes in graph */
  int num_edges;                               /* number of edges in graph */
  double c;                                        /* average connectivity */
  gs_graph_t *g;
  int *size;                                            /* of each cluster */
  double largest;                                          /* largest size */
  int *id;                             /* for each node, id of its cluster */
  int num_cl;                                        /* number of clusters */
  int t, cl;                                              /* loop counters */
  int num_real;                                  /* number of realizations */
  int argz = 1;                     /* for treating command line arguments */
  double size0, size1, size2,size4;  
                                  /* moments of sizes of largest component */
  int num_percol;

  num_real = 10000;
  num_nodes = atoi(argv[argz++]);                  /* read number of nodes */

  g = gs_create_graph(num_nodes);
  id = (int *) malloc(num_nodes*sizeof(int));
  /*gs_insert_edge(g, 0, 5);
  gs_insert_edge(g, 5, 7);
  gs_insert_edge(g, 7, 0);
  gs_insert_edge(g, 3, 8);
  gs_write_graph(g, stdout);
  */
  
  /** measure degree distribution; for testing **/
  c = 0.5;
  num_edges = (int) floor(c*num_nodes/2.0+0.5);
  double count[20];
  for(t=0; t<20; t++)
    count[t] = 0;
  for(t=0; t<num_real; t++)
  {
    gs_clear_graph(g);                      
    gs_random_graph(g, num_edges);
    for(cl=0; cl<num_nodes; cl++)
      count[gs_degree(g, cl)]++;
  }
  for(t=0; t<20; t++)
    printf("%d %e\n", t, count[t]/(num_nodes*num_real));
  exit(1);
  
  

  for(c=0.2; c<2.0; c+=0.05)         /* loop over different connectivities */
  {
    size0=0.0; size1=0.0; size2=0.0; size4=0.0;        /* reset statistics */
    num_percol = 0;
    num_edges = (int) floor(c*num_nodes/2.0+0.5);
    for(t=0; t<num_real; t++)
    {
      gs_clear_graph(g);                          /* generate random graph */
      gs_random_graph(g, num_edges);
      size = gs_clusters(g, id, &num_cl);
      largest=size[0];                       /* look for largest component */
      for(cl=1; cl<num_cl; cl++)
	if(size[cl] > largest)
	  largest = size[cl];
      size0++;                                            /* do statistics */
      largest /= num_nodes;
      if(largest > 0.3)      /* very "cheap" (wrong) percolation criterion */
	num_percol++;
      size1 += largest;
      largest = largest*largest;
      size2 += largest;
      largest = largest*largest;
      size4 += largest;
      free(size);
    }
    printf("%f %f %f %f  %f %d %d\n", c, size1/size0, 
	   sqrt( (size2/size0-size1*size1/(size0*size0))/num_real), 
	   0.5*(3-(size4)/(size2*size2/size0)), (double) num_percol/size0, 
	   num_nodes, num_edges);

  }

 
  gs_delete_graph(g);

  free(id);
  return(0);

}
