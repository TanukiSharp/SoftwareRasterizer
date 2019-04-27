#include "ase.h"
#include "rasterizer.h"

void transform_object(t_matrix3x3* matrix, t_model* model)
{
    int i;

    for (i = 0; i < model->vertices_count; i++)
        transform_vertex(matrix, &model->vertices[i]);
}
