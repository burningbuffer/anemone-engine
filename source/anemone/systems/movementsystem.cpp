#include "movementsystem.hpp"
#include <string>
#include <memory>
#include "../components/transformcomponent.hpp"
#include "../components/rigidbodycomponent.hpp"
#include "../core/corehandler.hpp"
#include "../logger/logger.hpp"

extern std::unique_ptr<CoreHandler> gCoreHandler;

MovementSystem::MovementSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<RigidBodyComponent>();
}

MovementSystem::~MovementSystem(){}

void MovementSystem::Update(float DeltaTime)
{
	for (auto entity : mEntities)
	{
		auto& transform = gCoreHandler->GetComponent<TransformComponent>(entity);
		const auto rigidBody = gCoreHandler->GetComponent<RigidBodyComponent>(entity);

		transform.Position.x += rigidBody.velocity.x * DeltaTime;
		transform.Position.y += rigidBody.velocity.y * DeltaTime;
	}
}

template<typename T>
void MovementSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}



