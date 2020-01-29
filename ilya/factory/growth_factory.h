#ifndef GROWTH_FACTORY_H
#define GROWTH_FACTORY_H

#include "growth_methods.h"
#include "../object/transformed_model.h"
#include "object_factory.h"
#include "tree_factory.h"

#include <vector>

using namespace std;


class Growth
{
  public:
    virtual vector<shared_ptr<Object>> buildModel(shared_ptr<Tree> tree, shared_ptr<Transform_Tree> tr_tree,
                                                  tree_params params) = 0;
    virtual ~Growth() {}
    static shared_ptr<Growth> createGrowth(Growth_ID id, int iteration);
};

class Linear: public Growth
{
    public:
        Linear(int iteration) : iteration(iteration) {}
        ~Linear() override = default;

        vector<shared_ptr<Object>> buildModel(shared_ptr<Tree> tree, shared_ptr<Transform_Tree> tr_tree,
                                              tree_params params) override;
    private:
        int iteration;
};


#endif // GROWTH_FACTORY_H
