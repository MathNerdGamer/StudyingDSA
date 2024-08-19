#include <stdio.h>
#include <stdlib.h>

int LIS(int, char **);

int main(int argc, char *argv[])
{
    if( argc > 1 )
    {
        printf("Largest contiguous sum: %d\n", LIS(argc, argv));
    }
    else
    {
        printf("%s [ints...]\n", argv[0]);
    }
}

int LIS(int count, char **numbers)
{
    int global_max = 0;
    int local_max = 0;

    for( int k = 0; k < count; ++k )
    {
        int value = atoi(numbers[k]);

        if( global_max < 0 )
        {
            global_max = 0;
        }

        if( local_max < global_max )
        {
            local_max = global_max;
        }

        global_max += value;
    }

    if( local_max > global_max )
    {
        global_max = local_max;
    }

    return global_max;
}