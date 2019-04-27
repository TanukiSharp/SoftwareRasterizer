#include <time.h>
#include "ase.h"
#include "rasterizer.h"
#include "../RenderLibrary/renderlib.h"

void main(int ac, char** av)
{
    char* filename;
    COLOR* buffer;
    t_context context;
    t_model* model;

    context.light.object_pos.x = 1;
    context.light.object_pos.y = -500;
    context.light.object_pos.z = 0;

    context.light.world_pos.x = context.light.object_pos.x;
    context.light.world_pos.y = context.light.object_pos.y;
    context.light.world_pos.z = context.light.object_pos.z;

    context.camera.x = WIN_WIDTH / 2;
    context.camera.y = WIN_HEIGHT / 2;
    context.camera.z = 256;

    context.projection_coef = 250.0;

    renderlib_create_window(L"Software Rasterizer", WIN_WIDTH, WIN_HEIGHT);
    buffer = renderlib_get_color_buffer();

    if (ac == 1)
        filename = "..\\Samples\\dragon.ase";
    else
        filename = av[1];

    model = ase_read_file(filename);
    if (model == NULL)
        return;

    draw_loop(&context, model);
}
