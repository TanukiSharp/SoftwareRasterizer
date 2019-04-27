#define _USE_MATH_DEFINES
#include <math.h>
#include "ase.h"
#include "rasterizer.h"
#include "../RenderLibrary/renderlib.h"

#define M_PI2 (M_PI * 2.0)

void draw_loop(t_context* params, t_model* model)
{
    double object_angle;
    double light_angle;
    t_matrix3x3 rotation;

    object_angle = 0.0;
    light_angle = 0.0;

    while (1)
    {
        renderlib_sync_start();

        renderlib_clear();

        if (object_angle >= M_PI2)
            object_angle -= M_PI2;

        object_angle += 0.04;

        if (light_angle >= M_PI2)
            light_angle -= M_PI2;

        light_angle -= 0.015;

        create_rotation_matrix(0.5, 0.0, object_angle, &rotation);

        transform_object(&rotation, model);
        transform_normals(&rotation, model);

        create_rotation_matrix(0.0, light_angle, 0.0, &rotation);

        transform_vertex(&rotation , &params->light);

        quick_sort_faces(0, model->faces_count - 1, model);
        draw_model(0x80A0FF, params, model);

        renderlib_update();

        renderlib_sync_end(60, 1);
    }
}
