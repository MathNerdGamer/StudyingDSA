#include "kmp.h"

void generate_failure_table(char const *const pattern, int m, int64_t *table)
{
    table[0] = 0;

    for( int pidx = 0, qidx = 1; qidx < m; /* blank */ )
    {
        if( pattern[qidx] == pattern[pidx] )
        {
            table[qidx] = pidx + 1;
            ++pidx;
            ++qidx;
        }
        else if( pidx == 0 )
        {
            table[qidx] = 0;
            ++qidx;
        }
        else
        {
            pidx = table[pidx - 1];
        }
    }
}

array_t *knuth_morris_pratt(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);

    int64_t *failure = malloc(m * sizeof(int64_t));
    generate_failure_table(pattern, m, failure);

    array_t *indices = create_array();

    for( int tidx = 0, pidx = 0; tidx < n; /* blank */ )
    {
        if( pattern[pidx] == text[tidx] )
        {
            if( pidx == m - 1 )
            {
                array_add(indices, tidx - pidx);
                pidx = failure[pidx];
            }
            else
            {
                ++pidx;
            }

            ++tidx;
        }
        else if( pidx == 0 )
        {
            ++tidx;
        }
        else
        {
            pidx = failure[pidx - 1];
        }
    }

    free(failure);

    if( indices->size == 0 )
    {
        delete_array(&indices);
    }

    return indices;
}