#include <stdio.h>
#include <stdlib.h>

void LIS(int, char **);

int main(int argc, char *argv[])
{
    if( argc > 1 )
    {
        LIS(argc - 1, argv + 1);
    }
    else
    {
        printf("%s [ints...]\n", argv[0]);
    }
}

void LIS(int count, char **numbers)
{
    int *A = malloc(count * sizeof(int));
    int *L = malloc(count * sizeof(int));

    for( int i = 0; i < count; ++i )
    {
        A[i] = atoi(numbers[i]);
    }

    L[0] = 1;

    for( int k = 1; k < count; ++k )
    {
        int T = 0;
        for( int j = 0; j < k; ++j )
        {
            if( A[j] < A[k] && T < L[j] )
            {
                T = L[j];
            }
        }

        L[k] = 1 + T;
    }

    int length = 0;
    int max_index = 0;

    for( int i = 0; i < count; ++i )
    {
        if( length < L[i] )
        {
            length = L[i];
            max_index = i;
        }
    }

    int *S = malloc(length * sizeof(int));
    S[length - 1] = A[max_index];
    int current = max_index;

    for( int i = max_index - 1, j = 1; i >= 0 && j < length; --i )
    {
        if( L[i] == L[current] - 1 && A[i] < A[current] )
        {
            S[length - 1 - j] = A[i];
            ++j;
            current = i;
        }
    }

    printf("Longest increasing subsequence has length %d.\n", L[max_index]);

    for( int i = 0; i < length; ++i )
    {
        printf("%d", S[i]);

        if( i != length - 1 )
        {
            printf(", ");
        }
        else
        {
            printf("\n");
        }
    }

    free(S);
    free(L);
    free(A);
}