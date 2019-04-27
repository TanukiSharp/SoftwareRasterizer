#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* ase_get_faces_count(char* ptr, int* faces_count)
{
    ptr = strstr(ptr, "*MESH_NUMFACES ");

    if (ptr == NULL)
    {
        printf("Failed to find MESH_NUMFACES marker.\n");
        return NULL;
    }

    ptr += 15;

    *faces_count = atoi(ptr);

    return ptr;
}
