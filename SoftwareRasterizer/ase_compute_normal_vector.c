#include "ase.h"

void ase_compute_normal_vector(t_model* model, int face_index)
{
    double a[3];
    double b[3];
    t_vertex* vertices;
    t_face* face;
    t_vertex* normal;

    vertices = model->vertices;
    face = &model->faces[face_index];
    normal = &model->faces[face_index].normal;

    a[X] = vertices[face->v1].object_pos.x - vertices[face->v2].object_pos.x;
    a[Y] = vertices[face->v1].object_pos.y - vertices[face->v2].object_pos.y;
    a[Z] = vertices[face->v1].object_pos.z - vertices[face->v2].object_pos.z;

    b[X] = vertices[face->v1].object_pos.x - vertices[face->v3].object_pos.x;
    b[Y] = vertices[face->v1].object_pos.y - vertices[face->v3].object_pos.y;
    b[Z] = vertices[face->v1].object_pos.z - vertices[face->v3].object_pos.z;

    normal->object_pos.x = a[Y] * b[Z] - a[Z] * b[Y];
    normal->object_pos.y = a[Z] * b[X] - a[X] * b[Z];
    normal->object_pos.z = a[X] * b[Y] - a[Y] * b[X];

    normal->world_pos.x = normal->object_pos.x;
    normal->world_pos.y = normal->object_pos.y;
    normal->world_pos.z = normal->object_pos.z;
}
