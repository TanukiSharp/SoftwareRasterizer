#include "ase.h"

void translate(int x, int y, int z, t_model* model)
{
    int i;

    for (i = 0; i < model->vertices_count; i++)
    {
        model->vertices[i].world_pos.x += x;
        model->vertices[i].world_pos.y += z;
        model->vertices[i].world_pos.z += y;
    }
}
