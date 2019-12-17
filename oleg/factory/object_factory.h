#ifndef OBJECT_FACTORY_H
#define OBJECT_FACTORY_H

#include <vector>
#include "../object/transformed_model.h"
#include "../object/model.h"
#include "../transform_tree_generate_methods.h"
#include <armadillo>
#include "../matrix/matrix.h"
#include <math.h>
#include "../object/color.h"

using namespace arma;
using namespace std;

class Transform_Tree
{
  public:
    virtual std::shared_ptr<Transformed_Model> buildModel(std::shared_ptr<Model> model) = 0;
    virtual ~Transform_Tree() {}
    static std::shared_ptr<Transform_Tree> create_Transform_Tree(Transform_Tree_ID id);
};

class Cylinder: public Transform_Tree
{
    public:
        Cylinder() {
            transformed_model = std::make_shared<Transformed_Model>();
        }
        ~Cylinder() override = default;

        std::shared_ptr<Transformed_Model> buildModel(std::shared_ptr<Model> model) override;

    protected:
        std::shared_ptr<Transformed_Model> transformed_model;
};

class Cone: public Transform_Tree
{
    public:
        Cone() {
            transformed_model = std::make_shared<Transformed_Model>();
        }
        ~Cone() override = default;

        std::shared_ptr<Transformed_Model> buildModel(std::shared_ptr<Model> model) override;

    protected:
        std::shared_ptr<Transformed_Model> transformed_model;
};


#endif // OBJECT_FACTORY_H
