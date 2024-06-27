#include <stdio.h>
#include <string.h>
#include "deque.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    deque_t *deque = CREATE_DEQUE(int);

    for( int i = 0; i < 11; ++i )
    {
        int number = (7 * (i + 3)) % 11;
        printf("push_back(%d)\n", number);
        push_back(deque, &number);
    }

    printf("\nOriginal Deque\n");
    printf("top(): %d\n", *( int * )top(deque));
    printf("bottom(): %d\n", *( int * )bottom(deque));
    printf("size: %zu\n", deque->size);
    printf("capacity: %zu\n", deque->capacity);
    printf("type size: %zu\n", deque->type_size);

    int push = 17;
    push_front(deque, &push);
    printf("\npush_front(17)\n");
    printf("top(): %d\n", *( int * )top(deque));
    printf("bottom(): %d\n", *( int * )bottom(deque));
    printf("size: %zu\n", deque->size);
    printf("capacity: %zu\n", deque->capacity);
    printf("type size: %zu\n", deque->type_size);

    push = 12;
    push_back(deque, &push);
    printf("\npush_back(12)\n");
    printf("top(): %d\n", *( int * )top(deque));
    printf("bottom(): %d\n", *( int * )bottom(deque));
    printf("size: %zu\n", deque->size);
    printf("capacity: %zu\n", deque->capacity);
    printf("type size: %zu\n", deque->type_size);

    pop_front(deque);
    printf("\npop_front()\n");
    printf("top(): %d\n", *( int * )top(deque));
    printf("bottom(): %d\n", *( int * )bottom(deque));
    printf("size: %zu\n", deque->size);
    printf("capacity: %zu\n", deque->capacity);
    printf("type size: %zu\n", deque->type_size);

    pop_back(deque);
    printf("\npop_back()\n");
    printf("top(): %d\n", *( int * )top(deque));
    printf("bottom(): %d\n", *( int * )bottom(deque));
    printf("size: %zu\n", deque->size);
    printf("capacity: %zu\n", deque->capacity);
    printf("type size: %zu\n", deque->type_size);

    delete_deque(&deque);
}
