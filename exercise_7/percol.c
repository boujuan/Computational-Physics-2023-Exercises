/****************************************************************/
/*** Simulates d-dim percolation                              ***/
/*** A.K. Hartmann April 2005                                 ***/
/*** Version 0.1.0.1 13.12.2007                               ***/
/*** Statistische Mechanik ungeordneter Systeme               ***/
/*** University of Goettingen, Germany 2005                   ***/
/*** Percolation using trees. See MEJ Newman and RM Ziff,     ***/
/*** Phys. Rev. Lett. 85, 4104 (2000)                         ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "percol.h"
#include "stacks.h"

/*** Vers. history ******************************************************/
/*** 0.1.0.1 (12/07) intit. 'id_largest' in percol_largest() cured    ***/


/******************* percol_cluster() *******************/
/** Calculates the connected clusters of the lattice   **/
/** 'site'. Occupied sites have 'site[i]=1' (i=1..N).  **/
/** Neigbours of occupied sites form clusters.         **/
/** For each site, in 'cluster[i]' the id of the       **/
/** cluster (starting at 0) is stored                  **/ 
/** PARAMETERS: (*)= return-paramter                   **/
/**       num_n: number of neighbours                  **/
/**           N: number of sites                       **/
/**        next: gives neighbours (0..N)x(0..num_n-1)  **/
/**              0 not used here. Use NEXT() to access **/
/**        site: tells whether site is occupied        **/
/** (*) cluster: id of clusters sites are contained in **/
/** RETURNS:                                           **/
/**     number of clusters                             **/
/********************************************************/
int percol_cluster(int num_n, int N, int *next, 
		   short int *site, int *cluster)
{
  int num_clusters=0;
  int t, r;       /* loop counters over sites, directions */
  int current, neighbour;                        /* sites */
  lstack_t *members;      /* stack of members for cluster */

  for(t=1; t<=N; t++)    /* initialise all clusters empty */
    cluster[t] = -1;
  members = lstack_new(N, sizeof(int));

  for(t=1; t<=N; t++)              /* loop over all sites */
  {
    if((site[t] == 1)&&(cluster[t]==-1)) /* new cluster ? */
    {
      lstack_push(members, &t);          /* start cluster */
      cluster[t] = num_clusters;
      while(!lstack_is_empty(members))  /* extend cluster */
      {
	lstack_pop(members, &current);
	for(r=0; r<num_n; r++)   /* loop over neighbours */
	{
	  neighbour = NEXT(current, r);
	  if((site[neighbour]==1)&&(cluster[neighbour]==-1))
	  {          /* neighbour belongs to same cluster */
	    lstack_push(members, &neighbour);
	    cluster[neighbour] = num_clusters;
	  }
	}
      }
      num_clusters++;
    }
  }

  lstack_delete(members);
  return(num_clusters);
}

/******************* percol_print() *********************/
/** Prints 'site' line by line. All occupied sites     **/
/** (site[i]==1, i=1..N) are indicated by printing X.  **/
/** PARAMETERS: (*)= return-paramter                   **/
/**           N: number of sites                       **/
/**           l: size of system in x,y,..              **/
/**        site: tells whether site is occupied        **/
/** RETURNS:                                           **/
/**     nothing                                        **/
/********************************************************/
void percol_print(int N, int *l, short int *site)
{
  int t;                                /* loop counter */
  
  for(t=1; t<=N; t++)            /* loop over all sites */
  {
    if(site[t])
      printf("X");
    else
      printf(" ");
    if( ((t-1)%l[0]) == (l[0]-1) )        /* end of line ? */
      printf("\n");
  }
}

/******************* percol_largest() *******************/
/** Picks largest cluster from all clusters            **/
/** PARAMETERS: (*)= return-paramter                   **/
/**            N: number of sites                      **/
/**       num_cl: number of clusters                   **/
/**      cluster: id of clusters sites are contained in**/
/**(*)id_largest: id of largest cluster                **/
/** RETURNS:                                           **/
/**     size of largest clusters                       **/
/********************************************************/
int percol_largest(int N, int num_cl, int *cluster, int *id_largest_p)
{
  int *size;             /* size[i] = size of cluster i */
  int t, cl;       /* loop counter over sites, clusters */
  int max_size;              /* size of largest cluster */
  int id_largest;

  size = (int *) malloc(num_cl*sizeof(int));    /* init */
  for(cl=0; cl<num_cl; cl++)
    size[cl] = 0;

  for(t=1; t<=N; t++)                /* determine sizes */
    if((cluster[t] >= 0) && (cluster[t] < num_cl))
      size[cluster[t]]++;

  max_size = size[0];              /* determine maximum */
  id_largest = 0;
  for(cl=1; cl<num_cl; cl++)
    if(size[cl] > max_size)
    {
      max_size = size[cl];
      id_largest = cl;
    }
  *id_largest_p = id_largest;

  free(size);
  return(max_size);
}




/******************* percol_analysis() ******************/
/** Performs evaluation with given data array          **/
/** PARAMETERS: (*)= return-paramter                   **/
/**     num_pts: number of points                      **/
/**       value: data                                  **/
/** RETURNS:                                           **/
/**     Binder parameter                               **/
/********************************************************/
double percol_analysis(int num_pts, double *value)
{
  double sum, sum2, sum4;
  int t;

  sum = 0; sum2=0; sum4=0;
  for(t=0; t<num_pts; t++)
  {
    sum += value[t];
    sum2 += value[t]*value[t];
    sum4 += value[t]*value[t]*value[t]*value[t];
  }

  return(sum/num_pts);
  /*return(0.5*(3.0-(sum4/num_pts)/(sum2*sum2/(num_pts*num_pts))));*/
}


/************** percol_init_next() **********************/
/** Allocates and initialises 'next[][]' For simple    **/
/** hypercubic lattice. Use macro                      **/
/** 'NEXT' to access. NEXT(t,r) gives neighbour of     **/
/** element 't'=1,2,... in direction 'r' with          **/
/** 'r'=0,1,..,num_n-1 correspond to                   **/
/**  +x,-x,+y,-y,...                                   **/
/** PARAMETERS: (*)= return-paramter                   **/
/**       dim: dimension of system                     **/
/**         l: size of system in x,y,..                **/
/**   (*) n_p: ptr to number of sites                  **/
/** RETURNS:                                           **/
/**     pointer to neighbour array                     **/
/**      next: gives neighbours next[0..N][0..num_n-1] **/
/********************************************************/
int *percol_init_next(int dim, int *l, int *n_p)
{
  int t, t2;                            /* loop counter */
  int N;                             /* number of sites */
  int *n;    /* n[d]= # of sites in subsystem of dim. d */  
  int *next;        /* contains neighbours of all sites */
  int num_n;                    /* number of neighbours */

  num_n = 2*dim;
  n = (int *) malloc((dim+1)*sizeof(int));
  n[0] = 1;            /* calculates sizes of subsytems */
  for(t=1; t<dim+1; t++)
    n[t] = l[t-1]*n[t-1];
  N = n[dim];
  *n_p =N;
  next = malloc((N+1)*(2*dim)*sizeof(int));
  for(t=1; t<N+1; t++)           /* loop over all sites */
  {
    /*NEXT(t, 2*dim) = N+1;
      NEXT(t, 2*dim+1) = 0;*/
    for(t2=0; t2<dim; t2++)
    {
      if((((t-1)%n[t2+1])/n[t2])==0) 
      {                                /* "left" border */
	NEXT(t, 2*t2)= t+n[t2];       /* right neigbour */
	NEXT(t, 2*t2+1) = t+(l[t2]-1)*n[t2];
      }
      else if((((t-1)%n[t2+1])/n[t2])==(l[t2]-1))
      {                               /* "right" border */
	NEXT(t, 2*t2) = t-(l[t2]-1)*n[t2];  
	NEXT(t, 2*t2+1) = t-n[t2];    /* left neighbour */
      }
      else     
      {                                /* standard case */
	NEXT(t, 2*t2) = t+n[t2];
	NEXT(t, 2*t2+1) = t-n[t2];
      }
    }
  }
  free(n);
  return(next);
}


/***************** percol_create_glob() *****************/
/** Creates global structure of system                 **/
/** PARAMETERS: (*)= return-paramter                   **/
/**       dim: dimension of system                     **/
/**         l: sizes of system                         **/
/** RETURNS:                                           **/
/**     pointer to global structure                    **/
/********************************************************/
percol_glob_t *percol_create_glob(int dim, int *l)
{
  percol_glob_t *glob;
  int d;

  glob = (percol_glob_t *) malloc(sizeof(percol_glob_t));
  glob->dim = dim;
  glob->n = (int *) malloc((dim+1)*sizeof(int));
  glob->l = (int *) malloc(dim*sizeof(int));
  glob->n[0] = 1;            /* calculates sizes of subsytems */
  for(d=1; d<dim+1; d++)
  {
    glob->l[d-1]=l[d-1];
    glob->n[d] = l[d-1]*glob->n[d-1];
  }
  glob->N = glob->n[dim];
  glob->largest = 0;
  glob->spanning_n = (int *) malloc(dim*sizeof(int));
  glob->spanning = (int *) malloc(dim*sizeof(int));
  for(d=0; d<dim; d++)
    glob->spanning[d] = 0;

  return(glob);
}


/***************** percol_delete_glob() *****************/
/** Deletes global structure of system                 **/
/** PARAMETERS: (*)= return-paramter                   **/
/**     glob: pointer to global structure              **/
/** RETURNS:                                           **/
/**         nothing                                    **/
/********************************************************/
void percol_delete_glob(percol_glob_t *glob)
{
  free(glob->spanning);
  free(glob->spanning_n);
  free(glob->l);
  free(glob->n);
  free(glob);
}


/***************** percol_create_node() *****************/
/** Creates node for site 'id'                         **/
/** PARAMETERS: (*)= return-paramter                   **/
/**       id: of site                                  **/
/**     glob: pointer to global structure              **/
/** RETURNS:                                           **/
/**       pointer to created node                      **/
/********************************************************/
percol_node_t *percol_create_node(int id, percol_glob_t *glob)
{
  percol_node_t *node;
  int d;

  node = (percol_node_t *) malloc(sizeof(percol_node_t));
  node->id = id;
  node->parent = NULL;
  node->size = 1;
  node->pos = (int *) malloc(glob->dim*sizeof(int));
  for(d=(glob->dim-1); d>=0; d--)             /* set position */
  {
    node->pos[d] = id/glob->n[d];
    id -= node->pos[d]*glob->n[d];
  }
  node->delta = (int *) malloc(glob->dim*sizeof(int));
  for(d=0; d<glob->dim; d++)            /* set diff to itself */
    node->delta[d] = 0;

  return(node);
}


/***************** percol_delete_node() *****************/
/** Deletes node                                       **/
/** PARAMETERS: (*)= return-paramter                   **/
/**     node: ....                                     **/
/** RETURNS:                                           **/
/**       nothing                                      **/
/********************************************************/
void percol_delete_node(percol_node_t *node)
{
  free(node->delta);
  free(node->pos);
  free(node);
}


/******************* percol_root() **********************/
/** Returns root of cluster where "node" is located in **/
/** PARAMETERS: (*)= return-paramter                   **/
/**       id: of site                                  **/
/** (*) diff: difference (on lattice) of node to root  **/
/**     glob: pointer to global structure              **/
/** RETURNS:                                           **/
/**       pointer to created node                      **/
/********************************************************/
percol_node_t *percol_root(percol_node_t *node, int *diff,
			   percol_glob_t *glob)
{
  int d;

  for(d=0; d<glob->dim; d++)
    diff[d] = 0;

  if(node->parent == NULL)     /* is node itself root ? */
  {
    return(node);
  }
  else if (node->parent->parent == NULL)
  {
    for(d=0; d<glob->dim; d++)
      diff[d] = node->delta[d];
    return(node->parent);        /* node points to root */
  }
  else                      
  {
    while(node->parent != 0)         /* search for root */
    {
      for(d=0; d<glob->dim; d++)
	diff[d] += node->delta[d];
      node = node->parent;
    }
    return(node);
  }
}

/******************* percol_join_trees() ****************/
/** Merges two trees into one. The smaller is attached **/
/** to the larger one.                                 **/
/** The merging occurs, because two sites node1,node2  **/
/** become adjacent.                                   **/
/** Also the delta displacments vectors are updated    **/
/** PARAMETERS: (*)= return-paramter                   **/
/**    root1: root of 1st tree                         **/
/**    diff1: vector from node1 to root1               **/
/**    root2: root of 2nd tree                         **/
/**    diff1: vector from node1 to root1               **/
/** diff_loc: vector from node1 to node2               **/
/**     glob: pointer to global data                   **/
/** RETURNS:                                           **/
/**       pointer to common root                       **/
/********************************************************/
percol_node_t *percol_join_trees(percol_node_t *root1, int *diff1,
				 percol_node_t *root2, int *diff2,
				 int *diff_loc, percol_glob_t *glob)
{
  int d;
  if(root1->size > root2->size)
  {
    root2->parent = root1;               /* attach tree */
    root1->size += root2->size;        /* updated sizes */
    if(root1->size > glob->largest)   /* update largest */
      glob->largest = root1->size;
    for(d=0; d<glob->dim; d++)
      root2->delta[d] = -diff2[d]-diff_loc[d]+diff1[d];
    return(root1);                   /* return new root */
  }
  else
  {
    root1->parent = root2;               /* attach tree */
    root2->size += root1->size;        /* updated sizes */
    if(root2->size > glob->largest)   /* update largest */
      glob->largest = root2->size;
    for(d=0; d<glob->dim; d++)
      root1->delta[d] = -diff1[d]+diff_loc[d]+diff2[d];
    return(root2);                   /* return new root */
  }
}


/***************** percol_occupy_site() *****************/
/** Occupies site 'id' and updates cluster trees 'node'**/
/** Also spanning statistics in 'glob' are updated.    **/
/** PARAMETERS: (*)= return-paramter                   **/
/**       id: of site                                  **/
/**num_sites: # sites occupied so far(statistics)      **/                  
/** (*) node: cluster trees                            **/
/**     next: neighbours of all sites                  **/
/**    num_n: (max) number of neighbours of each site  **/
/** (*) glob: pointer to global structure              **/
/** RETURNS:                                           **/
/**       nothing                                      **/
/********************************************************/
void percol_occupy_site(int id, int num_sites, percol_node_t **node,
		       int *next, int num_n, percol_glob_t *glob)
{
  int r, d;
  percol_node_t *neighb, *root1, *root2;
  int *diff1, *diff2, *diff_loc;

  if(node[id] != NULL)
  {
    fprintf(stderr, "node %d is not empty\n", id);
  }
  node[id] = percol_create_node(id, glob);
  diff1 = (int *) malloc(glob->dim*sizeof(double));
  diff2 = (int *) malloc(glob->dim*sizeof(double));
  diff_loc = (int *) malloc(glob->dim*sizeof(double));
  for(r=0; r<num_n; r++)           /* loop over all neighbours */
  {
    for(d=0; d<glob->dim; d++)       /* calculate displacement */
    {                                /* id -> NEXT(id,r)       */
      if( (2*d)==r)
	diff_loc[d] = 1;
      else if( (2*d+1)==r)
	diff_loc[d] = -1;
      else
	diff_loc[d] = 0;
    }
    neighb = node[NEXT(id, r)];

    if(neighb != NULL)         /* is neighbour site occupied ? */
    {
      root1 = percol_root(node[id], diff1, glob);
      root2 = percol_root(neighb, diff2, glob);
      if(root1 != root2)        /* in different trees so far ? */
	percol_join_trees(root1, diff1, root2, diff2, diff_loc, glob);
      else
      {
	for(d=0; d<glob->dim; d++)         /* check for spanning */
	  if(fabs((double) diff1[d]-diff2[d]) > 1)
	  {
	    if(glob->spanning[d] == 0)   /* for the first time ? */
	    {
	      glob->spanning[d] = 1;
	      glob->spanning_n[d] = num_sites;
	    }
	  }

      }
    }
  }
  free(diff1);
  free(diff2);
  free(diff_loc);
}


/*************** percol_print_cluster() *****************/
/** Prints for each site the cluster (=id of root site)**/        
/** nothing for each unoccupied site                   **/
/** PARAMETERS: (*)= return-paramter                   **/
/**     node: cluster trees                            **/
/**     glob: pointer to global structure              **/
/** RETURNS:                                           **/
/**        nothing                                     **/
/********************************************************/
void percol_print_cluster(percol_node_t **node, 
			 percol_glob_t *glob)
{
  int t;
  percol_node_t *root;
  int *diff;

  diff = (int *) malloc(glob->dim*sizeof(int));
  for(t=1; t<=glob->N; t++)          /* run through all sites */
  {
    if(node[t] == NULL)                      /* empty ? */
      printf("     ");
    else
    {
      root = percol_root(node[t], diff, glob);
      printf("%04d ", root->id);
    }
    if( (t % glob->l[0]) == 0)
      printf("\n");
  }
  free(diff);
}
