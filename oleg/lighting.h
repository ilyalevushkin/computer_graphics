#ifndef LIGHTING_H
#define LIGHTING_H

#include <math.h>

struct Point
{
    void shift(double x, double y, double z)
    {
        this->x += x;
        this->y += y;
        this->z += z;
    }
    void scale(double x, double y, double z)
    {
        this->x *= x;
        this->y *= y;
        this->z *= z;
    }
    void rotate(double x, double y, double z)
    {
        double tmp = this->y;
        this->y = this->y * cos(x) + this->z * sin(x);
        this->z = -tmp * sin(x) + this->z * cos(x);


        tmp = this->z;
        this->z = this->z * cos(y) + this->x * sin(y);
        this->x = -tmp * sin(y) + this->x * cos(y);


        tmp = this->x;
        this->x = this->x * cos(z) + this->y * sin(z);
        this->y = -tmp * sin(z) + this->y * cos(z);
    }
    double x;
    double y;
    double z;
};


struct lighting
{
    Point from;
    Point to;
};


#endif // LIGHTING_H
