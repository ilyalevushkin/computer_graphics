#ifndef SCENE_CPP
#define SCENE_CPP

#include "scene.h"

void Scene::addModel(const std::shared_ptr<Object>& object)
{
    this->object.addModel(object);
}

void Scene::removeModel(const size_t index)
{
    this->object.removeModel(index);
}

void Scene::addCamera(const std::shared_ptr<Object>& object)
{
    this->object.addCamera(object);
}

void Scene::removeCamera(const size_t index)
{
    this->object.removeCamera(index);
}

std::shared_ptr<Object> Scene::getModel(const size_t index)
{
    return this->object.getModel(index);
}

std::shared_ptr<Object> Scene::getCamera(const size_t index)
{
    return this->object.getCamera(index);
}

ObjIter Scene::objectBegin()
{
    return this->object.objectBegin();
}

ObjIter Scene::objectEnd()
{
    return this->object.objectEnd();
}

ObjIter Scene::modelIndex(const size_t index)
{
    return this->object.modelIndex(index);
}

ObjIter Scene::cameraIndex(const size_t index)
{
    return this->object.cameraIndex(index);
}

#endif // SCENE_CPP

