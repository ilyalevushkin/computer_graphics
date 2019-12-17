#ifndef SCENE_H
#define SCENE_H

#include "object/compositeobject.h"

#include <iostream>
#include <memory>
#include <vector>

class Scene
{
public:
    Scene() = default;
    ~Scene() = default;

    void addModel(const std::shared_ptr<Object>& model);
    void removeModel(const size_t index);

    void addCamera(const std::shared_ptr<Object>& camera);
    void removeCamera(const size_t index);

    std::shared_ptr<Object> getModel(const size_t index);
    std::shared_ptr<Object> getCamera(const size_t index);

    ObjIter objectBegin();
    ObjIter objectEnd();
    ObjIter modelIndex(const size_t index);
    ObjIter cameraIndex(const size_t index);

private:
    CompositeObject object;
};

#endif // SCENE_H

