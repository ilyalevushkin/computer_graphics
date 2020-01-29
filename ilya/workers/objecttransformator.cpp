#include "objecttransformator.h"

ModelTransformator::ModelTransformator(BaseTransformations &tr) : tr(tr) {}

void ModelTransformator::transform(std::shared_ptr<Object> obj)
{
    double x = tr.getX();
    double y = tr.getY();
    double z = tr.getZ();

    std::shared_ptr<Transformed_Model> model = std::static_pointer_cast<Transformed_Model>(obj);

    if (tr.isShifting())
        model->shift(x, y, z);
    if (tr.isScaling())
        model->scale(x, y, z);
    if (tr.isRotation())
        model->rotate(x, y, z);
}

CameraTransformator::CameraTransformator(BaseTransformations &tr) : tr(tr) {}


void CameraTransformator::transform(std::shared_ptr<Object> obj)
{
    double x = tr.getX();
    double y = tr.getY();
    double z = tr.getZ();

    std::shared_ptr<Camera> camera = std::static_pointer_cast<Camera>(obj);

    if (tr.isShifting())
        camera->shift(x, y, z);
    if (tr.isScaling())
        camera->scale(x, y, z);
    if (tr.isRotation())
        camera->rotate(x, y, z);
}

