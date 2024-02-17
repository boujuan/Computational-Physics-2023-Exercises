/****************************************************************/
/*** Data structures and functions for undirected graphs      ***/
/*** A.K. Hartmann January 2008                               ***/
/*** Forgeschrittene Computersimulationen                     ***/
/*** University of Oldenburg, Germany 2008                    ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "list.h"
#include "graphs_lists.h"

/******************* gs_create_graph() ********************/
/** Creates a graph with a fixed number of nodes and    **/
/** no edges.                                           **/
/** PARAMETERS: (*)= return-paramter                    **/
/**      num_nodes: number of nodes                     **/
/** RETURNS:                                            **/
/**     pointer to created graph                        **/
/*********************************************************/
gs_graph_t *gs_create_graph(int num_nodes)
{
    gs_graph_t *g;
    int n;

    g = (gs_graph_t *) malloc(sizeof(gs_graph_t));  /* allocate */
    g->node = (gs_node_t *) malloc(num_nodes*sizeof(gs_node_t));

    g->num_nodes = num_nodes;                     /* initialise */
    for(n=0; n<num_nodes; n++)
	g->node[n].neighbors = NULL;

    return(g);
}



/******************* gs_insert_edge() ********************/
/** Insert undirected edge (from,to) into graph         **/
/** if the edge does not exists so far.                 **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/**      from, to: id of nodes                          **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_insert_edge(gs_graph_t *g, int from, int to)
{
    elem_t *elem1, *elem2;

    if(search_info(g->node[from].neighbors, to) != NULL)  /* edge exists? */
	return;

    elem1 = create_element(to);              /* create neighbor for 'from' */
    g->node[from].neighbors = 
	insert_element(g->node[from].neighbors, elem1, NULL);
    elem2 = create_element(from);              /* create neighbor for 'to' */
    g->node[to].neighbors =             
	insert_element(g->node[to].neighbors, elem2, NULL);
}


/******************* gs_edge_exists() ********************/
/** Tests whether undirected edge (from,to) in graph    **/
/** exists already.                                     **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/**      from, to: id of nodes                          **/
/** RETURNS:                                            **/
/**     1 if edge exists, 0 else                        **/
/*********************************************************/
int gs_edge_exists(gs_graph_t *g, int from, int to)
{
    if(search_info(g->node[from].neighbors, to) != NULL)  /* edge exists? */
      return(1);
    else
      return(0);
}

/******************* gs_clear_graph() ********************/
/** Removes all edges from graph                        **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_clear_graph(gs_graph_t *g)
{
  int n;
  elem_t *neighb;

  for(n=0; n<g->num_nodes; n++)          /* for all nodes */
  {
    while(g->node[n].neighbors !=0) 
    {                      /* remove all neighbor elements */
      neighb = g->node[n].neighbors;
      g->node[n].neighbors = 
	remove_element(g->node[n].neighbors, neighb);
      delete_element(neighb);
    }
  }
}

/******************* gs_clear_graph() ********************/
/** Deletes graph                                       **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_delete_graph(gs_graph_t *g)
{
  gs_clear_graph(g);
  free(g->node);
  free(g);
}

/************************ gs_degree() ********************/
/** Calculates number of neighbors of node              **/
/** PARAMETERS: (*)= return-paramter                    **/
/**             g: graph                                **/
/**             n: node                                 **/
/** RETURNS:                                            **/
/**     degree                                          **/
/*********************************************************/
int gs_degree(gs_graph_t *g, int n)
{
  int degree;
  elem_t *neighb;

  if(n >= g->num_nodes)
      return(0);
  degree = 0;
  neighb = g->node[n].neighbors;
  while(neighb != NULL)      /* go through all neighbors */
  {
    degree++;
    neighb = neighb->next;
  }
  return(degree);
}


/******************* gs_preferential_attachment() ********/
/** Generates graph bei "adding" one node after the     **/
/** other. For each "added" node, exactly m edges to    **/
/** already "old added" nodes are inserted randomly. The**/
/** probability that an "old added" nodes receives a new**/
/** edge is proportional to its current degree          **/ 
/** No self loops are allowed. No edge is allowed to    **/
/*+ appear twice!                                       **/
/** PARAMETERS: (*)= return-paramter                    **/
/**         (*) g: graph                                **/
/**             m: number of edges to be added          **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_preferential_attachment(gs_graph_t *g, int m)
{
  int t;
  int n1, n2;
  int *pick;            /* array which holds for each edge {n1,n2} */
                        /* the numbers n1 and n2. Used for picking */
                       /* nodes proportional to its current degree */
  int num_pick;              /* number of entries in 'pick' so far */
  int max_pick;                       /* maximum number of entries */

  if(g->num_nodes < m+1)
  {
      printf("graph too small to have at least %d edges per node!\n", m);
      exit(1);
  }
  max_pick = 2*m*g->num_nodes- m*(m+1);
  pick = (int *) malloc(max_pick*sizeof(int));
  num_pick=0;
  for(n1=0; n1<m+1; n1++) /* start: complete subgraph of m+1 nodes */

    for(n2=n1+1; n2<m+1; n2++)
    {
      gs_insert_edge(g, n1, n2);
      pick[num_pick++] = n1;
      pick[num_pick++] = n2;
    }

  for(n1=m+1; n1<g->num_nodes; n1++)            /* add other nodes */
  {
    t=0;
    while(t<m)                                   /* insert m edges */
    {
      do
        n2 = (int) pick[(int) floor(drand48()*num_pick)];
      while(n2==n1);              /* chose pair of different nodes */
      if(!gs_edge_exists(g, n1, n2))
      {
	gs_insert_edge(g, n1, n2);
	pick[num_pick++] = n1;
	pick[num_pick++] = n2;
	t++;
      }
    }
  }
  free(pick);
}


/******************* gs_random_graph() *******************/
/** Function adds exactly m randomly chosen edges to    **/
/** the graph.                                          **/
/** No self loops are allowed. No edge is allowed to    **/
/*+ appear twice!                                       **/
/** PARAMETERS: (*)= return-paramter                    **/
/**         (*) g: graph                                **/
/**             m: number of edges to be added per node **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_random_graph(gs_graph_t *g, int m)
{
  int t;
  int n1, n2;
  
  t = 0;
  while(t < m)                                /* insert m edges */
  {
    n1 = (int) floor(drand48()* g->num_nodes);
    do
      n2 = (int) floor(drand48()* g->num_nodes);
    while(n2==n1);
	if(!gs_edge_exists(g, n1, n2))
	{
		gs_insert_edge(g, n1, n2);
		t++;
	}		
  }
}

/******************** gs_block_model() ********************/
/** Generates graph according to stochastic block model. **/
/** Nodes are members of groups. For each pair of nodes  **/
/** an edge is addged with probability p1 if they are in **/
/** the same group, and with probability p2, if they are **/
/** in different groups.                                 **/
/** PARAMETERS: (*)= return-paramter                     **/
/**         (*) g: graph                                 **/
/**            p1: edge probability (same group)         **/
/**            p2: edge probability (different groups)   **/
/**         group: group ID for each node                **/
/** RETURNS:                                             **/
/**     (nothing)                                        **/
/*********************************************************/
void gs_block_model(gs_graph_t *g, double p1, double p2, int *group)
{
  int n1, n2;

    /* INSERT YOUR CODE HERE */;
  
}


/******************* gs_write_graph() ********************/
/** prints graph to 'file'                              **/
/** PARAMETERS: (*)= return-paramter                    **/
/**      g: graph                                       **/
/**   file: where to write (e.g. stdout)                **/
/** RETURNS:                                            **/
/**     (nothing)                                       **/
/*********************************************************/
void gs_write_graph(gs_graph_t *g, FILE *file)
{
    int n;

    for(n=0; n<g->num_nodes; n++)
    {
	fprintf(file, "node: %d, neigbors: ", n);
	write_list(g->node[n].neighbors, file);
    }
}

/************************ gs_clusters() *********************/
/** Calculates for graph  the connected components:        **/
/** An array is updated, where for each node the id        **/
/** (0,1,...,num_clusters-1) of the cluster it belongs to  **/
/** is stored. Also, an array is created an returend, where**/
/** for each cluster the number of nodes is contains is    **/
/** stored.                                                **/
/** PARAMETERS: (*)= return-paramter                       **/
/**            g: graph                                    **/
/**       (*) id: for each node, id of cluster             **/
/** (*) num_cl_p: (p. to) number of clusters               **/
/** RETURNS:                                               **/
/**     array with sizes of each cluster (created)         **/
/************************************************************/
int *gs_clusters(gs_graph_t *g, int *id, int *num_cl_p)
{
  int num_cl;                                   /* number of clusters */
  int *size;                                   /* ... of each cluster */
  int *cands;               /* 'stack' for nodes yet to be considered */
  elem_t *neighb;
  int i, k, cl, top;                          /* loop counters, nodes, ... */

  cands = (int *) malloc(g->num_nodes*sizeof(int));
  for(i=0; i<g->num_nodes; i++)
  {
  	id[i] = -1;
  }
    
              /* means: node has not been visited so far */
  num_cl = 0;
  top = 0;
  for(k=0; k<g->num_nodes; k++)              /* loop over all sites */
  {
	if(id[k]==-1)
    {
      cands[top] = k;
      top++;
      id[k] = num_cl;
      while(top!=0)  /* extend cluster */
      {
		  neighb = g->node[cands[top-1]].neighbors;
		  top--;
		  while(neighb!=0) /* loop over all neighbors */
		  {
			  if(id[neighb->info]==-1)
			  {
				  cands[top] = neighb->info;
				  top++;
				  id[neighb->info] = num_cl; /* access node number */
			  }
			  neighb = neighb->next;
		  }
      }
      num_cl++;
    }
  }

  *num_cl_p = num_cl;
  size = (int *) malloc(num_cl*sizeof(int));
  for(cl=0; cl<num_cl; cl++)  
    size[cl] = 0;
  for(i=0; i<g->num_nodes; i++)            /* determine cluster sizes */
    size[id[i]]++;

  free(cands);
  return(size);
}


