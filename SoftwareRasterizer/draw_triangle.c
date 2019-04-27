#include <math.h>
#include "ase.h"
#include "rasterizer.h"
#include "../RenderLibrary/renderlib.h"

void draw_triangle(COLOR color, t_context* context, t_model* model, int face_index)
{
	double x[3];
    double y[3];
    double z[3];
    int miny;
    int maxy;
    int projected_x[3];
    int projected_y[3];
	unsigned char r;
	unsigned char g;
	unsigned char b;
	double k;
    t_vertex* vertices;
    t_face* face;

    vertices = model->vertices;
    face = &model->faces[face_index];

	init_boundaries(&context->boundaries);

	x[0] = vertices[face->v1].world_pos.x;
	x[1] = vertices[face->v2].world_pos.x;
	x[2] = vertices[face->v3].world_pos.x;

	y[0] = vertices[face->v1].world_pos.y;
	y[1] = vertices[face->v2].world_pos.y;
	y[2] = vertices[face->v3].world_pos.y;

	z[0] = vertices[face->v1].world_pos.z;
	z[1] = vertices[face->v2].world_pos.z;
	z[2] = vertices[face->v3].world_pos.z;

	if (y[0] < -context->camera.z || y[1] < -context->camera.z || y[2] < -context->camera.z)
		return;

	projected_x[0] = project_x(x[0], z[0], context);
	projected_x[1] = project_x(x[1], z[1], context);
	projected_x[2] = project_x(x[2], z[2], context);

	projected_y[0] = project_y(y[0], z[0], context);
	projected_y[1] = project_y(y[1], z[1], context);
	projected_y[2] = project_y(y[2], z[2], context);

	k = compute_lighting_coef(&context->light.world_pos, model, face_index);

	r = (unsigned char)(((color >> 16) & 0xFF) * k);
	g = (unsigned char)(((color >> 8) & 0xFF) * k);
	b = (unsigned char)((color & 0xFF) * k);

	color = (COLOR)(r << 16) + (g << 8) + b;

    miny = projected_y[0];
    if (miny > projected_y[1])
        miny = projected_y[1];
    if (miny > projected_y[2])
        miny = projected_y[2];
    if (miny < 0)
        miny = 0;

    maxy = projected_y[0];
    if (maxy < projected_y[1])
        maxy = projected_y[1];
    if (maxy < projected_y[2])
        maxy = projected_y[2];
    if (maxy > WIN_HEIGHT - 1)
        maxy = WIN_HEIGHT - 1;

    context->boundaries.ymin = miny;
    context->boundaries.ymax = maxy;

	draw_line(projected_x[0], projected_y[0], projected_x[1], projected_y[1], color, &context->boundaries);
	draw_line(projected_x[1], projected_y[1], projected_x[2], projected_y[2], color, &context->boundaries);
	draw_line(projected_x[2], projected_y[2], projected_x[0], projected_y[0], color, &context->boundaries);

    fill_triangle(color, context);
}
