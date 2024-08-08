#ifndef MATH_NERD_SORTING_MAX_HEAP_H
#define MATH_NERD_SORTING_MAX_HEAP_H
#include <quiet_vscode.h>
#include <stdio.h>
#include <stdlib.h>
#include "rendering.h"
#include "utility.h"

typedef struct
{
    int *array;
    int size;
} heap_t;

int left_child(int);
int right_child(int);
int parent(int);
int convert_index(int, int);

void down_heap(heap_t *, int, visualizer_t *, int, char *);
int remove_heap(heap_t *, visualizer_t *, int);
heap_t *build_heap(visualizer_t *, int, int);

void delete_heap(heap_t **);

#endif // MATH_NERD_SORTING_MAX_HEAP_H