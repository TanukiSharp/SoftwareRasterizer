#include "ase.h"

void transform_vertex(t_matrix3x3* matrix, t_vertex* vertex)
{
    vertex->world_pos.x =
        matrix->components[0][0] * vertex->object_pos.x +
        matrix->components[1][0] * vertex->object_pos.y +
        matrix->components[2][0] * vertex->object_pos.z;

    vertex->world_pos.y =
        matrix->components[0][1] * vertex->object_pos.x +
        matrix->components[1][1] * vertex->object_pos.y +
        matrix->components[2][1] * vertex->object_pos.z;

    vertex->world_pos.z =
        matrix->components[0][2] * vertex->object_pos.x +
        matrix->components[1][2] * vertex->object_pos.y +
        matrix->components[2][2] * vertex->object_pos.z;
}
