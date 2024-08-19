#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *LCS(char **);

int main(int argc, char *argv[])
{
    if( argc > 1 )
    {
        char *subseq = LCS(argv + 1);

        printf("Longest common subsequence is %s, which has length %lu.\n",
               subseq,
               strlen(subseq));

        free(subseq);
    }
    else
    {
        printf("%s [string1] [string2]\n", argv[0]);
    }
}

char *LCS(char **strings)
{
    int m = strlen(strings[0]);
    int n = strlen(strings[1]);

    int *S = malloc((m + 1) * (n + 1) * sizeof(int));

    for( int i = 0; i <= m; ++i )
    {
        S[i] = 0;
    }

    for( int j = 1; j <= n; ++j )
    {
        S[j * (m + 1)] = 0;
    }

    for( int i = 1; i <= m; ++i )
    {
        for( int j = 1; j <= n; ++j )
        {
            if( strings[0][i - 1] == strings[1][j - 1] )
            {
                S[i + (m + 1) * j] = 1 + S[(i - 1) + (m + 1) * (j - 1)];
            }
            else
            {
                if( S[(i - 1) + (m + 1) * j] < S[i + (m + 1) * (j - 1)] )
                {
                    S[i + (m + 1) * j] = S[i + (m + 1) * (j - 1)];
                }
                else
                {
                    S[i + (m + 1) * j] = S[(i - 1) + (m + 1) * j];
                }
            }
        }
    }

    int length = S[m + (m + 1) * n];

    char *subseq = malloc(length + 1);
    subseq[length] = '\0';

    int i = m, j = n, k = length - 1;

    while( i > 0 && j > 0 )
    {
        if( strings[0][i - 1] == strings[1][j - 1] )
        {
            subseq[k] = strings[0][i - 1];
            --i;
            --j;
            --k;
        }
        else
        {
            if( S[(i - 1) + (m + 1) * j] < S[i + (m + 1) * (j - 1)] )
            {
                --j;
            }
            else
            {
                --i;
            }
        }
    }

    free(S);
    return subseq;
}
