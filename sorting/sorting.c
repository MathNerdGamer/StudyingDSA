#include "sorting.h"
#include "rendering.h"

// Bubble Sort
void bubble_sort(visualizer_t *viz)
{
    int end_index = viz->array_size - 1;

    while( end_index > 0 )
    {
        int last_swap = 0;

        for( int i = 0; i < end_index; ++i )
        {
            update_array(viz, RGB_MAGENTA, i, i + 1);

            if( compare_indices(viz, i, i + 1) > 0 )
            {
                swap(viz, i, i + 1);
                last_swap = i;
            }
        }

        end_index = last_swap;
    }
}

// Insertion Sort
void insertion_sort(visualizer_t *viz)
{
    insertion_base(viz, 0, viz->array_size - 1);
}

void insertion_base(visualizer_t *viz, int lo, int hi)
{
    for( int j = lo + 1; j <= hi; ++j )
    {
        int next_insert;
        set_to_variable(&next_insert, viz, j);

        int i = j - 1;

        update_array(viz, RGB_MAGENTA, i, j);
        while( i >= lo && compare_variable(next_insert, viz, i) < 0 )
        {
            update_array(viz, RGB_MAGENTA, i, j);
            set_at_index(viz, i + 1, i);

            --i;
        }

        set_from_variable(next_insert, viz, i + 1);
    }
}

// Selection Sort
void selection_sort(visualizer_t *viz)
{
    for( int i = 0; i < viz->array_size; ++i )
    {
        int min_index = i;

        for( int j = i + 1; j < viz->array_size; ++j )
        {
            update_array(viz, RGB_MAGENTA, min_index, j);
            if( compare_indices(viz, j, min_index) < 0 )
            {
                min_index = j;
            }
        }

        if( min_index != i )
        {
            swap(viz, i, min_index);
        }
    }
}

// Merge Sort
void merge_sort(visualizer_t *viz)
{
    merge_recurse(viz, 0, viz->array_size - 1);
    viz->recursion_level = -1;
}

void merge_recurse(visualizer_t *viz, int left, int right)
{
    ++viz->recursion_level;

    if( left < right )
    {
        int mid = left + (right - left) / 2;

        merge_recurse(viz, left, mid);
        merge_recurse(viz, mid + 1, right);
        merge(viz, left, mid, right);
    }

    --viz->recursion_level;
}

void merge(visualizer_t *viz, int left, int mid, int right)
{
    int left_size = mid + 1 - left;
    int right_size = right - mid;

    int *left_subarray = malloc(left_size * sizeof(int));
    int *right_subarray = malloc(right_size * sizeof(int));

    for( int i = 0; i < left_size; ++i )
    {
        set_to_subarray(left_subarray, i, viz, left + i);

        update_array_with_alert(viz,
                                RGB_BLUE,
                                left + i,
                                left + i,
                                RGB_YELLOW,
                                "Allocating left subarray");
    }

    for( int j = 0; j < right_size; ++j )
    {
        set_to_subarray(right_subarray, j, viz, mid + 1 + j);

        update_array_with_alert(viz,
                                RGB_BLUE,
                                mid + 1 + j,
                                mid + 1 + j,
                                RGB_YELLOW,
                                "Allocating right subarray");
    }

    int i = 0, j = 0, k = left;
    while( i < left_size && j < right_size )
    {
        if( compare_subarrays(viz, left_subarray, i, right_subarray, j) <= 0 )
        {
            set_from_subarray(left_subarray, i, viz, k);
            ++i;
        }
        else
        {
            set_from_subarray(right_subarray, j, viz, k);
            ++j;
        }

        update_array_with_alert(viz, RGB_MAGENTA, k, k, RGB_YELLOW, "Merging.");
        ++k;
    }

    while( i < left_size )
    {
        set_from_subarray(left_subarray, i, viz, k);

        update_array_with_alert(viz, RGB_MAGENTA, k, k, RGB_YELLOW, "Merging.");

        ++i;
        ++k;
    }

    while( j < right_size )
    {
        set_from_subarray(right_subarray, j, viz, k);

        update_array_with_alert(viz, RGB_MAGENTA, k, k, RGB_YELLOW, "Merging.");

        ++j;
        ++k;
    }

    free(left_subarray);
    free(right_subarray);
}

// Heap Sort
void heap_sort(visualizer_t *viz)
{
    heap_base(viz, 0, viz->array_size - 1);
}

void heap_base(visualizer_t *viz, int lo, int hi)
{
    heap_t *heap = build_heap(viz, lo, hi);

    for( int i = hi; i > lo; --i )
    {
        set_from_variable(remove_heap(heap, viz, lo), viz, i);
    }

    delete_heap(&heap);
}

// Partition Functions for Quick Sort & Intro Sort
void handle_pt(
    visualizer_t *viz, int lo, int hi, partition_scheme ps, pivot_type pt)
{
    switch( pt )
    {
        case RANDOM_PIVOT:
        {
            int random_index = lo + rand() % (hi - lo + 1);

            if( ps == HOARE_SCHEME )
            {
                swap(viz, lo, random_index);
            }
            else
            {
                swap(viz, hi, random_index);
            }

            break;
        }

        case MEDIAN_OF_THREE_PIVOT:
        {
            median_of_three(viz, lo, hi, ps);
            break;
        }

        case DEFAULT_PIVOT:
        default:
        {
            break;
        }
    }
}

void median_of_three(visualizer_t *viz, int lo, int hi, partition_scheme ps)
{
    int mid = lo + (hi - lo) / 2;

    if( ps == LOMUTO_SCHEME )
    {
        update_array(viz, RGB_MAGENTA, lo, mid);
        if( compare_indices(viz, mid, lo) < 0 )
        {
            swap(viz, lo, mid);
        }

        update_array(viz, RGB_MAGENTA, hi, lo);
        if( compare_indices(viz, hi, lo) < 0 )
        {
            swap(viz, hi, lo);
        }

        update_array(viz, RGB_MAGENTA, mid, hi);
        if( compare_indices(viz, mid, hi) < 0 )
        {
            swap(viz, mid, hi);
        }
    }
    else
    {
        update_array(viz, RGB_MAGENTA, lo, mid);
        if( compare_indices(viz, lo, mid) < 0 )
        {
            swap(viz, lo, mid);
        }

        update_array(viz, RGB_MAGENTA, hi, lo);
        if( compare_indices(viz, hi, lo) < 0 )
        {
            swap(viz, hi, lo);
        }

        update_array(viz, RGB_MAGENTA, hi, mid);
        if( compare_indices(viz, hi, mid) < 0 )
        {
            swap(viz, hi, mid);
        }
    }
}

int lomuto_partition(visualizer_t *viz, int lo, int hi, pivot_type pt)
{
    handle_pt(viz, lo, hi, LOMUTO_SCHEME, pt);

    int pivot;
    set_to_variable(&pivot, viz, hi);

    int i = lo;

    for( int j = lo; j < hi; ++j )
    {
        update_array(viz, RGB_MAGENTA, j, hi);

        if( compare_variable(pivot, viz, j) >= 0 )
        {
            swap(viz, i, j);
            ++i;
        }
    }

    swap(viz, i, hi);

    return i;
}

int hoare_partition(visualizer_t *viz, int lo, int hi, pivot_type pt)
{
    handle_pt(viz, lo, hi, HOARE_SCHEME, pt);

    int pivot;
    set_to_variable(&pivot, viz, lo);

    int i = lo - 1;
    int j = hi + 1;

    while( true )
    {
        do
        {
            ++i;
            update_array(viz, RGB_MAGENTA, i, find_index(viz, pivot));
        } while( compare_variable(pivot, viz, i) > 0 );

        do
        {
            --j;
            update_array(viz, RGB_MAGENTA, find_index(viz, pivot), j);
        } while( compare_variable(pivot, viz, j) < 0 );

        if( i >= j )
        {
            return j;
        }

        swap(viz, i, j);
    }
}

// Quick Sort
// Lomuto Partition Scheme
void lomuto_quick_sort(visualizer_t *viz)
{
    quick_recurse(viz, 0, viz->array_size - 1, LOMUTO_SCHEME, DEFAULT_PIVOT);
    viz->recursion_level = -1;
}

void lomuto_random_quick_sort(visualizer_t *viz)
{
    quick_recurse(viz, 0, viz->array_size - 1, LOMUTO_SCHEME, RANDOM_PIVOT);
    viz->recursion_level = -1;
}

void lomuto_median_quick_sort(visualizer_t *viz)
{
    quick_recurse(
        viz, 0, viz->array_size - 1, LOMUTO_SCHEME, MEDIAN_OF_THREE_PIVOT);
    viz->recursion_level = -1;
}

// Hoare Partition Scheme
void hoare_quick_sort(visualizer_t *viz)
{
    quick_recurse(viz, 0, viz->array_size - 1, HOARE_SCHEME, DEFAULT_PIVOT);
    viz->recursion_level = -1;
}

void hoare_random_quick_sort(visualizer_t *viz)
{
    quick_recurse(viz, 0, viz->array_size - 1, HOARE_SCHEME, RANDOM_PIVOT);
    viz->recursion_level = -1;
}

void hoare_median_quick_sort(visualizer_t *viz)
{
    quick_recurse(
        viz, 0, viz->array_size - 1, HOARE_SCHEME, MEDIAN_OF_THREE_PIVOT);
    viz->recursion_level = -1;
}

void quick_recurse(
    visualizer_t *viz, int lo, int hi, partition_scheme ps, pivot_type pt)
{
    if( lo >= hi || lo < 0 || hi < 0 )
    {
        return;
    }

    ++viz->recursion_level;

    int pivot;

    if( ps == HOARE_SCHEME )
    {
        pivot = hoare_partition(viz, lo, hi, pt);
        quick_recurse(viz, lo, pivot, ps, pt);
    }
    else
    {
        pivot = lomuto_partition(viz, lo, hi, pt);
        quick_recurse(viz, lo, pivot - 1, ps, pt);
    }

    quick_recurse(viz, pivot + 1, hi, ps, pt);
    --viz->recursion_level;
}

// IntroSort
void intro_sort(visualizer_t *viz)
{
    int limit = viz->recursion_limit = 2 * log2(viz->array_size);

    intro_recurse(viz, limit, 0, viz->array_size - 1);

    viz->recursion_level = viz->recursion_limit = -1;
}

void intro_recurse(visualizer_t *viz, int limit, int lo, int hi)
{
    if( lo >= hi || lo < 0 || hi < 0 )
    {
        return;
    }

    ++viz->recursion_level;

    if( hi - lo < 16 )
    {
        insertion_base(viz, lo, hi);
        --viz->recursion_level;
        return;
    }
    else if( !limit )
    {
        update_array_with_alert(
            viz,
            RGB_MAGENTA,
            -1,
            -1,
            RGB_RED,
            "Recursion Limit Exceeded: Falling back on to Heap Sort.");

        render_frames(viz, viz->framerate * 2);

        heap_base(viz, lo, hi);
        --viz->recursion_level;
        return;
    }

    int pivot = hoare_partition(viz, lo, hi, RANDOM_PIVOT);

    intro_recurse(viz, limit - 1, lo, pivot);
    intro_recurse(viz, limit - 1, pivot + 1, hi);

    --viz->recursion_level;
}

// Bogo Sort
int const MAX_ATTEMPTS = 10;
void randomize_array(visualizer_t *viz)
{
    for( int i = viz->array_size - 1; i >= 0; --i )
    {
        int j = rand() % (i + 1);

        update_array_with_alert(
            viz, RGB_CYAN, i, j, RGB_YELLOW, "RANDOMIZING!");

        swap(viz, i, j);

        update_array_with_alert(
            viz, RGB_CYAN, i, j, RGB_YELLOW, "RANDOMIZING!");
    }
}

void check_success(visualizer_t *viz, bool const sorted, int const attempts)
{
    if( !sorted && (attempts >= MAX_ATTEMPTS) )
    {
        text_alert(viz, RGB_RED, "FAILED!");
        render_frames(viz, viz->framerate * 1.5);
    }
    else if( sorted )
    {
        text_alert(viz, RGB_GREEN, "SUCCESS!");
        render_frames(viz, viz->framerate * 1.5);
    }
    else
    {
        randomize_array(viz);
    }
}

void bogo_sort(visualizer_t *viz)
{
    bool sorted = false;
    int attempts = 0;

    while( !sorted && (attempts < MAX_ATTEMPTS) )
    {
        ++attempts;
        sorted = true;

        for( int i = 0; i < viz->array_size - 1; ++i )
        {
            update_array(viz, RGB_MAGENTA, i, i + 1);
            render_frames(viz, viz->framerate * 0.25);

            if( compare_indices(viz, i, i + 1) > 0 )
            {
                sorted = false;
                break;
            }
        }

        check_success(viz, sorted, attempts);
    }
}

// Slow Sort
void slow_sort(visualizer_t *viz)
{
    slow_base(viz, 0, viz->array_size - 1);
}

void slow_base(visualizer_t *viz, int lo, int hi)
{
    if( lo >= hi )
    {
        return;
    }

    ++viz->recursion_level;

    int mid = lo + (hi - lo) / 2;

    slow_base(viz, lo, mid);
    slow_base(viz, mid + 1, hi);

    update_array(viz, RGB_MAGENTA, hi, mid);
    if( compare_indices(viz, hi, mid) < 0 )
    {
        swap(viz, hi, mid);
    }

    slow_base(viz, lo, hi - 1);

    --viz->recursion_level;
}
