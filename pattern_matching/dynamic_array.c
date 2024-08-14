#include "dynamic_array.h"

array_t *create_array()
{
    array_t *array = malloc(sizeof(array_t));

    array->array = malloc(3 * sizeof(int64_t));
    array->capacity = 3;
    array->size = 0;

    memset(array->array, -1, 3 * sizeof(int64_t));

    return array;
}

void array_add(array_t *array, int64_t data)
{
    if( !array )
    {
        return;
    }

    if( array->size == array->capacity )
    {
        rebuild_array(array);
    }

    array->array[array->size] = data;
    ++array->size;
}

void rebuild_array(array_t *array)
{
    if( !array )
    {
        return;
    }

    size_t new_capacity = array->capacity + array->capacity / 2;

    int64_t *new_array = malloc(new_capacity * sizeof(int64_t));

    memcpy(new_array, array->array, array->size * sizeof(int64_t));

    free(array->array);

    array->array = new_array;
    array->capacity = new_capacity;
}

void delete_array(array_t **array)
{
    if( !array || !*array )
    {
        return;
    }

    free((*array)->array);
    free(*array);

    *array = nullptr;
}