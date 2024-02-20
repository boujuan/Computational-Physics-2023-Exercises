#include <stdio.h>
#include <stdlib.h>

/* data structures for list elements */
struct elem_struct
{
    int                 info;               /* holds ``information'' */
    struct elem_struct *next;  /* points to successor (NULL if last) */
};

typedef struct elem_struct elem_t;       /* define new type for nodes */

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

  /* INSERT YOUR CODE HERE */
}


/****************** remove_element() **************/
/** Remove given element from list without       **/
/** deleting it.                                 **/
/** PARAMETERS: (*)= return-paramter             **/
/**           list: first element of list        **/
/**           elem: to be removed                **/
/** RETURNS:                                     **/
/**  (new) pointer to beginning of the list      **/
/**************************************************/
elem_t *remove_element(elem_t *list, elem_t *elem)
{
  /* INSERT YOUR CODE HERE */

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
  /* INSERT YOUR CODE HERE */

  return(list);
}


int main(int argc, char *argv[])
{
  elem_t *list, *elem, *elem2;
  
  list = NULL;
  elem = create_element(5);
  list = insert_element(list, elem, NULL);
  elem2 = create_element(3);
  list = insert_element(list, elem2, NULL);
  elem2 = create_element(6);
  list = insert_element(list, elem2, elem);
  elem2 = create_element(10);
  list = insert_element(list, elem2, elem);
  elem2 = create_element(7);
  list = insert_element(list, elem2, elem);
  print_list(list);

  /* THIS SHOULD WORK WITH THE FUNCTION YOU HAVE IMPLEMENTED: */

  /*list = mergesort_list(list);
  printf("sort list\n");
  print_list(list);*/

  /*list = list_invert(list);
  printf("invert list\n");
  print_list(list);*/

  /* printf("delete 6:\n");
  elem = search_info(list, 6);
  list = remove_element(list, elem);
  delete_element(elem);
  print_list(list); 

  printf("delete first element\n");
  elem = list;
  list = remove_element(list, elem);
  delete_element(elem);
  print_list(list);*/

  return(0);
}
