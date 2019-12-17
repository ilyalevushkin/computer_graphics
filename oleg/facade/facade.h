#ifndef FACADE_H
#define FACADE_H

#include "scene/scene.h"
#include "managers/drawmanager.h"
#include "managers/objectmanager.h"
#include "../workers/modelUploader.h"
#include "../factory/object_factory.h"

class Facade
{
public:
    Facade() = default;
    ~Facade() = default;

    void addModel(BaseUploader& upld, std::shared_ptr<Tree> tree, std::shared_ptr<Transform_Tree> tr_tree);
    void removeModel(const size_t index);

    void addCamera();
    void removeCamera(const size_t index);

    void transformModel(BaseTransformator& tr, const ssize_t modelIndex);
    void transformCamera(BaseTransformator& tr, const size_t cameraIndex);

    void draw(BaseDrawer& drw, const size_t cameraIndex);

private:
    Scene scene;
    DrawManager drawManager;
    ModelManager modelManager;
    CameraManager cameraManager;
};

#endif // FACADE_H
