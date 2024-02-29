/****************************************************************/
/*** Stacks                                                   ***/
/*** A.K. Hartmann June 2004                                  ***/
/*** Rechnergestütztes Wissenschaftliches Rechnen             ***/
/*** University of Goettingen, Germany 2004                   ***/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "stacks.h"


/** Creates a stack of size 'cap', where each data-element has    **/
/** the size 'elem_size' (in bytes = char).                       **/
/** RETURN: pointer to the stack                                  **/
lstack_t *lstack_new(int cap, size_t elem_size)
{
  lstack_t *stack;

  stack = (lstack_t *) malloc(sizeof(lstack_t));
  stack->num = 0;
  stack->cap = cap;
  stack->elem_size = elem_size;
  stack->data = malloc(cap*elem_size);
  return(stack);
}

/** Deletes a 'stack'       **/
void lstack_delete(lstack_t *stack)
{
  free(stack->data);
  free(stack);
}

/** Tests wether 'stack' is empty **/
int lstack_is_empty(lstack_t *stack)
{
  return(stack->num == 0);
}


/** Pushes an 'element' on top of the 'stack'.     **/
/** RETURN: =0 -> everything ok, or = LSTACK_FULL  **/
int lstack_push(lstack_t *stack, void *element)
{
  void *ptr;

  if(stack->num >= stack->cap) /* Tests if stack is full */
    return(LSTACK_FULL);
  ptr = stack->data + (stack->num++) * stack->elem_size;
  memcpy(ptr, element, stack->elem_size);
  return(0);
}

/** Pops the top 'element' from the 'stack' **/
/** RETURNS =0 -> ok, or = LSTACK_FULL      **/
int lstack_pop(lstack_t *stack, void *element)
{
  char *ptr;

  if(stack->num == 0)         /* Tests if stack is empty */
    return(LSTACK_EMPTY);
  /** return the element to be poped: **/
  ptr = stack->data + (--(stack->num)) * stack->elem_size;
  memcpy(element, ptr, stack->elem_size);
  return(0);
}

