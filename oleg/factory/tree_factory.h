#ifndef TREE_FACTORY_H
#define TREE_FACTORY_H

#include <vector>
#include "../object/model.h"
#include "../object/transformed_model.h"
#include "../factory/object_factory.h"
#include "../object/color.h"
#include "../tree_params.h"
#include "matrix/matrix.h"
#include <armadillo>
#include "../tree_generate_methods.h"
#include <list>

#define MIN_VALUE 0.00001

using namespace arma;

class Tree
{
  public:
    virtual std::shared_ptr<Transformed_Model> buildModel(tree_params params, std::shared_ptr<Transform_Tree> tr_tree) = 0;
    virtual ~Tree() {}
    static std::shared_ptr<Tree> createTree(Tree_ID id);
};

class Honda: public Tree
{
    public:
        Honda() {
            model = std::make_shared<Model>();
        }
        ~Honda() override = default;

        std::shared_ptr<Transformed_Model> buildModel(tree_params params, std::shared_ptr<Transform_Tree> tr_tree) override;

    protected:
        std::shared_ptr<Model> model;
};

#endif // TREE_FACTORY_H
