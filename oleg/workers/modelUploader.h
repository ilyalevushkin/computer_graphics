#ifndef MODELUPLOADER_H
#define MODELUPLOADER_H

#include "exceptions/uploaderException.h"
#include "../factory/tree_factory.h"
#include "../factory/object_factory.h"
#include "../tree_params.h"
#include "../tree_generate_methods.h"

#include <fstream>

class BaseUploader
{
public:
    BaseUploader() = default;
    virtual ~BaseUploader() = default;

    virtual std::shared_ptr<Transformed_Model> uploadModel(std::shared_ptr<Tree> tree, std::shared_ptr<Transform_Tree> tr_tree) = 0;
    //virtual void openSrc() = 0;
    //virtual void closeSrc() = 0;
};

class FileUploader : public BaseUploader
{
public:
    explicit FileUploader(const std::string& fileName);
    ~FileUploader() override = default;

    std::shared_ptr<Transformed_Model> uploadModel(std::shared_ptr<Tree> tree, std::shared_ptr<Transform_Tree> tr_tree) override;

private:
    void openSrc();
    void closeSrc();

    std::string fileName;
    std::ifstream file;
};

class GenerateUploader : public BaseUploader
{
public:
    explicit GenerateUploader(const tree_params params) : params(params) {}
    ~GenerateUploader() override = default;

    std::shared_ptr<Transformed_Model> uploadModel(std::shared_ptr<Tree> tree, std::shared_ptr<Transform_Tree> tr_tree) override {
        return tree.get()->buildModel(params, tr_tree);
    }

private:
    tree_params params;
};

#endif // MODELUPLOADER_H

