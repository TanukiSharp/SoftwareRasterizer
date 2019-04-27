#include <stdio.h>
#include <stdlib.h>
#include "rasterizer.h"
#include "ase.h"

t_model* ase_read_file(char* filename)
{
	int vertices_count;
    int faces_count;
	char* original_file_buffer;
    char* file_ptr;

    t_vertex* vertices;
    t_face* faces;
    t_model* model;

	original_file_buffer = read_file(filename);
	if (original_file_buffer == NULL)
		return NULL;

    file_ptr = original_file_buffer;

    file_ptr = ase_get_vertices_count(file_ptr, &vertices_count);
    if (file_ptr == NULL)
        return NULL;

    if (vertices_count == 0)
    {
        printf("File '%s' contains no vertices.\n", filename);
        return NULL;
    }

    file_ptr = ase_get_faces_count(file_ptr, &faces_count);
    if (file_ptr == NULL)
        return NULL;

    if (faces_count == 0)
    {
        printf("File '%s' contains no faces.\n", filename);
        return NULL;
    }

    vertices = malloc(vertices_count * sizeof(t_vertex));
    if (vertices == NULL)
    {
        malloc_error(vertices_count);
        return NULL;
    }

    faces = malloc(faces_count * sizeof(t_face));
    if (faces == NULL)
    {
        malloc_error(faces_count);
        return NULL;
    }

    model = malloc(sizeof(t_model));
    if (model == NULL)
    {
        malloc_error(sizeof(t_model));
        return NULL;
    }

    model->vertices_count = vertices_count;
    model->faces_count = faces_count;

    model->vertices = vertices;
    model->faces = faces;

	file_ptr = ase_read_vertices(file_ptr, model);
    file_ptr = ase_read_faces(file_ptr, model);

	free(original_file_buffer);

    return model;
}
