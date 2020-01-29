#ifndef TRANSFORMED_MODEL_HPP
#define TRANSFORMED_MODEL_HPP

#include "transformed_model.h"

Transformed_Model::Transformed_Model(const std::vector<Triangle> triangles) : \
    triangles(triangles) {}

Transformed_Model::Transformed_Model(const Transformed_Model& model)
{
    this->triangles = model.triangles;
}

Transformed_Model::Transformed_Model(Transformed_Model&& model)
{
    this->triangles = model.triangles;
    model.~Transformed_Model();
}

Transformed_Model& Transformed_Model::operator=(const Transformed_Model& model)
{
    this->triangles = model.triangles;

    return *this;
}

Transformed_Model& Transformed_Model::operator=(Transformed_Model&& model)
{
    this->triangles = model.triangles;
    model.~Transformed_Model();

    return *this;
}

const std::vector<Triangle> Transformed_Model::getTriangles() const
{
    return this->triangles;
}

size_t Transformed_Model::getAccuracy() const
{
    return this->accuracy;
}

void Transformed_Model::addTriangle(const Triangle& triangle)
{
    this->triangles.push_back(triangle);
}

void Transformed_Model::addAccuracy(const size_t acc)
{
    this->accuracy = acc;
}

void Transformed_Model::shift(const double x, const double y, const double z)
{
    for (size_t i = 0; i < triangles.size(); ++i)
    {
        triangles[i].shift(x, y, z);
    }
}

void Transformed_Model::scale(const double x, const double y, const double z)
{
    for (size_t i = 0; i < triangles.size(); ++i)
    {
        triangles[i].scale(x, y, z);
    }
}

void Transformed_Model::rotate(const double x, const double y, const double z)
{
    for (size_t i = 0; i < triangles.size(); ++i)
    {
        triangles[i].rotateX(x);
        triangles[i].rotateY(y);
        triangles[i].rotateZ(z);
    }
}

#endif // TRANSFORMED_MODEL_HPP
