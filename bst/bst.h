#ifndef MATH_NERD_BST_H
#define MATH_NERD_BST_H
#include <quiet_vscode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    void *data;
    struct node *left;
    struct node *right;
} node_t;

typedef struct
{
    node_t *root;

    size_t size;

    int (*comparator)(void *, void *);
    void (*printer)(void *, void *);
    void (*deleter)(void *);
} bst_t;

#endif // MATH_NERD_BST_H