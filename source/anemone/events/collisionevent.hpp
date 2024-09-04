#pragma once

#include "../eventhandler/event.hpp"
#include "../utils/common.hpp"

class CollisionEvent : public Event 
{
public:
    CollisionEvent(Entity a, Entity b)
    {
        this->a = a;
        this->b = b;
    }

    Entity a;
    Entity b;
};