#ifndef __RASTERIZER_H__
#define __RASTERIZER_H__

#include "ase.h"
#include "../RenderLibrary/renderlib.h"

typedef	struct s_context
{
    double projection_coef;
    t_vertex light;
    t_position camera;
    t_boundaries boundaries;
} t_context;

void draw_triangle(COLOR color, t_context* context, t_model* model, int face_index);
void draw_model(COLOR color, t_context* context, t_model* model);
void swap_structs(int i, int j, t_face* faces);
void draw_loop(t_context* param, t_model* model);
void translate(int x, int y, int z, t_model* model);
double compute_lighting_coef(t_position* light, t_model* model, int face_index);
int project_x(double x, double z, t_context* param);
int project_y(double y, double z, t_context* param);
void fill_triangle(int color, t_context* context);
void init_boundaries(t_boundaries* boundaries);
void draw_line(int x1, int y1, int x2, int y2, COLOR color, t_boundaries* boundaries);
void create_rotation_matrix(double x_angle, double y_angle, double z_angle, t_matrix3x3* matrix);
void transform_object(t_matrix3x3* matrix, t_model* model);
void transform_normals(t_matrix3x3* matrix, t_model* model);
void transform_vertex(t_matrix3x3* matrix, t_vertex* vertex);
double get_average_depth(int numface, t_model* model);
void quick_sort_faces(int start, int end, t_model* model);

char* read_file(char* filename);
char* skip_spaces(char* str);
char* skip_non_spaces(char* str);
void malloc_error(long byte_count);

#endif // __RASTERIZER_H__
