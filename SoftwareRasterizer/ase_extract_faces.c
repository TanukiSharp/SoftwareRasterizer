#include "ase.h"

void ase_extract_faces(char* str, t_model* model)
{
    int index;

    index = atoi(str);
	str = strchr(str, ':') + 1;

	str = strchr(str, ':') + 1;
    model->faces[index].v1 = atoi(str);

	str = strchr(str, ':') + 1;
    model->faces[index].v2 = atoi(str);

	str = strchr(str, ':') + 1;
    model->faces[index].v3 = atoi(str);

    ase_compute_normal_vector(model, index);
}
