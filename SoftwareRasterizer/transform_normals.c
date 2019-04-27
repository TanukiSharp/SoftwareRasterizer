#include "ase.h"
#include "rasterizer.h"

void transform_normals(t_matrix3x3* matrix, t_model* model)
{
    int i;

    for (i = 0; i < model->faces_count; i++)
        transform_vertex(matrix, &model->faces[i].normal);
}
