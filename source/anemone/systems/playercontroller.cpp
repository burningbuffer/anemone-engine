#include <GL/glew.h>
#include "playercontroller.hpp"
#include "../core/corehandler.hpp"
#include "../components/components.hpp"
#include "../eventhandler/eventhandler.hpp"
#include "../logger/logger.hpp"
#include "../window/window.hpp"

extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<Window> gWindow;
extern std::unique_ptr<EventHandler> gEventHandler;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        gEventHandler->TriggerEvent<KeyPressedEvent>(key);
    }
    else if (action == GLFW_RELEASE)
    {
        gEventHandler->TriggerEvent<KeyReleasedEvent>(key);
    }
}

PlayerController::PlayerController(Entity entity, float speed)
{
    this->entity = entity;
    this->speed = speed;

    glfwSetKeyCallback(gWindow->GetWindow(), key_callback);
}

PlayerController::~PlayerController()
{
}


void PlayerController::Subscribe()
{
    gEventHandler->SubscribeToEvent<KeyPressedEvent>(this, &PlayerController::OnKeyPressed);
	gEventHandler->SubscribeToEvent<KeyReleasedEvent>(this, &PlayerController::OnKeyReleased);
}

void PlayerController::OnKeyPressed(KeyPressedEvent& e)//Event
{
    switch (e.key) {
        case GLFW_KEY_W: move_y_top = true; break;
        case GLFW_KEY_S: move_y_down = true; break;
        case GLFW_KEY_A: move_x_left = true; break;
        case GLFW_KEY_D: move_x_right = true; break;
    }
}

void PlayerController::OnKeyReleased(KeyReleasedEvent& e)
{
    switch (e.key) {
        case GLFW_KEY_W: move_y_top = false; break;
        case GLFW_KEY_S: move_y_down = false; break;
        case GLFW_KEY_A: move_x_left = false; break;
        case GLFW_KEY_D: move_x_right = false; break;
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
    }
    else if(move_x_right == true)
    {
        velocity.x = speed; 
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
