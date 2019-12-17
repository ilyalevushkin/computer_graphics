#ifndef MODELMANAGER_H
#define MODELMANAGER_H

#include "iterator/iterator.h"
#include "workers/objecttransformator.h"
#include "exceptions/transformerException.h"

class ModelManager
{
public:
    ModelManager() = default;
    ~ModelManager() = default;

    void transform(BaseTransformator& tr, const ObjIter& b, const ObjIter& e)
    {
        for (ObjIter iter = b; iter != e; ++iter)
        {
            if (!(*iter))
                throw NoTransformingObjectException();

            if ((*iter)->isVisible())
                tr.transform((*iter));
        }
    }
};

class CameraManager
{
public:
    CameraManager() = default;
    ~CameraManager() = default;

    void transform(BaseTransformator& tr, const ObjIter& b, const ObjIter& e)
    {
        for (ObjIter iter = b; iter != e; ++iter)
        {
            if (!(*iter))
                throw NoTransformingObjectException();

            if (!(*iter)->isVisible())
                tr.transform((*iter));
        }
    }
};

#endif // MODELMANAGER_H
