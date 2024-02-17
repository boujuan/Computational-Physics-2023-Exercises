#include <stdio.h>
#include <stdlib.h>

#include "list.h"


/* function commentary header (empty): */

/*******************  *****************/
/**  **/
/** PARAMETERS: (*)= return-paramter         **/
/**  **/
/** RETURNS:                               **/
/**  **/
/******************************************/


/* function commentary header (empty): */

/******************* create_element() *****************/
/** Creates an list element an initialized info      **/
/** PARAMETERS: (*)= return-paramter                 **/
/**        value: of info                            **/
/** RETURNS:                                         **/
/**     pointer to new element                       **/
/******************************************************/
elem_t *create_element(int value)
{
  elem_t *elem;

  elem = (elem_t *) malloc (sizeof(elem_t));
  elem->info = value;
  elem->next = NULL;
  return(elem);
}

/******************* delete_element() *****************/
/** Deletes a single list element (i.e. only if it   **/
/** is not linked to another element)                **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         elem: pointer to element                 **/
/** RETURNS:                                         **/
/**    0: OK, 1: error                               **/
/******************************************************/
int delete_element(elem_t *elem)
{
  if(elem == NULL)
  {
    fprintf(stderr, "attempt to delete `nothing`\n");
    return(1);
  }
  else if(elem->next != NULL)
  {
    fprintf(stderr, "attempt to delete linked element!\n");
    return(1);
  }
  else
  {
    free(elem);
    return(0);
  }
}

/******************* insert_element() *****************/
/** Inserts the element `elem` in the `list          **/
/** BEHIND the `where`. If 'where' is equal to NULL  **/
/** then the element is inserted at the beginning of **/
/** the list.                                        **/
/** PARAMETERS: (*)= return-paramter                 **/
/**         list: first element of list              **/
/**         elem: pointer to element to be inserted  **/
/**        where: position of new element            **/ 
/** RETURNS:                                         **/
/**  (new) pointer to the beginning of the list      **/
/******************************************************/
elem_t *insert_element(elem_t *list, elem_t *elem, elem_t *where)
{
  if(where==NULL)                               /* insert at beginning ? */
  {
    elem->next = list;
    list = elem;
  }
  else                                               /* insert elsewhere */
  {
    elem->next = where->next;
    where->next = elem;
  }
  return(list);
}

/******************* print_list() *****************/
/** Prints all elements of a list                **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/** RETURNS:                                     **/
/**          nothing                             **/
/**************************************************/
void print_list(elem_t *list)
{
  while(list != NULL)               /* run through list */
  {
    printf("%d ", list->info);
    list = list->next;
  }
  printf("\n");
}

/******************* write_list() *****************/
/** Writes all elements of a list to 'file'      **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**           file:  where to write (e.g. stdout)**/
/** RETURNS:                                     **/
/**          nothing                             **/
/**************************************************/
void write_list(elem_t *list, FILE *file)
{
  while(list != NULL)               /* run through list */
  {
    fprintf(file, "%d ", list->info);
    list = list->next;
  }
  fprintf(file, "\n");
}

/****************** search_info() *****************/
/** Search for 'value' in 'list'                 **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**          value: to be found                  **/
/** RETURNS:                                     **/
/**  pointer to element or NULL if not found     **/
/**************************************************/
elem_t *search_info(elem_t *list, int value)
{
  while( (list != NULL)&&(list->info != value))  /* run through list */
    list = list->next;
  return(list);
}


/****************** remove_element() **************/
/** Remove element from list                     **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**           elem: to be removed                **/
/** RETURNS:                                     **/
/**  (new) pointer to beginning of the list      **/
/**************************************************/
elem_t *remove_element(elem_t *list, elem_t *elem)
{
  elem_t *p;
  if(elem == list)                     /* delete first element ? */
  {
    list = elem->next;
  }
  else                         /* delete element not being first */
  {
    p = list;                /* search for element BEFORE 'elem' */
    while( (p != NULL)&&(p->next != elem))
      p = p->next;
    if(p==NULL)
    {
      fprintf(stderr, "element no found\n");
      return(list);
    }
    p->next = elem->next;
  }
  elem->next = NULL;                 /* remove element from list */
  return(list);
}


/****************** remove_value() ****************/
/** Search for 'value' in 'list' and remove it   **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**          value: to be removed                **/
/** RETURNS:                                     **/
/**  (new) pointer to beginning of the list      **/
/**************************************************/
elem_t *remove_value(elem_t *list, int value)
{
  elem_t *p, *p_pred;

  p_pred = NULL; p = list;
 
  while( (p != NULL)&&(p->info != value))    /* run through list */
  {
    p_pred = p;
    p = p->next;
  }
  if(p == NULL)                                     /* not found */ 
    return(list);                             /* nothing happens */

  if(p == list)                        /* remove first element ? */
  {  
    list = p->next;
  }
  else                         /* remove element not being first */
  {
    p_pred->next = p->next;
  }
  p->next = NULL;                    /* remove element from list */
  return(list);
}


/***************** mergesort_list() ***************/
/** Sorts list using mergesort algorithm         **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/** RETURNS:                                     **/
/**  (new) pointer to beginning of the list      **/
/**************************************************/
elem_t *mergesort_list(elem_t *list)
{
  elem_t *aux;                         /* auxiliary list pointer */
  elem_t *list1,*list2;       /* pointer to 1st/2nd half of list */
  int length, length1;         /* of full list/ 1st half of list */

  length = 0;                        /* determine length of list */
  aux = list;
  while(aux != NULL)
  {
    length++;
    aux = aux->next;
  }

  if(length == 1)          /* one element list is already sorted */
    return(list);

  length1 = 0;          /* move 'list2' to beginning of 2nd half */
  list2 = list;
  while(length1 < length/2)
  {
    length1 ++;
    aux = list2;
    list2 = list2->next;
  }       /* now 'aux' just points to one element before 'list2' */ 
  aux->next = NULL;                            /* decouple lists */
  
  list1 = mergesort_list(list);            /* sort partial lists */
  list2 = mergesort_list(list2);

  if(list1->info < list2->info)   /* start merged (=sorted) list */
  {
    list = list1;
    list1 = list1->next;
  }
  else
  {
    list = list2;
    list2 = list2->next;
  }
  aux = list;        /* aux points to current end of sorted list */
  while( (list1 != NULL)||(list2 != NULL))        /* merge lists */
  {
    if( (list1 == NULL)||((list2!=NULL)&&(list2->info<list1->info)))
    {                /* move element from 'list2' to sorted list */
      aux->next=list2;
      aux=list2;
      list2 = list2->next;
    }
    else
    {                /* move element from 'list1' to sorted list */
      aux->next=list1;
      aux=list1;
      list1 = list1->next;
    }
  }
  aux->next =NULL;      

  return(list);
}


