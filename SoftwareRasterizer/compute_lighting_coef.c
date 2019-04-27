#include <math.h>
#include "ase.h"

double compute_lighting_coef(t_position* light, t_model* model, int face_index)
{
    double k;
    double face_norm;
    double light_norm;
    double fn[3];
    double ln[3];
    double face_pos[3];
    t_vertex* vertices;
    t_face* face;

    vertices = model->vertices;
    face = &model->faces[face_index];

    face_pos[X] = (vertices[face->v1].world_pos.x + vertices[face->v2].world_pos.x + vertices[face->v3].world_pos.x) / 3.0;
    face_pos[Y] = (vertices[face->v1].world_pos.y + vertices[face->v2].world_pos.y + vertices[face->v3].world_pos.y) / 3.0;
    face_pos[Z] = (vertices[face->v1].world_pos.z + vertices[face->v2].world_pos.z + vertices[face->v3].world_pos.z) / 3.0;

    ln[X] = light->x - face_pos[X];
    ln[Y] = light->y - face_pos[Y];
    ln[Z] = light->z - face_pos[Z];

    fn[X] = face->normal.world_pos.x;
    fn[Y] = face->normal.world_pos.y;
    fn[Z] = face->normal.world_pos.z;

    face_norm = sqrt(fn[X] * fn[X] + fn[Y] * fn[Y] + fn[Z] * fn[Z]);
    light_norm = sqrt(ln[X] * ln[X] + ln[Y] * ln[Y] + ln[Z] * ln[Z]);

    k = (fn[X] * ln[X] + fn[Y] * ln[Y] + fn[Z] * ln[Z]) / (face_norm * light_norm);

    if (k < 0.0)
        k = -k;

    if (k > 1.0 + 1e5)
        k = 1.0;

    return k * 0.75 + 0.25;
}
