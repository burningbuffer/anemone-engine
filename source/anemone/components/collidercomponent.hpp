#pragma once
#include <box2d/box2d.h>

struct ColliderComponent
{
    virtual ~ColliderComponent() = default;
    
    b2ShapeId shapeId = b2_nullShapeId;
};