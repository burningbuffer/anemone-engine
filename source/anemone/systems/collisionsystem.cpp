#include "collisionsystem.hpp"

extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<EventHandler> gEventHandler;

CollisionSystem::CollisionSystem()
{
	RequireComponent<TransformComponent>();
    RequireComponent<BoxColliderComponent>();
}

CollisionSystem::~CollisionSystem(){}

void CollisionSystem::Update(float DeltaTime)
{
    for (auto a : mEntities)
	{
		auto& a_transform = gCoreHandler->GetComponent<TransformComponent>(a);
		auto& a_boxcollider = gCoreHandler->GetComponent<BoxColliderComponent>(a);

		for (auto b : mEntities)
	    {
			if(a != b)
			{
				auto& b_transform = gCoreHandler->GetComponent<TransformComponent>(b);
				auto& b_boxcollider = gCoreHandler->GetComponent<BoxColliderComponent>(b);

				bool collision = CheckAABBCollision(
									a_transform.Position.x,
									a_transform.Position.y,
									a_boxcollider.width,
									a_boxcollider.height,
									b_transform.Position.x,
									b_transform.Position.y,
									b_boxcollider.width,
									b_boxcollider.height);

				if(collision)
				{
					Logger::Log("Collision Happening !");
					gEventHandler->TriggerEvent<CollisionEvent>(a, b);
				} 
			}
            
	    }
	}
}

bool CollisionSystem::CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH)
{
	return (aX < bX + bW && aX + aW > bX && aY < bY + bH && aY + aH > bY);
}

template<typename T>
void CollisionSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}

