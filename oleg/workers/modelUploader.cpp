#ifndef UPLOADER_HPP
#define UPLOADER_HPP

#include "modelUploader.h"

FileUploader::FileUploader(const std::string& fileName) : fileName(fileName) {}

std::shared_ptr<Transformed_Model> FileUploader::uploadModel(std::shared_ptr<Tree> tree, std::shared_ptr<Transform_Tree> tr_tree)
{
    try
    {
        openSrc();
        tree_params params;
        file >> params.dot.x >> params.dot.y >> params.dot.z >> \
                params.angles.alpha >> params.angles.alpha1 >> \
                params.angles.alpha2 >> params.koef.r_length >> \
                params.koef.l_length >> params.koef.r_start >> \
                params.koef.l_start >> params.body_length.length;
        closeSrc();
        return tree.get()->buildModel(params, tr_tree);
    }
    catch (const std::ifstream::failure& e)
    {
        throw ReadFileException();
    }
}

void FileUploader::openSrc()
{
    this->file.open(this->fileName);
    if (!file)
        throw OpenFileException();
}

void FileUploader::closeSrc()
{
    try
    {
        this->file.close();
    }
    catch (const std::ifstream::failure& e)
    {
        throw CloseFileException();
    }
}

#endif // UPLOADER_HPP

