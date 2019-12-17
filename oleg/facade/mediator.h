#ifndef MEDIATOR_H
#define MEDIATOR_H

#include "facade.h"
#include "actions/action.h"

class Mediator
{
public:
    Mediator()
    {
        facade = std::make_shared<Facade>();
    }

    ~Mediator() = default;

    void executeAction(BaseAction& action)
    {
        action.execute(facade);
    }

private:
    std::shared_ptr<Facade> facade;
};

#endif // MEDIATOR_H

