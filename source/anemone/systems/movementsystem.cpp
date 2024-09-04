#include "movementsystem.hpp"
#include <string>
#include <memory>
#include "../components/transformcomponent.hpp"
#include "../components/rigidbodycomponent.hpp"
#include "../components/playercontrollercomponent.hpp"
#include "../eventhandler/eventhandler.hpp"
#include "../core/corehandler.hpp"
#include "../logger/logger.hpp"

extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<EventHandler> gEventHandler;

MovementSystem::MovementSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<RigidBodyComponent>();
	RequireComponent<PlayerControllerComponent>();
}

MovementSystem::~MovementSystem(){}

void MovementSystem::Subscribe()
{
	gEventHandler->SubscribeToEvent<KeyPressedEvent>(this, &MovementSystem::OnKeyPressed);
	gEventHandler->SubscribeToEvent<KeyReleasedEvent>(this, &MovementSystem::OnKeyReleased);
}

void MovementSystem::OnKeyReleased(KeyReleasedEvent &event)
{
	for (auto entity : mEntities)
    {
        auto& playerController = gCoreHandler->GetComponent<PlayerControllerComponent>(entity);

       switch (event.key) {
            case SDLK_w:
				move_y_top = false;
				break;
            case SDLK_s:
                move_y_down = false;
                break;
            case SDLK_a:
				move_x_left = false;
				break;
            case SDLK_d:
				move_x_right = false;
                break;
        }
    }
}

void MovementSystem::OnKeyPressed(KeyPressedEvent &event)
{
	for (auto entity : mEntities)
    {
        auto& controller = gCoreHandler->GetComponent<PlayerControllerComponent>(entity);

        switch (event.key) {
            case SDLK_w:
                move_y_top = true;  
                break;
            case SDLK_s:
                move_y_down = true; 
                break;
            case SDLK_a:
                move_x_left = true; 
                break;
            case SDLK_d:
                move_x_right = true;  
                break;
        }
    }
}

void MovementSystem::Update(float DeltaTime)
{
	for (auto entity : mEntities)
	{
		auto& transform = gCoreHandler->GetComponent<TransformComponent>(entity);
		auto& rigidBody = gCoreHandler->GetComponent<RigidBodyComponent>(entity);

		if(move_y_top == true)
		{
			transform.Position.y -= rigidBody.velocity.y * DeltaTime;
		}
		else if(move_y_down == true)
		{
			transform.Position.y += rigidBody.velocity.y * DeltaTime;
		}
		if(move_x_left == true)
		{
			transform.Position.x -= rigidBody.velocity.x * DeltaTime;
		}
		else if(move_x_right == true)
		{
			transform.Position.x += rigidBody.velocity.x * DeltaTime;
		}
	}
}

template<typename T>
void MovementSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}



