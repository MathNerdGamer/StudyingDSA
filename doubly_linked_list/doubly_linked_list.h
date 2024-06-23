#ifndef MATH_NERD_DOUBLY_LINKED_LIST_H
#define MATH_NERD_DOUBLY_LINKED_LIST_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    void *data;
    struct node *next;
    struct node *prev;
} node_t;

typedef struct
{
    node_t *head;
    node_t *tail;

    size_t size;

    int (*comparator)(void *, void *);
    void (*printer)(void *, void *);
    void (*deleter)(void *);
} linked_list_t;

// Node creation and deletion.
node_t *create_node(void *);

// List creation and deletion.
linked_list_t *create_linked_list(int (*compare)(void *, void *),
                                  void (*print)(void *, void *),
                                  void (*delete)(void *));

void delete_linked_list(linked_list_t **);

// Insertion function
void insert(linked_list_t *, void *);

// Access functions
void *access_at_head(linked_list_t const *const);
void *access_at_tail(linked_list_t const *const);
void *access_at_index(linked_list_t const *const, size_t const);
void *access_by_value(linked_list_t const *const, void *);

// Removal functions
void *remove_at_head(linked_list_t *);
void *remove_at_tail(linked_list_t *);
void *remove_at_index(linked_list_t *, size_t const);
void *remove_by_value(linked_list_t *, void *);
void clear_list(linked_list_t *);

// Utility functions
void print_list(linked_list_t const *const, FILE *);
bool contains(linked_list_t const *const, void *);
size_t get_size(linked_list_t const *const);

// Linked list instantiation macro
#define CREATE_LINKED_LIST(t)                                                  \
    create_linked_list(t##_cmp, t##_print, t##_delete);

#endif // MATH_NERD_DOUBLY_LINKED_LIST_H