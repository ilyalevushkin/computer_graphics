#ifndef TRANSFORMATIONS_H
#define TRANSFORMATIONS_H

#include <vector>

class BaseTransformations
{
public:
    BaseTransformations(const double x, const double y, const double z) :
        x(x), y(y), z(z) {}
    virtual ~BaseTransformations() = default;

    virtual bool isShifting() = 0;
    virtual bool isScaling() = 0;
    virtual bool isRotation() = 0;

    double getX() {return x;}
    double getY() {return y;}
    double getZ() {return z;}

protected:
    double x, y, z;
};

namespace transformtions
{
class Shifting : public BaseTransformations
{
public:
    Shifting(const double shX, const double shY, const double shZ) :
        BaseTransformations(shX, shY, shZ) {}
    ~Shifting() = default;

    bool isShifting() {return true;}
    bool isScaling() {return false;}
    bool isRotation() {return false;}
};

class Scaling : public BaseTransformations
{
public:
    Scaling(const double scX, const double scY, const double scZ) :
        BaseTransformations(scX, scY, scZ) {}
    ~Scaling() = default;

    bool isShifting() {return false;}
    bool isScaling() {return true;}
    bool isRotation() {return false;}
};

class Rotation : public BaseTransformations
{
public:
    Rotation(const double rtX, const double rtY, const double rtZ) :
        BaseTransformations(rtX, rtY, rtZ) {}
    ~Rotation() = default;

    bool isShifting() {return false;}
    bool isScaling() {return false;}
    bool isRotation() {return true;}
};
}

#endif // TRANSFORMATIONS_H
