#ifndef MATRIX_H
#define MATRIX_H

#include <armadillo>

using namespace arma;

class matrix
{
public:
    static mat get_turn_matrix(double a, double b, double c);
    static mat get_scale_matrix(double a, double b, double c);
    static mat get_rotate_round_ox_matrix(double cos_alpha, double sin_alpha);
    static mat get_rotate_round_oy_matrix(double cos_alpha, double sin_alpha);
    static mat get_rotate_round_oz_matrix(double cos_alpha, double sin_alpha);
};

#endif // MATRIX_H
