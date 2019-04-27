#include "ase.h"

void init_boundaries(t_boundaries* boundaries)
{
	int i;

    boundaries->ymin = -1;
    boundaries->ymax = -1;

	for (i = 0; i < WIN_HEIGHT; i++)
	{
		boundaries->rows[i].xmin = WIN_WIDTH + 1;
		boundaries->rows[i].xmax = -1;
	}
}
