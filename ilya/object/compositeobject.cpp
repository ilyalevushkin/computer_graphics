#include "compositeobject.h"

CompositeObject::CompositeObject() : countModel(0), countCamera(0) {}

void CompositeObject::addModel(std::shared_ptr<Object> object)
{
    objects.push_back(std::static_pointer_cast<Model>(object));
    ++countModel;
}

void CompositeObject::removeModel(const size_t index)
{
    size_t count = 0;
    size_t i = 0;

    for (; i < objects.size(); ++i)
    {
        if (objects[i]->isVisible())
            ++count;
        if (count == index + 1)
            break;
    }

    if (count != index + 1)
    {
        throw OutOfRangeObjectException(": removeModel");
    }
    else
    {
        objects.erase(objects.begin() + i);
        --countModel;
    }
}


void CompositeObject::addCamera(std::shared_ptr<Object> object)
{
    shared_ptr<Camera> cm = std::static_pointer_cast<Camera>(object);
    objects.push_back(cm);
    ++countCamera;
}

void CompositeObject::addNextCamera(std::shared_ptr<Object> object, const size_t index)
{
    shared_ptr<Camera> cm = std::static_pointer_cast<Camera>(object);

    shared_ptr<Camera> cm_previous = std::static_pointer_cast<Camera>(getCamera(index));

    cm->shift(cm_previous->getShX(), cm_previous->getShY(), cm_previous->getShZ());

    cm->scale(cm_previous->getScX(),cm_previous->getScY(), cm_previous->getScZ());

    cm->rotate(cm_previous->getRtX(),cm_previous->getRtY(), cm_previous->getRtZ());

    objects.push_back(cm);
    ++countCamera;
}

void CompositeObject::removeCamera(const size_t index)
{
    size_t count = 0;
    size_t i = 0;

    for (; i < objects.size(); ++i)
    {
        if (!objects[i]->isVisible())
            ++count;
        if (count == index + 1)
            break;
    }

    if (count != index + 1)
    {
        throw OutOfRangeObjectException(": removeCamera");
    }
    else
    {
        objects.erase(objects.begin() + i);
        --countModel;
    }
}

std::shared_ptr<Object> CompositeObject::getModel(const size_t index)
{
    size_t count = 0;
    size_t i = 0;

    for (; i < objects.size(); ++i)
    {
        if (objects[i]->isVisible())
            ++count;
        if (count == index + 1)
            break;
    }

    if (count != index + 1)
        throw OutOfRangeObjectException(": getModel");
    else
        return objects[i];
}

std::shared_ptr<Object> CompositeObject::getCamera(const size_t index)
{
    size_t count = 0;
    size_t i = 0;

    for (; i < objects.size(); ++i)
    {
        if (!objects[i]->isVisible())
            ++count;
        if (count == index + 1)
            break;
    }

    if (count != index + 1)
        throw OutOfRangeObjectException(": getCamera");
    else
        return objects[i];
}

ObjIter CompositeObject::objectBegin()
{
    return objects.begin();
}

ObjIter CompositeObject::objectEnd()
{
    return objects.end();
}

ObjIter CompositeObject::modelIndex(const size_t index)
{
    if (index == countModel)
        return objects.end();

    size_t count = 0;
    size_t i = 0;

    for (; i < objects.size(); ++i)
    {
        if (objects[i]->isVisible())
            ++count;
        if (count == index + 1)
            break;
    }

    if (count != index + 1)
        throw OutOfRangeObjectException(": modelIndex");
    else
        return objects.begin() + i;

    //return objects.begin() + index;
}

ObjIter CompositeObject::cameraIndex(const size_t index)
{
    if (index == countCamera)
        return objects.end();

    size_t count = 0;
    size_t i = 0;

    for (; i < objects.size(); ++i)
    {
        if (!objects[i]->isVisible())
            ++count;
        if (count == index + 1)
            break;
    }

    if (count != index + 1)
        throw OutOfRangeObjectException(": cameraIndex");
    else
        return objects.begin() + i;
}

