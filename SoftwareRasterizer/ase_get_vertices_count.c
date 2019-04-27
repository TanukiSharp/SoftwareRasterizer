#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ase_get_vertices_count(char* ptr, int* vertices_count)
{
    ptr = strstr(ptr, "*MESH_NUMVERTEX ");

    if (ptr == NULL)
    {
        printf("Failed to find MESH_NUMVERTEX marker.\n");
        return NULL;
    }

    ptr += 16;

    *vertices_count = atoi(ptr);

    return ptr;
}
