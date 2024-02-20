#ifndef _LIST_H_
#define _LIST_H_

/** data types **/

/* data structures for list elements */
struct elem_struct
{
    int                 info;               /* holds ``information'' */
    struct elem_struct *next;  /* points to successor (NULL if last) */
};

typedef struct elem_struct elem_t;       /* define new type for nodes */

/** function prototypes **/
extern elem_t *create_element(int value);
extern int delete_element(elem_t *elem);
extern elem_t *insert_element(elem_t *list, elem_t *elem, elem_t *where);
extern void print_list(elem_t *list);
extern void write_list(elem_t *list, FILE *file);
extern elem_t *search_info(elem_t *list, int value);
extern elem_t *remove_element(elem_t *list, elem_t *elem);
extern elem_t *remove_value(elem_t *list, int value);
extern elem_t *mergesort_list(elem_t *list);
extern elem_t *list_invert(elem_t *list);



#endif
