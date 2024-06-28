#include <stdio.h>
#include <string.h>
#include "deque.h"

int main([[maybe_unused]] int argc, [[maybe_unused]] char **argv)
{
    deque_t *deque = CREATE_DEQUE(int);

    constexpr int PRIME = 11;

    for( int i = 0; i < PRIME; ++i )
    {
        int number = (7 * (i + 3)) % PRIME;
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

    pop_front(deque, NULL);
    printf("\npop_front()\n");
    printf("top(): %d\n", *( int * )top(deque));
    printf("bottom(): %d\n", *( int * )bottom(deque));
    printf("size: %zu\n", deque->size);
    printf("capacity: %zu\n", deque->capacity);
    printf("type size: %zu\n", deque->type_size);

    pop_back(deque, NULL);
    printf("\npop_back()\n");
    printf("top(): %d\n", *( int * )top(deque));
    printf("bottom(): %d\n", *( int * )bottom(deque));
    printf("size: %zu\n", deque->size);
    printf("capacity: %zu\n", deque->capacity);
    printf("type size: %zu\n", deque->type_size);

    int result;
    pop_back(deque, &result);
    printf("\npop_back() with result\n");
    printf("top(): %d\n", *( int * )top(deque));
    printf("bottom(): %d\n", *( int * )bottom(deque));
    printf("size: %zu\n", deque->size);
    printf("capacity: %zu\n", deque->capacity);
    printf("type size: %zu\n", deque->type_size);
    printf("result of pop_back(): %d\n", result);

    delete_deque(&deque);
}
