#ifndef __ASE_H__
#define __ASE_H__

#include "../RenderLibrary/renderlib.h"

#define WIN_WIDTH 640
#define WIN_HEIGHT 480

#define X 0
#define Y 1
#define Z 2

typedef	struct s_position
{
    double x;
    double y;
    double z;
} t_position;

typedef	struct s_vertex
{
    t_position object_pos;
    t_position world_pos;
} t_vertex;

typedef	struct s_horizontal_boundaries
{
    int xmin;
    int xmax;
} t_horizontal_boundaries;

typedef struct s_boundaries
{
    int ymin;
    int ymax;
    t_horizontal_boundaries rows[WIN_HEIGHT];
} t_boundaries;

typedef	struct s_face
{
    int v1;
    int v2;
    int v3;
    t_vertex normal;
} t_face;

typedef struct s_model
{
    int vertices_count;
    int faces_count;
    t_vertex* vertices;
    t_face* faces;
} t_model;

typedef struct s_matrix3x3
{
    double components[3][3];
} t_matrix3x3;

void ase_extract_faces(char* str, t_model* model);
void ase_extract_vertex(char* ptr, t_vertex* vertices);
char* ase_get_faces_count(char* ptr, int* faces_count);
char* ase_get_vertices_count(char* ptr, int* vertices_count);
char* ase_read_vertices(char* ptr, t_model* model);
char* ase_read_faces(char* ptr, t_model* model);
t_model* ase_read_file(char* filename);

void ase_compute_normal_vector(t_model* model, int face_index);

#endif // __ASE_H__
