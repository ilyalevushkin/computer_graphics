#include "triangle.h"

Triangle::Triangle() : node1({0,0,0,{0,0,0}}), node2({0,0,0,{0,0,0}}), node3({0,0,0,{0,0,0}}), intensity(1) {}

Triangle::Triangle(const Node node1, const Node node2, const Node node3) :
    node1(node1), node2(node2), node3(node3), intensity(1) {}

Triangle::Triangle(const Triangle& Triangle)
{
    this->node1 = Triangle.node1;
    this->node2 = Triangle.node2;
    this->node3 = Triangle.node3;
    this->intensity = Triangle.intensity;
}

Triangle::Triangle(Triangle&& Triangle)
{
    this->node1 = Triangle.node1;
    this->node2 = Triangle.node2;
    this->node3 = Triangle.node3;
    this->intensity = Triangle.intensity;
    Triangle.~Triangle();
}

Triangle::~Triangle()
{
    this->node1 = {0,0,0,{0,0,0}};
    this->node2 = {0,0,0,{0,0,0}};
    this->node3 = {0,0,0,{0,0,0}};
    this->intensity = 1;
}

Triangle& Triangle::operator=(const Triangle& triangle)
{
    this->node1 = triangle.node1;
    this->node2 = triangle.node2;
    this->node3 = triangle.node3;
    this->intensity = triangle.intensity;

    return *this;
}

Triangle& Triangle::operator=(Triangle&& triangle)
{
    this->node1 = triangle.node1;
    this->node2 = triangle.node2;
    this->node3 = triangle.node3;
    this->intensity = triangle.intensity;
    triangle.~Triangle();

    return *this;
}

Node Triangle::getNode1() const
{
    return node1;
}

Node Triangle::getNode2() const
{
    return node2;
}

Node Triangle::getNode3() const
{
    return node3;
}

Node Triangle::getNode(int k) const
{
    switch (k)
    {
    case 0:
        return getNode1();
    case 1:
        return getNode2();
    case 2:
        return getNode3();
    }
}

double Triangle::getIntensity() const
{
    return intensity;
}

Point Triangle::getNorm() const
{
    return norm;
}


void Triangle::setNode1(const Node node)
{
    this->node1 = node;
}

void Triangle::setNode2(const Node node)
{
    this->node2 = node;
}

void Triangle::setNode3(const Node node)
{
    this->node3 = node;
}

void Triangle::setNode1Color(const rgb_color clr)
{
    this->node1.setColor(clr);
}

void Triangle::setNode2Color(const rgb_color clr)
{
    this->node2.setColor(clr);
}

void Triangle::setNode3Color(const rgb_color clr)
{
    this->node3.setColor(clr);
}

void Triangle::setNorm(const Point norm)
{
    this->norm = norm;
}

void Triangle::setIntensity(const double intensity)
{
    this->intensity = intensity;
}

void Triangle::shift(const double dx, const double dy, const double dz)
{
    this->node1.shift(dx, dy, dz);
    this->node2.shift(dx, dy, dz);
    this->node3.shift(dx, dy, dz);
}

void Triangle::scale(const double kx, const double ky, const double kz)
{
    this->node1.scale(kx, ky, kz);
    this->node2.scale(kx, ky, kz);
    this->node3.scale(kx, ky, kz);
}

void Triangle::rotateX(const double angle)
{
    this->node1.rotateX(angle);
    this->node2.rotateX(angle);
    this->node3.rotateX(angle);
}

void Triangle::rotateY(const double angle)
{
    this->node1.rotateY(angle);
    this->node2.rotateY(angle);
    this->node3.rotateY(angle);
}

void Triangle::rotateZ(const double angle)
{
    this->node1.rotateZ(angle);
    this->node2.rotateZ(angle);
    this->node3.rotateZ(angle);
}
