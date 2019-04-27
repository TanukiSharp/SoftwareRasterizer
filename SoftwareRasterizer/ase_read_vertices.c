#include "ase.h"
#include "rasterizer.h"

char* ase_read_vertices(char* ptr, t_model* model)
{
    char* temp_ptr;

    while (1)
    {
		temp_ptr = strstr(ptr, "*MESH_VERTEX ");

        if (temp_ptr == NULL)
            return ptr;

        ptr = temp_ptr + 13;

		ase_extract_vertex(ptr, model->vertices);
	}
}
