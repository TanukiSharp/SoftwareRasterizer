#include <stdio.h>
#include "ase.h"
#include "rasterizer.h"

void ase_extract_vertex(char* ptr, t_vertex* vertices)
{
	int num;
	double coord;

    ptr = skip_spaces(ptr);
	num = atoi(ptr);
    ptr = skip_non_spaces(ptr);

	ptr = skip_spaces(ptr);
	coord = atof(ptr);
	ptr = skip_non_spaces(ptr);
    vertices[num].object_pos.x = coord;
    vertices[num].world_pos.x = coord;

	ptr = skip_spaces(ptr);
	coord = atof(ptr);
	ptr = skip_non_spaces(ptr);
    vertices[num].object_pos.z = coord;
    vertices[num].world_pos.z = coord;

	ptr = skip_spaces(ptr);
	coord = atof(ptr);
	ptr = skip_non_spaces(ptr);
    vertices[num].object_pos.y = coord;
    vertices[num].world_pos.y = coord;
}
