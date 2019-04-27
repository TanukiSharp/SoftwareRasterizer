#include <math.h>
#include "ase.h"

void create_rotation_matrix(double x_angle, double y_angle, double z_angle, t_matrix3x3* matrix)
{
    double cosxa;
    double cosya;
    double cosza;

    double sinxa;
    double sinya;
    double sinza;

    cosxa = cos(x_angle);
    cosya = cos(y_angle);
    cosza = cos(z_angle);

    sinxa = sin(x_angle);
    sinya = sin(y_angle);
    sinza = sin(z_angle);

    matrix->components[0][0] = cosya * cosza;
    matrix->components[1][0] = sinya * cosza;
    matrix->components[2][0] = -sinza;

    matrix->components[0][1] = cosya * sinza * sinxa - sinya * cosxa;
    matrix->components[1][1] = sinya * sinza * sinxa + cosxa * cosya;
    matrix->components[2][1] = sinxa * cosza;

    matrix->components[0][2] = cosya * sinza * cosxa + sinya * sinxa;
    matrix->components[1][2] = sinya * sinza * cosxa - cosya * sinxa;
    matrix->components[2][2] = cosxa * cosza;
}
