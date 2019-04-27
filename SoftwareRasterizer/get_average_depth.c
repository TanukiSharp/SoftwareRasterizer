#include "ase.h"

double get_average_depth(int face_index, t_model* model)
{
    double average_z;

    average_z =
        model->vertices[model->faces[face_index].v1].world_pos.z +
        model->vertices[model->faces[face_index].v2].world_pos.z +
        model->vertices[model->faces[face_index].v3].world_pos.z;

    return average_z;
}
