#ifndef NODE_H
#define NODE_H

#include <math.h>
#include "color.h"
#include <vector>

using namespace std;

class Node
{
public:
    Node();
    Node(const double x, const double y, const double z, const rgb_color color);
    Node(const Node& node);
    Node(Node&& node);
    ~Node();

    Node& operator=(const Node& node);
    Node& operator=(Node&& node);

    double getX() const;
    double getY() const;
    double getZ() const;
    rgb_color getcolor() const;
    double getIntensity();

    void setX(const double x);
    void setY(const double y);
    void setZ(const double z);
    void setColor(const rgb_color color);

    void setIntensity(double intensity);

    void shift(const double dx, const double dy, const double dz);
    void scale(const double kx, const double ky, const double kz);
    void rotateX(const double angle);
    void rotateY(const double angle);
    void rotateZ(const double angle);

private:
    double x;
    double y;
    double z;
    double intensity;
    rgb_color color;
};

#endif // NODE_H

