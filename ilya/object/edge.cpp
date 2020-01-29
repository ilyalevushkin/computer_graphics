#ifndef EDGE_HPP
#define EDGE_HPP

#include "edge.h"

Edge::Edge() : src(0), purp(0), radius(0) {}

Edge::Edge(const size_t src, const size_t purp, const double radius) : src(src), purp(purp), radius(radius) {}

Edge::Edge(const Edge& edge)
{
    this->src = edge.src;
    this->purp = edge.purp;
    this->radius = edge.radius;
}

Edge::Edge(Edge &&edge)
{
    this->src = edge.src;
    this->purp = edge.purp;
    this->radius = edge.radius;
    edge.~Edge();
}

Edge::~Edge()
{
    this->src = 0;
    this->purp = 0;
    this->radius = 0;
}

Edge& Edge::operator=(const Edge& edge)
{
    this->src = edge.src;
    this->purp = edge.purp;
    this->radius = edge.radius;

    return *this;
}

Edge& Edge::operator=(Edge&& edge)
{
    this->src = edge.src;
    this->purp = edge.purp;
    this->radius = edge.radius;
    edge.~Edge();

    return *this;
}

size_t Edge::getSrc() const
{
    return src;
}

size_t Edge::getPurp() const
{
    return purp;
}

double Edge::getRadius() const
{
    return radius;
}

void Edge::setSrc(const size_t src)
{
    this->src = src;
}

void Edge::setPurp(const size_t purp)
{
    this->purp = purp;
}

void Edge::setRadius(const double radius)
{
    this->radius = radius;
}

#endif // EDGE_HPP

