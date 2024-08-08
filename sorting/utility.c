#include "utility.h"

char const *order[3] = {"Random", "Sorted", "Reverse"};
char const *lower_order[3] = {"random", "sorted", "reverse"};

void swap(visualizer_t *viz, int i, int j)
{
    viz->accesses += 4;
    ++viz->swaps;
    int temp = viz->array[i];
    viz->array[i] = viz->array[j];
    viz->array[j] = temp;
}

void set_to_variable(int *var, visualizer_t *viz, int index)
{
    ++viz->accesses;
    *var = viz->array[index];
}

void set_from_variable(int var, visualizer_t *viz, int index)
{
    ++viz->accesses;
    viz->array[index] = var;
}

int compare_variable(int var, visualizer_t *viz, int index)
{
    ++viz->accesses;
    ++viz->comparisons;
    return var - viz->array[index];
}

void set_at_index(visualizer_t *viz, int i, int j)
{
    viz->accesses += 2;
    viz->array[i] = viz->array[j];
}

int compare_indices(visualizer_t *viz, int i, int j)
{
    viz->accesses += 2;
    ++viz->comparisons;
    return viz->array[i] - viz->array[j];
}

void set_to_subarray(int *subarray, int sub_index, visualizer_t *viz, int index)
{
    viz->accesses += 2;
    subarray[sub_index] = viz->array[index];
}

void set_from_subarray(int *subarray,
                       int sub_index,
                       visualizer_t *viz,
                       int index)
{
    viz->accesses += 2;
    viz->array[index] = subarray[sub_index];
}

int compare_subarrays(visualizer_t *viz, int *sub1, int i, int *sub2, int j)
{
    ++viz->comparisons;
    viz->accesses += 2;
    return sub1[i] - sub2[j];
}

float fraction_to_float(char *str)
{
    char *ch = strchr(str, '/');

    if( !ch )
    {
        return ( float )atoi(str);
    }

    char temp[256];

    snprintf(
        temp, MIN(( unsigned long )(ch - str + 1), sizeof(temp)), "%s", str);

    int numerator = atoi(temp);

    snprintf(temp, sizeof(temp), "%s", ch + 1);
    int denominator = atoi(temp);

    return (( float )numerator) / denominator;
}

void shuffle_array(visualizer_t *viz)
{
    // Fisher-Yates Shuffle
    for( int i = viz->array_size - 1; i >= 0; --i )
    {
        int j = rand() % (i + 1);
        swap(viz, i, j);
    }
}

void inversion_count(visualizer_t *viz)
{
    viz->inversions = 0;
    for( int i = 0; i < viz->array_size - 1; ++i )
    {
        for( int j = i + 1; j < viz->array_size; ++j )
        {
            if( viz->array[i] > viz->array[j] )
            {
                ++viz->inversions;
            }
        }
    }
}

int find_index(visualizer_t *viz, int value)
{
    for( int i = 0; i < viz->array_size; ++i )
    {
        if( viz->array[i] == value )
        {
            return i;
        }
    }

    return -1;
}

char const *order_title(visualizer_t *viz)
{
    if( viz->random )
    {
        return order[0];
    }

    if( viz->sorted )
    {
        return order[1];
    }

    return order[2];
}

char const *lower_order_title(visualizer_t *viz)
{
    if( viz->random )
    {
        return lower_order[0];
    }

    if( viz->sorted )
    {
        return lower_order[1];
    }

    return lower_order[2];
}