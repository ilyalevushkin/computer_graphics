#ifndef FACADE_HPP
#define FACADE_HPP

#include "facade.h"

void Facade::addModel(BaseUploader& upld, std::shared_ptr<Tree> tree, std::shared_ptr<Transform_Tree> tr_tree)
{
    this->scene.addModel(upld.uploadModel(tree, tr_tree));
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

void Facade::removeCamera(const size_t index)
{
    this->scene.removeCamera(index);
}

#include <qdebug.h>

void Facade::transformModel(BaseTransformator& tr, const ssize_t modelIndex)
{
    ObjIter begin = (modelIndex == -1) ? this->scene.objectBegin() : \
                                         this->scene.modelIndex(modelIndex);
    ObjIter end = (modelIndex == -1) ? this->scene.objectEnd() : \
                                       this->scene.modelIndex(modelIndex + 1);

    this->modelManager.transform(tr, begin, end);
}

void Facade::transformCamera(BaseTransformator &tr, const size_t cameraIndex)
{
    ObjIter begin = this->scene.cameraIndex(cameraIndex);
    ObjIter end = this->scene.cameraIndex(cameraIndex + 1);
    this->cameraManager.transform(tr, begin, end);
}

void Facade::draw(BaseDrawer& drw, const size_t cameraIndex)
{
    ObjIter begin = this->scene.objectBegin();
    ObjIter end = this->scene.objectEnd();
    //this->drawManager.drawModel(drw, begin, end, this->scene.getCamera(cameraIndex));
    this->drawManager.drawcolorfulModel(drw, begin, end, this->scene.getCamera(cameraIndex));
}

#endif // FACADE_HPP

