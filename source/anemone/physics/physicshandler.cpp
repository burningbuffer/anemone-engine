#include "physicshandler.hpp"

PhysicsHandler::PhysicsHandler(b2Vec2 gravity)
{
    b2WorldDef worldDef;
    worldDef = b2DefaultWorldDef();
    worldDef.gravity = gravity;

    mWorldId = b2CreateWorld(&worldDef);
}

PhysicsHandler::~PhysicsHandler()
{
    b2DestroyWorld(mWorldId);
}

b2WorldId PhysicsHandler::World()
{
    return mWorldId;
}

void PhysicsHandler::Update()
{
    b2World_Step(mWorldId, mTimeStep, mSubStepCount);

}
