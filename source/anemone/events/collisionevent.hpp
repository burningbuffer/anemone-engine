#pragma once

#include "../eventhandler/event.hpp"
#include "../utils/common.hpp"

class CollisionEvent : public Event 
{
public:
    Entity a;
    Entity b;
    CollisionEvent(Entity a, Entity b)
    {
        this->a = a;
        this->b = b;
    }

};