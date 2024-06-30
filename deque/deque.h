#ifndef MATH_NERD_DEQUE_H
#define MATH_NERD_DEQUE_H
#include <quiet_vscode.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    void *array;
    size_t type_size;

    size_t size;
    size_t capacity;

    size_t front;
    size_t back;
} deque_t;

typedef unsigned char byte;

// Create a deque.
deque_t *create_deque(size_t);

// Rebuild deque.
void rebuild_deque(deque_t *);

// Delete a deque.
void delete_deque(deque_t **);

// Push functions.
void push_front(deque_t *, void *);
void push_back(deque_t *, void *);

// Peek functions.
void *top(deque_t *);
void *bottom(deque_t *);

// Pop functions.
bool pop_front(deque_t *, void *);
bool pop_back(deque_t *, void *);

// Clear deque.
void clear_deque(deque_t *);

// Deque instantiation macro
#define CREATE_DEQUE(t) create_deque(sizeof(t));

#endif // MATH_NERD_DEQUE_H