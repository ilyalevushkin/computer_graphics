#ifndef TRANSFORMED_MODEL_H
#define TRANSFORMED_MODEL_H

#include "object.h"
#include "node.h"
#include "triangle.h"

#include <vector>

using namespace std;

class Transformed_Model : public VisibleObject
{
public:
    Transformed_Model() = default;
    Transformed_Model(const std::vector<Triangle> triangles);
    Transformed_Model(const Transformed_Model& model);
    Transformed_Model(Transformed_Model&& model);
    ~Transformed_Model() = default;

    Transformed_Model& operator=(const Transformed_Model& model);
    Transformed_Model& operator=(Transformed_Model&& model);

    const vector<Triangle> getTriangles() const;
    size_t getAccuracy() const;

    void addTriangle(const Triangle& triangle);
    void addAccuracy(const size_t acc);

    void shift(const double x, const double y, const double z);
    void scale(const double x, const double y, const double z);
    void rotate(const double x, const double y, const double z);

private:
    vector<Triangle> triangles;
    size_t accuracy;
};

#endif // TRANSFORMED_MODEL_H
