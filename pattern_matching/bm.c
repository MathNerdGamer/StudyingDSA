#include "bm.h"

void generate_last_occurrence_table(char const *const pattern,
                                    int m,
                                    int64_t table[])
{
    for( int i = 0; i < 128; ++i )
    {
        table[i] = -1;
    }

    for( int pidx = 0; pidx < m; ++pidx )
    {
        table[pattern[pidx]] = pidx;
    }
}

array_t *boyer_moore(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);

    int64_t last_occurrence[128];
    generate_last_occurrence_table(pattern, m, last_occurrence);

    array_t *indices = create_array();

    for( int tidx = 0; tidx <= n - m; /* blank */ )
    {
        int pidx = m - 1;
        for( /* blank */; pidx >= 0 && text[tidx + pidx] == pattern[pidx];
             --pidx )
        { // Intentionally left blank.
        }

        if( pidx == -1 )
        {
            array_add(indices, tidx);
        }

        int shift = last_occurrence[pattern[pidx]];

        if( shift < pidx )
        {
            tidx += pidx - shift;
        }
        else
        {
            ++tidx;
        }
    }

    if( indices->size == 0 )
    {
        delete_array(&indices);
    }

    return indices;
}
