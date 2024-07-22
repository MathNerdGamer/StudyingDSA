#ifndef MATH_NERD_BINARY_SEARCH_TREE_H
#define MATH_NERD_BINARY_SEARCH_TREE_H
#include <quiet_vscode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

typedef struct node
{
    void *data;
    struct node *parent;
    struct node *left;
    struct node *right;
} node_t;

typedef struct
{
    node_t *root;

    size_t size;

    int (*comparator)(void *, void *);
    void (*printer)(void *);
    void (*deleter)(void *);
} bst_t;

bst_t *create_bst(int (*comparator)(void *, void *),
                  void (*printer)(void *),
                  void (*deleter)(void *));

node_t *create_node(void *, node_t *);

node_t *find_previous_node(bst_t *, void *);
node_t *find_node(bst_t *, void *);

void insert_node(bst_t *, void *);
bool contains(bst_t *, void *);
void *remove_node(bst_t *, void *);

void *remove_leaf(bst_t *, node_t *);
void *remove_one_child(bst_t *, node_t *);
void *remove_two_child(bst_t *, node_t *);

void clear(bst_t *);
void clear_recursive(node_t *, void (*deleter)(void *));

void pre_order_print(bst_t *);
void pre_order_traverse(bst_t *, void (*func)(void *));
void pre_order_recurse(node_t *, void (*func)(void *));

void in_order_print(bst_t *);
void in_order_traverse(bst_t *, void (*func)(void *));
void in_order_recurse(node_t *, void (*func)(void *));

void post_order_print(bst_t *);
void post_order_traverse(bst_t *, void (*func)(void *));
void post_order_recurse(node_t *, void (*func)(void *));

void level_order_print(bst_t *);
void level_order_traverse(bst_t *, void (*func)(void *));

bool is_empty(bst_t *);

void delete_bst(bst_t **);

#define CREATE_BST(t) create_bst(t##_cmp, t##_print, t##_delete)

#endif // MATH_NERD_BINARY_SEARCH_TREE_H