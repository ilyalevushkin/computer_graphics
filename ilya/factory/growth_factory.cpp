#ifndef GROWTH_FACTORY_CPP
#define GROWTH_FACTORY_CPP



#include "growth_factory.h"


shared_ptr<Growth> Growth::createGrowth(Growth_ID id, int iteration)
{
    shared_ptr<Growth> ptr(nullptr);
    switch (id)
    {
        case Linear_ID:
            ptr = std::make_shared<Linear>(iteration);
            break;
    }
    return ptr;
};

vector<shared_ptr<Object>> Linear::buildModel(shared_ptr<Tree> tree, shared_ptr<Transform_Tree> tr_tree, tree_params params)
{
    vector<shared_ptr<Object>> v_m;

    double length = params.body.length;
    double radius = params.body.radius;
    double alpha1 = params.angles.alpha1;
    double alpha2 = params.angles.alpha2;

    double min_length = 6;

    double min_radius = 1;

    double min_angle = 0;

    double length_iter = (length - min_length) / double(this->iteration);
    double radius_iter = (radius - min_radius) / double(this->iteration);
    double alpha1_iter = (alpha1 - min_angle) / double(this->iteration);
    double alpha2_iter = (alpha2 - min_angle) / double(this->iteration);

    params.body.length = min_length;
    params.body.radius = min_radius;
    params.angles.alpha1 = min_angle;
    params.angles.alpha2 = min_angle;

    shared_ptr<Transformed_Model> ptr(nullptr);

    for (int i = 0; i < this->iteration; i++)
    {
        ptr = tree->buildModel(params, tr_tree);
        v_m.push_back(ptr);
        params.body.length += length_iter;
        params.body.radius += radius_iter;
        params.angles.alpha1 += alpha1_iter;
        params.angles.alpha2 += alpha2_iter;
    }
    return v_m;
}

#endif // GROWTH_FACTORY_CPP
