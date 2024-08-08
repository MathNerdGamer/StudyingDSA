#ifndef MATH_NERD_SORTING_H
#define MATH_NERD_SORTING_H
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include "max_heap.h"
#include "utility.h"

// Bubble Sort
void bubble_sort(visualizer_t *);

// Insertion Sort
void insertion_sort(visualizer_t *);
void insertion_base(visualizer_t *, int, int);

// Selection Sort
void selection_sort(visualizer_t *);

// Merge Sort
void merge_sort(visualizer_t *);
void merge_recurse(visualizer_t *, int, int);
void merge(visualizer_t *, int, int, int);

// Heap Sort
void heap_sort(visualizer_t *);
void heap_base(visualizer_t *, int, int);

// Partition Functions for Quick Sort & Intro Sort
typedef enum
{
    DEFAULT_PIVOT,
    RANDOM_PIVOT,
    MEDIAN_OF_THREE_PIVOT
} pivot_type;

typedef enum
{
    LOMUTO_SCHEME,
    HOARE_SCHEME
} partition_scheme;

void handle_pt(visualizer_t *, int, int, partition_scheme, pivot_type);

void median_of_three(visualizer_t *, int, int, partition_scheme);

int lomuto_partition(visualizer_t *, int, int, pivot_type);
int hoare_partition(visualizer_t *, int, int, pivot_type);

// Quick Sort
void lomuto_quick_sort(visualizer_t *);
void lomuto_random_quick_sort(visualizer_t *);
void lomuto_median_quick_sort(visualizer_t *);

void hoare_quick_sort(visualizer_t *);
void hoare_random_quick_sort(visualizer_t *);
void hoare_median_quick_sort(visualizer_t *);

void quick_recurse(visualizer_t *, int, int, partition_scheme, pivot_type);

// IntroSort
void intro_sort(visualizer_t *);
void intro_recurse(visualizer_t *, int, int, int);

// Bogo Sort
void randomize_array(visualizer_t *);
void check_success(visualizer_t *, bool, int);
void bogo_sort(visualizer_t *);

// Slow Sort
void slow_sort(visualizer_t *);
void slow_base(visualizer_t *, int, int);

#endif // MATH_NERD_SORTING_H