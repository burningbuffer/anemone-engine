#include "playercontroller.hpp"
#include "../core/corehandler.hpp"
#include "../components/components.hpp"
#include "../eventhandler/eventhandler.hpp"
#include "../logger/logger.hpp"

extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<EventHandler> gEventHandler;

PlayerController::PlayerController(Entity entity)
{
    this->entity = entity;
}

PlayerController::~PlayerController()
{
}

void PlayerController::Subscribe()
{
    gEventHandler->SubscribeToEvent<KeyPressedEvent>(this, &PlayerController::OnKeyPressed);
	gEventHandler->SubscribeToEvent<KeyReleasedEvent>(this, &PlayerController::OnKeyReleased);
}

void PlayerController::OnKeyPressed(KeyPressedEvent &event)
{
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

void PlayerController::OnKeyReleased(KeyReleasedEvent &event)
{
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

void PlayerController::Update(float DeltaTime)
{
    auto& transform = gCoreHandler->GetComponent<TransformComponent>(entity);
    auto& rigidBody = gCoreHandler->GetComponent<RigidBodyComponent>(entity);

    b2Vec2 velocity = b2Body_GetLinearVelocity(rigidBody.body);

    if(move_y_top == true)
    {
        velocity.y = -speed; 
    }
    else if(move_y_down == true)
    {
        velocity.y = speed; 
    }
    else
    { 
        velocity.y = 0;
    }
    if(move_x_left == true)
    {
        velocity.x = -speed; 
        Logger::Log("move_x_left flag");
    }
    else if(move_x_right == true)
    {
        velocity.x = speed; 
        Logger::Log("move_x_right flag");
    }
    else
    {
        velocity.x = 0;
    }

    b2Body_SetLinearVelocity(rigidBody.body, velocity);

    b2Vec2 rigidbody_pos = b2Body_GetPosition(rigidBody.body);
    transform.Position.x = rigidbody_pos.x;
    transform.Position.y = rigidbody_pos.y;
}
