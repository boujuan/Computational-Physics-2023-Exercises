#ifndef _GRAPHS_LISTS_H_
#define _GRAPHS_LISTS_H_

/* data structures for graphs elements */

typedef struct
{
    elem_t *neighbors;   /* pointer to list of neighbors */
} gs_node_t;

typedef struct
{
    int           num_nodes;          /* number of nodes */
    gs_node_t         *node;          /* array of nodes */
} gs_graph_t;

/** function prototypes **/

extern gs_graph_t *gs_create_graph(int num_nodes);
extern void gs_insert_edge(gs_graph_t *g, int from, int to);
extern int gs_edge_exists(gs_graph_t *g, int from, int to);
extern void gs_clear_graph(gs_graph_t *g);
extern void gs_delete_graph(gs_graph_t *g);
extern int gs_degree(gs_graph_t *g, int n);
extern void gs_preferential_attachment(gs_graph_t *g, int m);
extern void gs_random_graph(gs_graph_t *g, int m);
extern void gs_block_model(gs_graph_t *g, double p1, double p2, int *group);
extern void gs_write_graph(gs_graph_t *g, FILE *file);
extern int *gs_clusters(gs_graph_t *g, int *id, int *num_cl_p);

#endif /* #ifndef _GRAPHS_LISTS_H_ */
