#include <stdlib.h>
#include <math.h>
#include "ase.h"
#include "rasterizer.h"

int project_x(double x, double z, t_context* context)
{
    double coef_x;
    double depth;

    coef_x = x * context->projection_coef;
    depth = z + context->camera.z;

    if (fabs(depth) < 1e-3)
        return coef_x >= 0.0 ? WIN_WIDTH + 1 : -1;

    return (int)round((coef_x / depth) + context->camera.x);
}

int project_y(double y, double z, t_context* context)
{
    double coef_y;
    double depth;

    coef_y = y * context->projection_coef;
    depth = z + context->camera.z;

    if (fabs(depth) < 1e-3)
        return coef_y <= 0.0 ? WIN_HEIGHT + 1 : -1;

    return (int)round(WIN_HEIGHT - ((coef_y / depth) + context->camera.y));
}
