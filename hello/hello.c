#include <stdio.h>

int main()
{
#ifdef TEST
    printf("Hello, world!\n");
#else
    printf("What's this?\n");
#endif
}