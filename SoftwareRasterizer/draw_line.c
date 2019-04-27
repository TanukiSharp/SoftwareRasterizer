#include "ase.h"

void draw_dot(int x, int y, t_boundaries* boundaries)
{
    if (boundaries->rows[y].xmin > x)
        boundaries->rows[y].xmin = x;
    if (boundaries->rows[y].xmax < x)
        boundaries->rows[y].xmax = x;
}

void draw_horizontal_line(int x1, int x2, int y, t_boundaries* boundaries)
{
    if (boundaries->rows[y].xmin > x1)
        boundaries->rows[y].xmin = x1;

    if (boundaries->rows[y].xmax < x2)
        boundaries->rows[y].xmax = x2;
}

void draw_vertical_line(int x, int y1, int y2, t_boundaries* boundaries)
{
    int y;

    y = y1;

    while (y <= y2)
    {
        if (boundaries->rows[y].xmin > x)
            boundaries->rows[y].xmin = x;
        if (boundaries->rows[y].xmax < x)
            boundaries->rows[y].xmax = x;

        y++;
    }
}

void draw_larger_dx(int x1, int y1, int x2, int y2, t_boundaries* boundaries)
{
    int x;
    int y;

    x = x1;

    while (x <= x2)
    {
        y = y1 + ((y2 - y1) * (x - x1)) / (x2 - x1);

        if (boundaries->rows[y].xmin > x)
            boundaries->rows[y].xmin = x;

        if (boundaries->rows[y].xmax < x)
            boundaries->rows[y].xmax = x;

        x++;
    }
}

void draw_larger_dy(int x1, int y1, int x2, int y2, t_boundaries* boundaries)
{
    int x;
    int y;

    y = y1;

    while (y <= y2)
    {
        x = x1 + ((x2 - x1) * (y - y1)) / (y2 - y1);

        if (boundaries->rows[y].xmin > x)
            boundaries->rows[y].xmin = x;
        if (boundaries->rows[y].xmax < x)
            boundaries->rows[y].xmax = x;

        y++;
    }
}

void draw_line(int x1, int y1, int x2, int y2, COLOR color, t_boundaries* boundaries)
{
    int dx;
    int dy;

    dx = abs(x2 - x1);
    dy = abs(y2 - y1);

    if (dx == 0 && dy == 0)
        draw_dot(x1, y1, boundaries);
    else if (dx == 0)
    {
        if (y1 < y2)
            draw_vertical_line(x1, y1, y2, boundaries);
        else
            draw_vertical_line(x1, y2, y1, boundaries);
    }
    else if (dy == 0)
    {
        if (x1 > x2)
            draw_horizontal_line(x1, x2, y1, boundaries);
        else
            draw_horizontal_line(x2, x1, y1, boundaries);
    }
    else if (dx >= dy)
    {
        if (x1 <= x2)
            draw_larger_dx(x1, y1, x2, y2, boundaries);
        else
            draw_larger_dx(x2, y2, x1, y1, boundaries);
    }
    else // if (dy > dx)
    {
        if (y1 <= y2)
            draw_larger_dy(x1, y1, x2, y2, boundaries);
        else
            draw_larger_dy(x2, y2, x1, y1, boundaries);
    }
}
