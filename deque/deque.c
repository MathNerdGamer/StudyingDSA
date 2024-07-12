#include "deque.h"

deque_t *create_deque(size_t type_size)
{
    deque_t *deque = malloc(sizeof(deque_t));

    deque->array = malloc(3 * type_size);
    deque->type_size = type_size;
    deque->size = 0;
    deque->capacity = 3;
    deque->front = 0;
    deque->back = 0;

    return deque;
}

void rebuild_deque(deque_t *deque)
{
    if( !deque )
    {
        return;
    }

    size_t new_capacity = deque->capacity + deque->capacity / 2;

    void *new_array = malloc(new_capacity * deque->type_size);

    memcpy(new_array,
           ( byte * )deque->array + deque->type_size * deque->front,
           deque->type_size * (deque->size - deque->front));

    if( deque->back < deque->front )
    {
        memcpy(( byte * )new_array +
                   deque->type_size * (deque->size - deque->front),
               deque->array,
               deque->type_size * deque->back);
    }

    free(deque->array);
    deque->array = new_array;
    deque->capacity = new_capacity;
    deque->front = 0;
    deque->back = deque->size - 1;
}

void delete_deque(deque_t **deque)
{
    if( !deque || !*deque )
    {
        return;
    }

    free((*deque)->array);
    free(*deque);
    *deque = nullptr;
}

void push_front(deque_t *deque, void *data)
{
    if( !deque || !data )
    {
        return;
    }

    if( deque->size == 0 && deque->front == deque->back )
    {
        deque->front = 1;
    }
    else if( deque->size == deque->capacity )
    {
        rebuild_deque(deque);
    }

    deque->front += deque->capacity - 1;
    deque->front %= deque->capacity;

    memcpy(( byte * )deque->array + deque->type_size * deque->front,
           data,
           deque->type_size);
    ++deque->size;
}

void push_back(deque_t *deque, void *data)
{
    if( !deque || !data )
    {
        return;
    }

    if( deque->size == 0 && deque->front == deque->back )
    {
        deque->back = -1;
    }
    else if( deque->size == deque->capacity )
    {
        rebuild_deque(deque);
    }

    ++deque->back;
    deque->back %= deque->capacity;

    memcpy(( byte * )deque->array + deque->type_size * deque->back,
           data,
           deque->type_size);
    ++deque->size;
}

void *top(deque_t *deque)
{
    if( !deque )
    {
        return nullptr;
    }

    return ( byte * )deque->array + deque->type_size * deque->front;
}

void *bottom(deque_t *deque)
{
    if( !deque )
    {
        return nullptr;
    }

    return ( byte * )deque->array + deque->type_size * deque->back;
}

bool pop_front(deque_t *deque, void *return_reference)
{
    if( !deque || deque->size == 0 )
    {
        return false;
    }

    void *data = ( byte * )deque->array + deque->type_size * deque->front;
    ++deque->front;
    deque->front %= deque->capacity;
    --deque->size;

    if( return_reference )
    {
        memcpy(return_reference, data, deque->type_size);
    }
    memset(data, 0, deque->type_size);

    return true;
}

bool pop_back(deque_t *deque, void *return_reference)
{
    if( !deque || deque->size == 0 )
    {
        return false;
    }

    void *data = ( byte * )deque->array + deque->type_size * deque->back;
    deque->back += deque->capacity - 1;
    deque->back %= deque->capacity;
    --deque->size;

    if( return_reference )
    {
        memcpy(return_reference, data, deque->type_size);
    }
    memset(data, 0, deque->type_size);

    return true;
}

void clear_deque(deque_t *deque)
{
    if( !deque )
    {
        return;
    }

    memset(deque->array, 0, deque->type_size * deque->capacity);
    deque->front = deque->back = deque->size = 0;
}
