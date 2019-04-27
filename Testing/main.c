#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include "../RenderLibrary/renderlib.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

void main()
{
	int x;
	int y;
	double angle;
	COLOR* buffer;

	const double radius = 150.0;

	angle = 0.0;

	renderlib_create_window(L"Software Rasterizer", WIN_WIDTH, WIN_HEIGHT);
	buffer = renderlib_get_color_buffer();

	while (1)
	{
        renderlib_sync_start();
		renderlib_clear();

		x = (int)round(radius * cos(angle));
		y = (int)round(radius * sin(angle));

		renderlib_draw_line(
			(WIN_WIDTH / 2) + x,
			(WIN_HEIGHT / 2) + y,
			(WIN_WIDTH / 2),
			(WIN_HEIGHT / 2),
			0xFF0000
		);

        renderlib_draw_line(
            (WIN_WIDTH / 2) - x,
            (WIN_HEIGHT / 2) - y,
            (WIN_WIDTH / 2),
            (WIN_HEIGHT / 2),
            0xFF00
        );

		angle += M_PI / 30.0;

		renderlib_update();
        renderlib_sync_end(60, 1);
    }
}
