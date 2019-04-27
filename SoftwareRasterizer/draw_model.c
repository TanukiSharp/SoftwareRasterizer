#include "ase.h"
#include "rasterizer.h"

void draw_model(COLOR color, t_context* context, t_model* model)
{
    int i;

    for (i = 0; i < model->faces_count; i++)
        draw_triangle(color, context, model, i);
}
