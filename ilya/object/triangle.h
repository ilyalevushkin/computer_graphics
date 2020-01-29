#ifndef TRIANGLE_H
#define TRIANGLE_H


#include "node.h"
#include "color.h"
#include "../lighting.h"

using namespace std;

class Triangle
{
public:
    Triangle();
    Triangle(const Node node1, const Node node2, const Node node3);
    Triangle(const Triangle& Triangle);
    Triangle(Triangle&& Triangle);
    ~Triangle();

    Triangle& operator=(const Triangle& triangle);
    Triangle& operator=(Triangle&& triangle);

    Node getNode1() const;
    Node getNode2() const;
    Node getNode3() const;
    Node getNode(int k) const;

    Point getNorm() const;

    double getIntensity() const;

    void setNode1(const Node node);
    void setNode2(const Node node);
    void setNode3(const Node node);

    void setNode1Color(const rgb_color clr);
    void setNode2Color(const rgb_color clr);
    void setNode3Color(const rgb_color clr);

    void setIntensity(const double intensity);

    void setNorm(const Point norm);

    void shift(const double dx, const double dy, const double dz);
    void scale(const double kx, const double ky, const double kz);
    void rotateX(const double angle);
    void rotateY(const double angle);
    void rotateZ(const double angle);

private:
    Node node1;
    Node node2;
    Node node3;
    Point norm;
    double intensity;
};

#endif // TRIANGLE_H
