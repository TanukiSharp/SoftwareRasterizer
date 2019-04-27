#include "ase.h"
#include "rasterizer.h"

char* ase_read_faces(char* ptr, t_model* model)
{
    char* temp_ptr;

    while (1)
    {
        temp_ptr = strstr(ptr, "*MESH_FACE ");

        if (temp_ptr == NULL)
            return ptr;

        ptr = temp_ptr + 11;

        ase_extract_faces(ptr, model);
    }
}
