#pragma once
#include <box2d/box2d.h>

class PhysicsHandler
{
public:
    PhysicsHandler(b2Vec2 gravity);
    ~PhysicsHandler();

    void Update();

    b2WorldId World();

private:

    b2WorldId mWorldId;
    float mTimeStep = 1.0f / 60.0f;
    int mSubStepCount = 8;
};