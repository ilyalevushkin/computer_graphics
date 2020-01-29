#ifndef UPLOADER_HPP
#define UPLOADER_HPP

#include "modelUploader.h"

FileUploader::FileUploader(const std::string& fileName, tree_params *params) : fileName(fileName), params(params) {}

vector<shared_ptr<Object>> FileUploader::uploadModels(shared_ptr<Growth> growth, shared_ptr<Tree> tree, shared_ptr<Transform_Tree> tr_tree)
{
    tree_params params;
    return growth.get()->buildModel(tree, tr_tree, params);
}

double convert_to_rad2(double alpha)
{
    return M_PI * alpha / 180;
}

std::shared_ptr<Transformed_Model> FileUploader::uploadModel(std::shared_ptr<Tree> tree, std::shared_ptr<Transform_Tree> tr_tree)
{
    try
    {
        openSrc();
        tree_params params;
        rgb_color clr;
        double alpha, alpha1, alpha2;
        file >> params.dot.x >> params.dot.y >> params.dot.z >> \
                alpha >> alpha1 >> \
                alpha2 >> params.koef.r_length >> \
                params.koef.l_length >> params.koef.r_start >> \
                params.koef.l_start >> params.body.length >> \
                params.body.radius >> params.body.accuracy >> \
                clr.red >> clr.green >> clr.blue;
        params.angles.alpha = convert_to_rad2(alpha);
        params.angles.alpha1 = convert_to_rad2(alpha1);
        params.angles.alpha2 = convert_to_rad2(alpha2);
        params.tree_clr.clr.setRgb(clr.red, clr.green, clr.blue);
        *this->params = params;
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

