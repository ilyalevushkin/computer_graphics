#ifndef FACADE_HPP
#define FACADE_HPP

#include "facade.h"

void Facade::addModel(BaseUploader& upld, shared_ptr<Tree> tree, shared_ptr<Transform_Tree> tr_tree)
{
    this->scene.addModel(upld.uploadModel(tree, tr_tree));
}

void Facade::modelingGrowth(BaseUploader& upld, shared_ptr<Growth> growth, shared_ptr<Tree> tree, shared_ptr<Transform_Tree> tr_tree)
{
    this->scene.addModels(upld.uploadModels(growth, tree, tr_tree));
}

void Facade::removeModel(const size_t index)
{
    this->scene.removeModel(index);
}

void Facade::addCamera()
{
    Camera* cameraPtr = new Camera();
    std::shared_ptr<Object> camera(cameraPtr);
    this->scene.addCamera(camera);
}

void Facade::addNextCamera(const size_t index)
{
    Camera* cameraPtr = new Camera();
    std::shared_ptr<Object> camera(cameraPtr);
    this->scene.addNextCamera(camera, index);
}

void Facade::removeCamera(const size_t index)
{
    this->scene.removeCamera(index);
}

#include <qdebug.h>

void Facade::transformModel(BaseTransformator& tr, const ssize_t modelIndex)
{
    ObjIter begin = this->scene.objectBegin();
    ObjIter end = this->scene.objectEnd();

    this->modelManager.transform(tr, begin, end);
}

void Facade::transformCamera(BaseTransformator &tr, const size_t cameraIndex)
{
    ObjIter begin = this->scene.cameraIndex(cameraIndex);
    ObjIter end = this->scene.cameraIndex(cameraIndex + 1);
    this->cameraManager.transform(tr, begin, end);
}

void Facade::draw(BaseDrawer& drw, const size_t cameraIndex, const int modelIndex)
{
    if (modelIndex < 0)
    {
        this->drawManager.drawWhiteList(drw);
    }
    else
    {
        this->drawManager.drawcolorfulModel(drw, this->scene.getModel(size_t(modelIndex)), this->scene.getCamera(cameraIndex));
    }
}

#endif // FACADE_HPP

