#ifndef MATH_NERD_DYNAMIC_ARRAY_H
#define MATH_NERD_DYNAMIC_ARRAY_H
#include <quiet_vscode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int64_t *array;
    size_t capacity;
    size_t size;
} array_t;

array_t *create_array();
void array_add(array_t *, int64_t);
void rebuild_array(array_t *);
void delete_array(array_t **);

#endif // MATH_NERD_DYNAMIC_ARRAY_H