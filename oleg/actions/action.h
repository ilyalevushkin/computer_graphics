#ifndef ACTION_H
#define ACTION_H

#include "facade/facade.h"
#include "workers/modelUploader.h"
#include "workers/objecttransformator.h"
#include "transformations/transformations.h"
#include "../tree_generate_methods.h"
#include "../factory/object_factory.h"
#include "../tree_params.h"

class BaseAction
{
public:
    BaseAction() = default;
    virtual ~BaseAction() = default;

    virtual void execute(std::shared_ptr<Facade> facade) = 0;
};

namespace actions
{
class ModelUploadAction : public BaseAction
{
public:
    explicit ModelUploadAction(const std::string& fileName) : fileName(fileName) {}
    ~ModelUploadAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        FileUploader uploader(fileName);
        std::shared_ptr<Tree> tree = Tree::createTree(Honda_ID);
        std::shared_ptr<Transform_Tree> transform_tree = Transform_Tree::create_Transform_Tree(Cone_ID);
        facade->addModel(uploader, tree, transform_tree);
    }
private:
    std::string fileName;
};

class ModelUploadFromGenerateAction : public BaseAction
{
public:
    explicit ModelUploadFromGenerateAction(const tree_params params) : params(params) {}
    ~ModelUploadFromGenerateAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        GenerateUploader uploader(params);
        std::shared_ptr<Tree> tree = Tree::createTree(Honda_ID);
        std::shared_ptr<Transform_Tree> transform_tree = Transform_Tree::create_Transform_Tree(Cone_ID);
        facade->addModel(uploader, tree, transform_tree);
    }
private:
    tree_params params;
};

class CameraAddAction : public BaseAction
{
public:
    explicit CameraAddAction(const double angleX, const double angleY, \
        const double angleZ) : angleX(angleX), angleY(angleY), angleZ(angleZ) {}
    ~CameraAddAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        facade->addCamera();
    }
private:
    double angleX, angleY, angleZ;
};

class CameraRemoveAction : public BaseAction
{
public:
    explicit CameraRemoveAction(const size_t index) : index(index) {}
    ~CameraRemoveAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        facade->removeCamera(this->index);
    }
private:
    size_t index;
};

class ModelShiftAction : public BaseAction
{
public:
    explicit ModelShiftAction(const double dx, const double dy, \
                              const double dz, const ssize_t index) :
        dx(dx), dy(dy), dz(dz), modelIndex(index) {}
    ~ModelShiftAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        transformtions::Shifting shf(dx, dy, dz);
        ModelTransformator transformator(shf);
        facade->transformModel(transformator, modelIndex);
    }
private:
    double dx, dy, dz;
    ssize_t modelIndex;
};

class CameraShiftAction : public BaseAction
{
public:
    explicit CameraShiftAction(const double dx, const double dy, \
                              const double dz, const ssize_t index) :
        dx(dx), dy(dy), dz(dz), cameraIndex(index) {}
    ~CameraShiftAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        transformtions::Shifting shf(dx, dy, dz);
        CameraTransformator transformator(shf);
        facade->transformCamera(transformator, cameraIndex);
    }
private:
    double dx, dy, dz;
    ssize_t cameraIndex;
};

class ModelScaleAction : public BaseAction
{
public:
    explicit ModelScaleAction(const double kx, const double ky, \
                              const double kz, const size_t index) :
        kx(kx), ky(ky), kz(kz), modelIndex(index) {}
    ~ModelScaleAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        transformtions::Scaling scl(kx, ky, kz);
        ModelTransformator transformator(scl);
        facade->transformModel(transformator, modelIndex);
    }
private:
    double kx, ky, kz;
    size_t modelIndex;
};

class CameraScaleAction : public BaseAction
{
public:
    explicit CameraScaleAction(const double kx, const double ky, \
                              const double kz, const size_t index) :
        kx(kx), ky(ky), kz(kz), cameraIndex(index) {}
    ~CameraScaleAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        transformtions::Scaling scl(kx, ky, kz);
        CameraTransformator transformator(scl);
        facade->transformCamera(transformator, cameraIndex);
    }
private:
    double kx, ky, kz;
    size_t cameraIndex;
};

class ModelRotateAction : public BaseAction
{
public:
    explicit ModelRotateAction(const double x, const double y, const double z,
                                const size_t index) :
        angleX(x), angleY(y), angleZ(z), modelIndex(index) {}
    ~ModelRotateAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        transformtions::Rotation rt(angleX, angleY, angleZ);
        ModelTransformator transformator(rt);
        facade->transformModel(transformator, modelIndex);
    }
private:
    double angleX, angleY, angleZ;
    size_t modelIndex;
};

class CameraRotateAction : public BaseAction
{
public:
    explicit CameraRotateAction(const double x, const double y, const double z,
                                const size_t index)
        : angleX(x), angleY(y), angleZ(z), cameraIndex(index) {}
    ~CameraRotateAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        transformtions::Rotation rt(angleX, angleY, angleZ);
        CameraTransformator transformator(rt);
        facade->transformCamera(transformator, cameraIndex);
    }
private:
    double angleX, angleY, angleZ;
    size_t cameraIndex;
};

class ModelDrawAction : public BaseAction
{
public:
    explicit ModelDrawAction(ModelDrawer drw, const size_t index)
        : drawer(drw), cameraIndex(index) {}
    ~ModelDrawAction() override = default;

    void execute(std::shared_ptr<Facade> facade) override
    {
        facade->draw(drawer, cameraIndex);
    }
private:
    ModelDrawer drawer;
    size_t cameraIndex;
};
}

#endif // ACTION_H
