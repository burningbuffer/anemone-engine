#include "damagesystem.hpp"

extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<EventHandler> gEventHandler;

DamageSystem::DamageSystem()
{
	RequireComponent<TransformComponent>();
    RequireComponent<RigidBodyComponent>();
    RequireComponent<BoxColliderComponent>();
}

DamageSystem::~DamageSystem(){}

void DamageSystem::Subscribe()
{
    gEventHandler->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
}

void DamageSystem::Update(float DeltaTime)
{
    
}

void DamageSystem::OnCollision(CollisionEvent& event)
{
    Logger::Log("Test Collision event triggered");
    gCoreHandler->addToRemoveEntity(event.a);
    gCoreHandler->addToRemoveEntity(event.b);
}

template<typename T>
void DamageSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}

