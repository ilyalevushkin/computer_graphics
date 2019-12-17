#ifndef NODE_HPP
#define NODE_HPP

#include "node.h"

Node::Node() : x(0), y(0), z(0), color({0,0,0}) {
    //std::vector<double> v();
    //this->intensity = v;
}


int check_color(int rgb)
{
    if (rgb > 255)
    {
        return 255;
    }
    else if (rgb < 0)
    {
        return 0;
    }
    return rgb;
}

Node::Node(const double x, const double y, const double z, const rgb_color color) : x(x), y(y), z(z) {
    this->color.red = check_color(color.red);
    this->color.blue = check_color(color.blue);
    this->color.green = check_color(color.green);
}

Node::Node(const Node& node)
{
    this->x = node.x;
    this->y = node.y;
    this->z = node.z;
    this->color = node.color;
}

Node::Node(Node &&node)
{
    this->x = node.x;
    this->y = node.y;
    this->z = node.z;
    this->color = node.color;
    node.~Node();
}

Node::~Node()
{
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->color = {0,0,0};
}

Node& Node::operator=(const Node& node)
{
    this->x = node.x;
    this->y = node.y;
    this->z = node.z;
    this->color = node.color;
    return *this;
}

Node& Node::operator=(Node&& node)
{
    this->x = node.x;
    this->y = node.y;
    this->z = node.z;
    this->color = node.color;
    node.~Node();

    return *this;
}

double Node::getX() const
{
    return x;
}

double Node::getY() const
{
    return y;
}

double Node::getZ() const
{
    return z;
}

rgb_color Node::getcolor() const
{
    return color;
}

double Node::getIntensity()
{
    return intensity;
}

void Node::setX(const double x)
{
    this->x = x;
}

void Node::setY(const double y)
{
    this->y = y;
}

void Node::setZ(const double z)
{
    this->z = z;
}

void Node::setColor(const rgb_color color)
{
    this->color.red = check_color(color.red);
    this->color.blue = check_color(color.blue);
    this->color.green = check_color(color.green);
}

void Node::setIntensity(double intensity)
{
    this->intensity = intensity;
}

void Node::shift(const double dx, const double dy, const double dz)
{
    this->x += dx;
    this->y += dy;
    this->z += dz;
}

void Node::scale(const double kx, const double ky, const double kz)
{
    this->x = this->x * kx;
    this->y = this->y * ky;
    this->z = this->z * kz;
}

void Node::rotateX(const double angle)
{
    const double tmp = this->y;
    this->y = this->y * cos(angle) + this->z * sin(angle);
    this->z = -tmp * sin(angle) + this->z * cos(angle);
}

void Node::rotateY(const double angle)
{
    const double tmp = this->z;
    this->z = this->z * cos(angle) + this->x * sin(angle);
    this->x = -tmp * sin(angle) + this->x * cos(angle);
}

void Node::rotateZ(const double angle)
{
    const double tmp = this->x;
    this->x = this->x * cos(angle) + this->y * sin(angle);
    this->y = -tmp * sin(angle) + this->y * cos(angle);
}

#endif // NODE_HPP

