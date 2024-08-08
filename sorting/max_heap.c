#include "max_heap.h"

int left_child(int index)
{
    return 2 * index + 1;
}

int right_child(int index)
{
    return 2 * index + 2;
}

int parent(int index)
{
    if( index == 0 )
    {
        return -1;
    }

    if( index % 2 == 0 )
    {
        return (index - 1) / 2;
    }

    return index / 2;
}

int convert_index(int index, int lo)
{
    return lo + index;
}

void down_heap(heap_t *heap, int index, visualizer_t *viz, int lo, char *msg)
{
    if( !heap )
    {
        return;
    }

    while( index < heap->size )
    {
        int left = left_child(index);
        int right = right_child(index);

        bool left_swap =
            (left < heap->size) &&
            (compare_indices(
                 viz, convert_index(index, lo), convert_index(left, lo)) < 0);

        bool right_swap =
            (right < heap->size) &&
            (compare_indices(
                 viz, convert_index(index, lo), convert_index(right, lo)) < 0);

        if( left < heap->size )
        {
            update_array_with_alert(viz,
                                    RGB_MAGENTA,
                                    convert_index(left, lo),
                                    convert_index(index, lo),
                                    RGB_YELLOW,
                                    msg);
        }

        if( right < heap->size )
        {
            update_array_with_alert(viz,
                                    RGB_MAGENTA,
                                    convert_index(right, lo),
                                    convert_index(index, lo),
                                    RGB_YELLOW,
                                    msg);
        }

        int new_index = 0;

        if( left_swap && right_swap )
        {
            if( compare_indices(viz,
                                convert_index(right, lo),
                                convert_index(left, lo)) < 0 )
            {
                right_swap = false;
            }
            else
            {
                left_swap = false;
            }

            update_array_with_alert(viz,
                                    RGB_MAGENTA,
                                    convert_index(left, lo),
                                    convert_index(right, lo),
                                    RGB_YELLOW,
                                    msg);
        }

        if( left_swap )
        {
            new_index = left;
        }
        else if( right_swap )
        {
            new_index = right;
        }
        else
        {
            break;
        }

        swap(viz, convert_index(index, lo), convert_index(new_index, lo));

        index = new_index;
    }
}

int remove_heap(heap_t *heap, visualizer_t *viz, int lo)
{
    if( !heap || heap->size == 0 )
    {
        return -1;
    }

    int data;
    set_to_variable(&data, viz, 0);

    set_at_index(viz, convert_index(0, lo), convert_index(heap->size - 1, lo));
    --heap->size;

    down_heap(heap, 0, viz, lo, "Remove Head and Heapify");
    return data;
}

heap_t *build_heap(visualizer_t *viz, int lo, int hi)
{
    if( !viz->array )
    {
        return nullptr;
    }

    heap_t *heap = malloc(sizeof(heap_t));
    heap->size = hi - lo + 1;
    heap->array = viz->array + lo;

    for( int i = parent(heap->size - 1); i >= 0; --i )
    {
        down_heap(heap, i, viz, lo, "Build Heap");
    }

    return heap;
}

void delete_heap(heap_t **heap)
{
    if( !heap || !*heap )
    {
        return;
    }

    free(*heap);
    *heap = nullptr;
}
