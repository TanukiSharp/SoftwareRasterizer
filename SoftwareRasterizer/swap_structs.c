#include "ase.h"

void swap_structs(int i, int j, t_face* faces)
{
    t_face temp;

    temp = faces[i];
    faces[i] = faces[j];
    faces[j] = temp;
}
