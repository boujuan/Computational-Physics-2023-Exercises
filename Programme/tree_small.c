#include <stdio.h>
#include <stdlib.h>

/* data structures for tree elements */
struct node_struct
{
    int                  info;                  /* holds ``information'' */
    struct node_struct  *left;  /* points to left subtree (NULL if none) */
    struct node_struct *right;  /* points to left subtree (NULL if none) */
};

typedef struct node_struct node_t;       /* define new type for nodes */

/* function commentary header (empty): */

/*******************  *****************/
/**  **/
/** PARAMETERS: (*)= return-paramter         **/
/**  **/
/** RETURNS:                               **/
/**  **/
/******************************************/


/* function commentary header (empty): */

/******************* create_node() ********************/
/** Creates an tree node and initializes info        **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        value: of info                            **/
/** RETURNS:                                         **/
/**     pointer to new node                          **/
/******************************************************/
node_t *create_node(int value)
{
  node_t *node;

  node = (node_t *) malloc (sizeof(node_t));
  node->info = value;
  node->right = NULL;
  node->left = NULL;
  return(node);
}

/********************* delete_node() ******************/
/** Deletes a single tree node (i.e. only if it      **/
/** is not linked to other nodes)                    **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         node: pointer to node                    **/
/** RETURNS:                                         **/
/**    0: OK, 1: error                               **/
/******************************************************/
int delete_node(node_t *node)
{
  if(node == NULL)
  {
    fprintf(stderr, "attempt to delete `nothing`\n");
    return(1);
  }
  else if( (node->left != NULL)||(node->right != NULL))
  {
    fprintf(stderr, "attempt to delete linked node!\n");
    return(1);
  }
  else
  {
    free(node);
    return(0);
  }
}

/********************* insert_node() ******************/
/** Inserts 'node' into the 'tree' such that the     **/
/** increasing order is preserved                    **/
/** if node exists already, nothing happens          **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/**         node: pointer to node                    **/
/** RETURNS:                                         **/
/**   (new) pointer to root of tree                  **/
/******************************************************/
node_t *insert_node(node_t *tree, node_t *node)
{
  node_t *current;

  if(tree==NULL)
    return(node);
  current = tree;
  while( current != NULL)                  /* run through tree */
  {
    if(current->info==node->info)  /* node already contained ? */
      return(tree);
    if( node->info < current->info)            /* left subtree */  
    {
      if(current->left == NULL)
      {             
	current->left = node;                      /* add node */
	return(tree);
      }
      else
	current = current->left;         /* continue searching */
    }
    else                                      /* right subtree */
    {
      if(current->right == NULL)             
      {
	current->right = node;                     /* add node */
	return(tree);
      }
      else
	current = current->right;         /* continue searching */
    }
  }
  return(tree);
}

/********************* print_tree() *******************/
/** Prints tree in ascending order recursively.      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   nothing                                        **/
/******************************************************/
void print_tree(node_t *tree)
{
  if(tree != NULL)
  {
    print_tree(tree->left);
    printf("%d ", tree->info);
    print_tree(tree->right);
  }
}

/************** print_tree_indent() *******************/
/** Prints tree in ascending order recursively.      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   nothing                                        **/
/******************************************************/
void print_tree_indent(node_t *tree, int level)
{
  int t;
  if(tree != NULL)
  {
    print_tree_indent(tree->left, level+1);
    for(t=0; t<level; t++)
      printf("  ");
    printf("%d\n", tree->info);
    print_tree_indent(tree->right, level+1);
  }
}



int main(int argc, char *argv[])
{
  node_t *tree, *node;
  
  tree = NULL;
  node = create_node(20);
  tree = insert_node(tree, node);
  node = create_node(25);
  tree = insert_node(tree, node);
  node = create_node(15);
  tree = insert_node(tree, node);
  node = create_node(13);
  tree = insert_node(tree, node);
  node = create_node(23);
  tree = insert_node(tree, node);
  node = create_node(27);
  tree = insert_node(tree, node);
  node = create_node(24);
  tree = insert_node(tree, node);
  node = create_node(22);
  tree = insert_node(tree, node);


  print_tree_indent(tree, 0); printf("\n");

  return(0);
}
 
