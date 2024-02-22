#include <stdio.h>
#include <stdlib.h>
#include <time.h> // for srand (random seed)
#include <math.h> // for fabs (absolute value for double)

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

void print_tree_indent_clear(node_t *tree, int level, char* direction)
{
  int t;
  if(tree != NULL)
  {
    print_tree_indent_clear(tree->left, level+1, "L");
    for(t=0; t<level; t++)
      printf("  ");
    if(level > 0) // if not root
      printf("|-%s-", direction);
    printf("%d\n", tree->info);
    print_tree_indent_clear(tree->right, level+1, "R");
  }
}
/********************* count_leaves() *****************/
/** Caluclates number of leaves recursively.         **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/** RETURNS:                                         **/
/**   number of leaves                               **/
/******************************************************/
int count_leaves(node_t *tree)
{
  if (tree == NULL) {
    return 0; // empty tree (no leaves)
  } else if (tree->left == NULL && tree->right == NULL) {
    return 1; // it's a leaf, so count 1 leaf
  } else { // it's not a leaf, so count leaves in left and right subtrees
    return count_leaves(tree->left) + count_leaves(tree->right); // sum of leaves in left and right subtrees
  }
}
// Modify the function to count the number of nodes in the tree
int tree_size(node_t *tree)
{
  int n1, n2;
  if (tree == NULL)
    return 0; // empty tree 
  n1 = tree_size(tree->left); // left subtree size
  n2 = tree_size(tree->right); // right subtree size
  return n1 + n2 + 1; // total size
}

/******************** remove_value() ******************/
/** Removes node containung the 'value' from  the    **/
/** tree.                                            **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         tree: pointer to root of tree            **/
/**         value: to be removed                     **/
/**    (*) node_p: address of ptr to removed node    **/
/** RETURNS:                                         **/
/** (new) pointer to the root                        **/
/******************************************************/
node_t *remove_value(node_t *tree, int value, node_t **node_p)
{
  node_t *current;                     /* used for running through tree */
  node_t  *pred;           /* always pred->(left/right) = current holds */
  node_t *next;           // next node to be removed
  pred = NULL;
  next = NULL;          // initialize
  current = tree;
  while( (current != NULL)&&(current->info != value) )  /* search value */
  {
    pred = current;
    if(current->info > value)
      current = current->left;
    else
      current = current->right;
  }

  if(current == NULL)                              /* value not found ? */
  {
    *node_p = NULL;
    return(tree);
  }

  
  if( (current->left != NULL)&&(current->right != NULL)) // Node has 2 children
  {
    /* search smallest val. in right subtree, adjust pred as well! , exchange values */
    next = current->right; // look at right subtree of current node
    pred = current; // set pred to current node
    while(next->left != NULL) // keep looking at left subtree of next node and update pred and next  
    {
      pred = next;
      next = next->left;
    }
    current->info = next->info;
    current = next; // set current to next node
  }
  *node_p = current;
  /* now node 'current' is to be removed from tree. We know here */
  /* that it  has at most one descendant                         */

  
  if(pred == NULL) // Remove root node with one child
  {
    /** COMPLETE **/
    /* return new root */
    if(current->left != NULL) // if left child exists, set it as new root, otherwise set right child as new root
      tree = current->left;
    else
      tree = current->right;
  }
  
  else // Remove node 
  {
    /** COMPLETE **/
    /* treat standard case */
    if (pred->left == current) { // if current node is left child of pred
      if (current->left != NULL) {
        pred->left = current->left; // reemplace current node with left child
      } else {
        pred->left = current->right;
      }
    } else {
      if (current->left != NULL) {
        pred->right = current->left;
      } else {
        pred->right = current->right; // reemplace current node with right child
      }
    }

  }
  return(tree);
}

// TODO: 1
// Knuth's algorithm for estimating the number of leaves in a binary tree
int knuth(node_t *tree) {
    int b = 1; // Estimate at root node
    while (tree != NULL) {
        if (tree->left != NULL && tree->right != NULL) { // If 2 children, double b and choose random direction.
            b = 2 * b;
            // choose left or right successor with same probability
            if (drand48() < 0.5) { // drand48() returns a random number between 0 and 1, with uniform distribution
                tree = tree->left;
            } else {
                tree = tree->right;
            }
        } else if (tree->left != NULL) { // Move to successor if only one child without increasing b.
            tree = tree->left;
        } else if (tree->right != NULL) {
            tree = tree->right;
        } else {
            break;
        }
    }
    return b;
}

// TODO: 2
// Show by recursion that the expectation value <b> = number of leaves in the tree
void test_knuth(node_t *tree, int num_runs) {
  int b = 0;
  for (int i = 0; i < num_runs; i++) {
    b += knuth(tree);
  }
  double average = (double)b / num_runs;
  int actual = count_leaves(tree);
  printf("Average estimate of number of leaves over %d runs: %f\n", num_runs, average);
  printf("Actual number of leaves: %d\n", actual);
}

// TODO: 3
// Function to test the number of runs needed until convergence
void test_knuth_simple(node_t *tree) {
  int b = 0;
  int num_runs = 0;
  double average = 0;
  int actual = count_leaves(tree);
  double tolerance = 0.01; // Tolerance
  double error = 0;

  remove("output.txt"); // Remove file if it exists

  // Open a file in write mode.
  FILE *file = fopen("output.txt", "a");
  if (file == NULL) {
    printf("Error opening file!\n");
    return;
  }

  do { // Need to run it at least once to update average value
    
    b += knuth(tree);
    num_runs++;
    average = (double)b / num_runs; // Added missing semicolon here
    error = fabs(average - actual); // Need math.h for fabs, ab

    // Write the values of num_runs and error to the file.
    fprintf(file, "num_runs: %d, error: %f\n", num_runs, error);
  } while (num_runs < 10000000 && error > tolerance);

  // Close the file.
  fclose(file);
}

// TODO: 4
// Create a random tree with N nodes
void create_random_tree(node_t *tree, int N) {
  srand(time(NULL)); // seed for random number generator
  for (int i = 0; i < N; i++) {
    int value = rand() % 100; // random number between 0 and 99
    node_t *node = create_node(value);
    tree = insert_node(tree, node);
  }
}

int main(int argc, char *argv[])
{
  node_t *tree, *node;
  int value;
  
  tree = NULL;
  node = create_node(20);
  tree = insert_node(tree, node);
  node = create_node(10);
  tree = insert_node(tree, node);
  node = create_node(30);
  tree = insert_node(tree, node);
  node = create_node(5);
  tree = insert_node(tree, node);
  node = create_node(15);
  tree = insert_node(tree, node);
  node = create_node(25);
  tree = insert_node(tree, node);
  node = create_node(35);
  tree = insert_node(tree, node);
  node = create_node(3);
  tree = insert_node(tree, node);
  node = create_node(12);
  tree = insert_node(tree, node);
  node = create_node(27);
  tree = insert_node(tree, node);
  node = create_node(40);
  tree = insert_node(tree, node);

  printf("%d leaves\n", count_leaves(tree));

  print_tree_indent(tree,0); printf("\n");
  value = 40;
  printf("rem: %d\n", value);
  tree = remove_value(tree, value, &node);
  print_tree_indent(tree,0); printf("\n");

  value = 25;
  printf("rem: %d\n", value);
  tree = remove_value(tree, value, &node);
  print_tree_indent(tree,0); printf("\n");

  value = 20;
  printf("rem: %d\n", value);
  tree = remove_value(tree, value, &node);
  print_tree_indent(tree,0); printf("\n");

  // TODO:
  // Knuth's algorithm for estimating the number of leaves in a binary tree
  printf("Knuth's estimation: %d leaves\n", knuth(tree));

  // Test Knuth's algorithm
  int num_runs = atoi(argv[1]); // number of runs input from cl argument
  test_knuth(tree, num_runs);

  //Generate random tree and print it
  int N = atoi(argv[2]); // number of nodes input from cl argument
  create_random_tree(tree, N);
  printf("Random tree with %d nodes\n", N);
  // print_tree_indent_clear(tree, 0, "");
  print_tree(tree);

  // Test the number of runs needed until convergence for random tree
  test_knuth_simple(tree);

  return(0);
}
