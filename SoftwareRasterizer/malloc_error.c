#include <stdlib.h>
#include <stdio.h>

void malloc_error(long byte_count)
{
    printf("Failed to allocate %ld bytes, out of memory, u mad?\n", byte_count);
    exit(1);
}
