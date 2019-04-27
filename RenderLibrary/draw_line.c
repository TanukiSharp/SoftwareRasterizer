#include "renderlib.h"

void renderlib_draw_horizontal_line(int x1, int x2, int y, COLOR color)
{
	int x;

	for (x = x1; x <= x2; x++)
		renderlib_set_pixel(x, y, color);
}

void renderlib_draw_vertical_line(int x, int y1, int y2, COLOR color)
{
	int y;

	for (y = y1; y <= y2; y++)
		renderlib_set_pixel(x, y, color);
}

void renderlib_draw_larger_dx(int x1, int y1, int x2, int y2, COLOR color)
{
	int x;
	int y;

	for (x = x1; x <= x2; x++)
	{
		y = y1 + ((y2 - y1) * (x - x1)) / (x2 - x1);
		renderlib_set_pixel(x, y, color);
	}
}

void renderlib_draw_larger_dy(int x1, int y1, int x2, int y2, COLOR color)
{
	int x;
	int y;

	for (y = y1; y <= y2; y++)
	{
		x = x1 + ((x2 - x1) * (y - y1)) / (y2 - y1);
		renderlib_set_pixel(x, y, color);
	}
}

void renderlib_draw_line(int x1, int y1, int x2, int y2, COLOR color)
{
	int dx;
	int dy;

	dx = abs(x2 - x1);
	dy = abs(y2 - y1);

	if (dx == 0 && dy == 0)
		renderlib_set_pixel(x1, y1, color);
	else if (dx == 0)
	{
		if (y1 < y2)
			renderlib_draw_vertical_line(x1, y1, y2, color);
		else
			renderlib_draw_vertical_line(x1, y2, y1, color);
	}
	else if (dy == 0)
	{
		if (x1 > x2)
			renderlib_draw_horizontal_line(x1, x2, y1, color);
		else
			renderlib_draw_horizontal_line(x2, x1, y1, color);
	}
	else if (dx >= dy)
	{
		if (x1 <= x2)
			renderlib_draw_larger_dx(x1, y1, x2, y2, color);
		else
			renderlib_draw_larger_dx(x2, y2, x1, y1, color);
	}
	else // if (dy > dx)
	{
		if (y1 <= y2)
			renderlib_draw_larger_dy(x1, y1, x2, y2, color);
		else
			renderlib_draw_larger_dy(x2, y2, x1, y1, color);
	}
}
