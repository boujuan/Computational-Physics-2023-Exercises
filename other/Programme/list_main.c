#include <stdio.h>
#include <stdlib.h>

#include "list.h"



int main(int argc, char *argv[])
{
  elem_t *list, *elem, *elem2;
  
  list = NULL;
  elem = create_element(6);
  list = insert_element(list, elem, NULL);
  elem = create_element(5);
  list = insert_element(list, elem, NULL);
  elem2 = create_element(7);
  list = insert_element(list, elem2, NULL);
  elem = create_element(4);
  list = insert_element(list, elem, NULL);
  elem = create_element(8);
  list = insert_element(list, elem, /*NULL*/ elem2);
  print_list(list);

  /*list = list_invert(list);
    print_list(list);*/
  /*list = mergesort_list(list);
  printf("sort list\n");
  print_list(list);*/

  /*printf("delete 7:\n");
  elem = search_info(list, 7);
  list = remove_element(list, elem);
  delete_element(elem);
  print_list(list);*/

  /*printf("delete first element\n");
  elem = list;
  list = remove_element(list, elem);
  delete_element(elem);
  print_list(list);*/

  return(0);
}
