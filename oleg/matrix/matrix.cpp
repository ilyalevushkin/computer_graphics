#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "matrix.h"

mat matrix::get_turn_matrix(double a, double b, double c)
{
    mat A(4,4);
    A << 1 << 0 << 0 << 0 << endr
      << 0 << 1 << 0 << 0 << endr
      << 0 << 0 << 1 << 0 << endr
      << a << b << c << 1 << endr;
    return A;
}

mat matrix::get_scale_matrix(double a, double b, double c)
{
    mat A(4,4);
    A << a << 0 << 0 << 0 << endr
      << 0 << b << 0 << 0 << endr
      << 0 << 0 << c << 0 << endr
      << 0 << 0 << 0 << 1 << endr;
    return A;
}

mat matrix::get_rotate_round_ox_matrix(double cos_alpha, double sin_alpha)
{
    mat A(4,4);
    A << 1 << 0          << 0         << 0 << endr
      << 0 << cos_alpha  << sin_alpha << 0 << endr
      << 0 << -sin_alpha << cos_alpha << 0 << endr
      << 0 << 0          << 0         << 1 << endr;
    return A;
}

mat matrix::get_rotate_round_oy_matrix(double cos_alpha, double sin_alpha)
{
    mat A(4,4);
    A << cos_alpha << 0 << -sin_alpha << 0 << endr
      << 0         << 1 << 0          << 0 << endr
      << sin_alpha << 0 << cos_alpha  << 0 << endr
      << 0         << 0 << 0          << 1 << endr;
    return A;
}

mat matrix::get_rotate_round_oz_matrix(double cos_alpha, double sin_alpha)
{
    mat A(4,4);
    A << cos_alpha  << sin_alpha << 0 << 0 << endr
      << -sin_alpha << cos_alpha << 0 << 0 << endr
      << 0          << 0         << 1 << 0 << endr
      << 0          << 0         << 0 << 1 << endr;
    return A;
}


#endif // MATRIX_HPP
