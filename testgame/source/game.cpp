#include "game.hpp"
#include <glm/glm.hpp>
#include <anemone/core/corehandler.hpp>
#include <anemone/resourcehandler/resourcehandler.hpp>
#include <anemone/components/components.hpp>
#include <anemone/systems/rendersystem.hpp>
// #include <anemone/systems/damagesystem.hpp>
#include <anemone/logger/logger.hpp>
#include <anemone/window/window.hpp>
#include <anemone/eventhandler/eventhandler.hpp>
#include <anemone/events/keypressedevent.hpp>
#include <anemone/events/keyreleasedevent.hpp>
#include <anemone/physics/physicshandler.hpp>
#include <anemone/systems/playercontroller.hpp>
#include <iostream>
#include <memory>
#include <box2d/box2d.h>

std::unique_ptr<CoreHandler> gCoreHandler;
std::unique_ptr<Window> gWindow;
std::unique_ptr<ResourceHandler> gResourceHandler;
std::unique_ptr<EventHandler> gEventHandler;
std::unique_ptr<PhysicsHandler> gPhysicsHandler;

std::unique_ptr<PlayerController> gPlayerController;
///std::shared_ptr<DamageSystem> damageSystem;
std::shared_ptr<RenderSystem> renderSystem;

b2Vec2 gGravity = {0.0f, 0.0f};
b2WorldDef worldDef;
b2WorldId gWorldId;
float gTimeStep = 1.0f / 60.0f;
int gSubStepCount = 8;

int gWindowWidth = 800;
int gWindowHeight = 600;

Game::Game() {}
Game::~Game() {}

bool Game::Initialize() 
{
    
    gCoreHandler = std::make_unique<CoreHandler>();
    gWindow = std::make_unique<Window>();
    gResourceHandler = std::make_unique<ResourceHandler>();
    gEventHandler = std::make_unique<EventHandler>();
    gCoreHandler->Init();
    isRunning = gWindow->CreateWindow("my game", gWindowWidth, gWindowHeight);

    if (!isRunning) 
    {
        Logger::Err("Window Creation Failed");
        return false;
    }

    worldDef = b2DefaultWorldDef();
    worldDef.gravity = gGravity;

    gWorldId = b2CreateWorld(&worldDef);

    gResourceHandler->AddTexture("tank_image","resources/images/tank-panther-right.png");
    gResourceHandler->AddTexture("truck_image","resources/images/truck-ford-right.png");

    gCoreHandler->CreateComponent<TransformComponent>();
    gCoreHandler->CreateComponent<RigidBodyComponent>();
    gCoreHandler->CreateComponent<SpriteComponent>();
    gCoreHandler->CreateComponent<BoxColliderComponent>();

    renderSystem = gCoreHandler->CreateSystem<RenderSystem>();
    //damageSystem = gCoreHandler->CreateSystem<DamageSystem>();

    Entity tank = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(tank, TransformComponent{glm::vec2{157, 30}});
    gCoreHandler->AddComponent(tank, RigidBodyComponent{});
    gCoreHandler->AddComponent(tank, SpriteComponent{"tank_image", 32, 32});
    gCoreHandler->AddComponent(tank, BoxColliderComponent{glm::vec2{14.0f, 9.5f}, glm::vec2{1 , 0}});

    CreateBody(tank, b2_dynamicBody);
    
    gPlayerController = std::make_unique<PlayerController>(tank, 100.0f);

    Entity truck = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(truck, TransformComponent{glm::vec2{130, 160}});
    gCoreHandler->AddComponent(truck, RigidBodyComponent{});
    gCoreHandler->AddComponent(truck, SpriteComponent{"truck_image", 64, 64});
    gCoreHandler->AddComponent(truck, BoxColliderComponent{glm::vec2{14.0f, 9.5f}, glm::vec2{1 , 0}});

    CreateBody(truck, b2_staticBody);

    Entity truck2 = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(truck2, TransformComponent{glm::vec2{230, 270}});
    gCoreHandler->AddComponent(truck2, RigidBodyComponent{});
    gCoreHandler->AddComponent(truck2, SpriteComponent{"truck_image", 32, 32});
    gCoreHandler->AddComponent(truck2, BoxColliderComponent{glm::vec2{14.0f, 9.5f}, glm::vec2{1 , 0}});

    CreateBody(truck2, b2_staticBody);

    Entity truck3 = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(truck3, TransformComponent{glm::vec2{130, 270}});
    gCoreHandler->AddComponent(truck3, RigidBodyComponent{});
    gCoreHandler->AddComponent(truck3, SpriteComponent{"truck_image", 32, 32});
    gCoreHandler->AddComponent(truck3, BoxColliderComponent{glm::vec2{14.0f, 9.5f}, glm::vec2{1 , 0}});

    CreateBody(truck3, b2_staticBody);

    return true;
}

void Game::CreateBody(Entity e, b2BodyType bodyType)
{
    auto& transform = gCoreHandler->GetComponent<TransformComponent>(e);
    auto& rigidbody = gCoreHandler->GetComponent<RigidBodyComponent>(e);

    b2BodyDef bodyDef = b2DefaultBodyDef();
    bodyDef.type = bodyType;
    bodyDef.position = b2Vec2{transform.Position.x , transform.Position.y};
    bodyDef.fixedRotation = true;
    bodyDef.userData = &e;
    bodyDef.linearDamping = 0.0f;

    rigidbody.body = b2CreateBody(gWorldId, &bodyDef);

    if(gCoreHandler->HasComponent<BoxColliderComponent>(e))
    {
        auto& box_collider = gCoreHandler->GetComponent<BoxColliderComponent>(e);
    
        box_collider.boxCollider = b2MakeOffsetBox(box_collider.size.x, box_collider.size.y, b2Vec2{box_collider.offset.x , box_collider.offset.y}, b2MakeRot(0.0f));
        
        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.friction = 0.0f;
        shapeDef.restitution = 0.0;
        box_collider.shapeId = b2CreatePolygonShape(rigidbody.body, &shapeDef, &box_collider.boxCollider);
    }

    Logger::Log("CreateBody");
}

void Game::ProcessInput() 
{
    if (glfwGetKey(gWindow->GetWindow(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(gWindow->GetWindow(), true);
}

void Game::Update() 
{
    float currentFrame = static_cast<float>(glfwGetTime());
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    gEventHandler->Clear();

    // Subscribe Systems

    //damageSystem->Subscribe();

    gPlayerController->Subscribe();

    // Update Systems

    gPlayerController->Update(deltaTime);

    renderSystem->Update(deltaTime);

    //collisionSystem->Update(deltaTime);

    //damageSystem->Update(deltaTime);

    // Update Objects

    gCoreHandler->Update();

    UpdateBox2d();
}

void Game::UpdateBox2d()
{
    b2World_Step(gWorldId, gTimeStep, gSubStepCount);
}

void Game::Render() 
{
    gWindow->RenderClear(222, 222, 222, 255);

    renderSystem->Render();

    gWindow->RenderPresent();
}

void Game::Run() 
{
    while (!glfwWindowShouldClose(gWindow->GetWindow())) 
    {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy() 
{
    gWindow->DestroyWindow();
    gResourceHandler->ClearResources();
    b2DestroyWorld(gWorldId);
}


