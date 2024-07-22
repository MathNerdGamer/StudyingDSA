#ifndef MATH_NERD_AVL_TREE_H
#define MATH_NERD_AVL_TREE_H
#include <quiet_vscode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "deque.h"

typedef struct node
{
    void *data;

    size_t height;

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
} avl_t;

avl_t *create_avl(int (*comparator)(void *, void *),
                  void (*printer)(void *),
                  void (*deleter)(void *));

node_t *create_node(void *);
node_t *find_node(avl_t *, void *);

int node_height(node_t *);
void update_height(node_t *);
int balance_factor(node_t *);

node_t *left_rotate(node_t *);
node_t *right_rotate(node_t *);

node_t *rebalance_node(node_t *);

void insert_node(avl_t *, void *);
node_t *insert_recursive(avl_t *, node_t *, void *);

bool contains(avl_t *, void *);

void *remove_node(avl_t *, void *);
node_t *remove_recursive(avl_t *, node_t *, node_t **, void *);

node_t *remove_leaf(avl_t *, node_t *, node_t **);
node_t *remove_one_child(avl_t *, node_t *, node_t **);
node_t *remove_two_child(avl_t *, node_t *, node_t **);

void clear(avl_t *);
void clear_recursive(node_t *, void (*deleter)(void *));

void pre_order_print(avl_t *);
void pre_order_traverse(avl_t *, void (*func)(void *));
void pre_order_recurse(node_t *, void (*func)(void *));

void in_order_print(avl_t *);
void in_order_traverse(avl_t *, void (*func)(void *));
void in_order_recurse(node_t *, void (*func)(void *));

void post_order_print(avl_t *);
void post_order_traverse(avl_t *, void (*func)(void *));
void post_order_recurse(node_t *, void (*func)(void *));

void level_order_print(avl_t *);
void level_order_traverse(avl_t *, void (*func)(void *));

bool is_empty(avl_t *);

void delete_avl(avl_t **);

#define CREATE_AVL(t) create_avl(t##_cmp, t##_print, t##_delete)

#define MAX(a, b) ((a < b) ? b : a)

#endif // MATH_NERD_AVL_TREE_H