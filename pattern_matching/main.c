#include <stdio.h>
#include "bm.h"
#include "kmp.h"
#include "rk.h"

char *test_text = "Hello, this is a test text for this algorithm.";
char *test_pattern = "is";

int main()
{
    printf("Boyer-Moore\n");
    array_t *indices = boyer_moore(test_text, test_pattern);

    for( int i = 0; i < indices->size; ++i )
    {
        printf("Found at index %ld.\n", indices->array[i]);
    }

    delete_array(&indices);

    printf("\nKnuth-Morris-Pratt\n");

    indices = knuth_morris_pratt(test_text, test_pattern);

    for( int i = 0; i < indices->size; ++i )
    {
        printf("Found at index %ld.\n", indices->array[i]);
    }

    delete_array(&indices);

    printf("\nRabin-Karp\n");

    indices = rabin_karp(test_text, test_pattern);

    for( int i = 0; i < indices->size; ++i )
    {
        printf("Found at index %ld.\n", indices->array[i]);
    }

    delete_array(&indices);
}