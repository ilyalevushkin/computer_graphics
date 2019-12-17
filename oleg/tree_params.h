#ifndef TREE_PARAMS_H
#define TREE_PARAMS_H

struct start_dot
{
    double x;
    double y;
    double z;
};

struct body
{
    double length;
};

struct tree_angles
{
    double alpha;
    double alpha1;
    double alpha2;
};

struct tree_koef
{
    double r_length;
    double l_length;
    double r_start;
    double l_start;
};


struct tree_params
{
    start_dot dot;
    body body_length;
    tree_angles angles;
    tree_koef koef;
};


#endif // TREE_PARAMS_H
