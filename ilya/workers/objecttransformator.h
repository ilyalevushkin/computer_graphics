#ifndef MODELTRANSFORMATOR_H
#define MODELTRANSFORMATOR_H

#include "transformations/transformations.h"
#include "object/compositeobject.h"
#include "../object/transformed_model.h"

class BaseTransformator
{
public:
    BaseTransformator() = default;
    virtual ~BaseTransformator() = default;

    virtual void transform(std::shared_ptr<Object> obj) = 0;
};

class ModelTransformator : public BaseTransformator
{
public:
    ModelTransformator(BaseTransformations& tr);
    ~ModelTransformator() = default;

    void transform(std::shared_ptr<Object> obj);

private:
    BaseTransformations& tr;
};

class CameraTransformator : public BaseTransformator
{
public:
    CameraTransformator(BaseTransformations& tr);
    ~CameraTransformator() = default;

    void transform(std::shared_ptr<Object> obj);

private:
    BaseTransformations& tr;
};

#endif // MODELTRANSFORMATOR_H
