#include "ase.h"
#include "rasterizer.h"
#include "../RenderLibrary/renderlib.h"

void fill_triangle(int color, t_context* context)
{
	int x;
	int y;
    int xmin;
    int xmax;
    int ymin;
    int ymax;
    t_horizontal_boundaries* rows;

    ymin = context->boundaries.ymin;
    ymax = context->boundaries.ymax;
    rows = context->boundaries.rows;

    if (ymin < 0 && ymax < 0)
        return;

	for (y = ymin; y <= ymax; y++)
	{
        xmin = rows[y].xmin;
        xmax = rows[y].xmax;

		for (x = xmin; x <= xmax; x++)
			renderlib_set_pixel(x, y, color);
	}
}
