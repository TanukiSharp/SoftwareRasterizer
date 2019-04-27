#include "ase.h"
#include "rasterizer.h"

void quick_sort_faces(int start, int end, t_model* model)
{
    int i;
    int j;
    double mid;

    i = start;
    j = end;
    mid = get_average_depth((start + end) / 2, model);

    while (i <= j)
    {
        while (get_average_depth(i, model) > mid)
            i++;

        while (get_average_depth(j, model) < mid)
            j--;

        if (i <= j)
        {
            swap_structs(i, j, model->faces);
            i++;
            j--;
        }
    }

    if (i < end)
        quick_sort_faces(i, end, model);

    if (start < j)
        quick_sort_faces(start, j, model);
}
