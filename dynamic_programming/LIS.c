#include <stdio.h>
#include <stdlib.h>

int LIS(int, char **);

int main(int argc, char *argv[])
{
    if( argc > 1 )
    {
        printf("Longest increasing subsequence has length %d.\n",
               LIS(argc - 1, argv + 1));
    }
    else
    {
        printf("%s [ints...]\n", argv[0]);
    }
}

int LIS(int count, char **numbers)
{
    int *A = malloc(count * sizeof(int));
    int *S = malloc(count * sizeof(int));

    for( int i = 0; i < count; ++i )
    {
        A[i] = atoi(numbers[i]);
    }

    S[0] = 1;

    for( int k = 1; k < count; ++k )
    {
        int T = 0;
        for( int j = 0; j < k; ++j )
        {
            if( A[j] < A[k] && T < S[j] )
            {
                T = S[j];
            }
        }

        S[k] = 1 + T;
    }

    int length = 0;

    for( int i = 0; i < count; ++i )
    {
        if( length < S[i] )
        {
            length = S[i];
        }
    }

    free(S);
    free(A);

    return length;
}