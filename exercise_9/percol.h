/********************************************************/
/*** types etc for simulation of percolation          ***/
/*** A.H. Hartmann  24.4.2005                         ***/
/********************************************************/

#ifndef _PERCOL_H_
#define _PERCOL_H_

/** macros **/

#define INDEX(t, r, nn) ((t)*(nn)+r)
#define NEXT(t, r) next[INDEX(t, r, num_n)]


/** types **/

/** global data of system **/
typedef struct
{
  int       dim;   /* dimension of system              */
  int        *l;   /* sizes of system                  */
  int        *n;   /* n[d]=size of d-dim subsystem     */
  int         N;   /* total number of sites = n[dim]   */
  int   largest;   /* size of currently largest cluster*/
  int *spanning;   /* does system span in dim 0,1,...? */
  int *spanning_n; /* # of sites spanning has 1st occ. */
} percol_glob_t;


/** node of tree respresenting sites in cluster **/
typedef struct p_node
{
  int id;                                 /* to identify node */
  struct p_node *parent;             /* points to predecessor */ 
  int              size; /* of subtree with this node as root */
  int            *delta; /* difference vector to site at root */
  int              *pos; /* position of site                  */
} percol_node_t;


/** prototypes **/

extern int percol_cluster(int num_n, int N, int *next, 
			  short int *site, int *cluster);
extern void percol_print(int N, int *l, short int *site);
extern int percol_largest(int N, int num_cl, int *cluster, int *id_largest_p);
extern double percol_analysis(int num_pts, double *value);

extern int *percol_init_next(int dim, int *l, int *n_p);
extern percol_glob_t *percol_create_glob(int dim, int *l);
extern void percol_delete_glob(percol_glob_t *glob);
extern percol_node_t *percol_create_node(int id, percol_glob_t *glob);
extern void percol_delete_node(percol_node_t *nodepercol_analysis);
extern percol_node_t *percol_root(percol_node_t *node, int *diff,
				  percol_glob_t *glob);
extern percol_node_t *percol_join_trees(percol_node_t *root1, int *diff1, 
					percol_node_t *root2, int *diff2,
					int *diff_loc, percol_glob_t *largest);
extern void percol_occupy_site(int id, int num_sites, percol_node_t **node,
			      int *next, int num_n, percol_glob_t *glob);
extern void percol_print_cluster(percol_node_t **node, 
				 percol_glob_t *glob);


/** in percol_spanning.c **/
// TODO: 2 Exercise 1
extern int percol_spanning(int N, int *cluster, 
			   int cluster_ID, int x_length);


/** in percol_surface.c **/
extern int percol_surface(int num_n, int N, int *next, int num_cl, 
			  int *cluster, int id_largest);


#endif  /* ifndef _PERCOL_H_ */
