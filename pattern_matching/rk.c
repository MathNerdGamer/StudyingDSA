#include "rk.h"

uint64_t simple_hash(char *key, int m, int p)
{
    uint64_t hash = 0;

    for( int i = 0; i < m; ++i )
    {
        hash *= p;
        hash += key[i];
    }

    return hash;
}

array_t *rabin_karp(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    constexpr int PRIME = 33;

    uint64_t pattern_hash = simple_hash(pattern, m, PRIME);

    array_t *indices = create_array();

    for( int tidx = 0; tidx < n - m; ++tidx )
    {
        if( simple_hash(text + tidx, m, PRIME) == pattern_hash )
        {
            int pidx;

            for( pidx = 0; pidx < m && text[tidx + pidx] == pattern[pidx];
                 ++pidx )
            {
                // Intentionally left blank.
            }

            if( pidx == m )
            {
                array_add(indices, tidx);
            }
        }
    }

    if( indices->size == 0 )
    {
        delete_array(&indices);
    }

    return indices;
}