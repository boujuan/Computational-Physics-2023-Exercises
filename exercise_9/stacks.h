/****************************************************************/
/*** Include-File for stacks                                  ***/
/*** A.K. Hartmann June 2004                                  ***/
/*** Rechnergestütztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#ifndef _LSTACK_H_
#define _LSTACK_H_

#include <stdlib.h>


typedef struct 
{
  int           num; /* current num. of elements in the stack */
  int           cap; /* size of a stack  (No. of elements)    */
  size_t  elem_size; /* size of an element                    */
  char        *data; /* pointer to stack-memory               */
} lstack_t;

/** Errorcodes: **/
#define LSTACK_FULL 1
#define LSTACK_EMPTY 2

/** function prototypes **/
extern lstack_t *lstack_new(int cap, size_t elem_size);
extern void lstack_delete(lstack_t *stack);
extern int lstack_is_empty(lstack_t *stack);
extern int lstack_push(lstack_t *stack, void *element);
extern int lstack_pop(lstack_t *stack, void *element);

#endif   /* _LSTACK_H_ */
