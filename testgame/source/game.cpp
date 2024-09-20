#include "game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <anemone/core/corehandler.hpp>
#include <anemone/resourcehandler/resourcehandler.hpp>
#include <anemone/components/components.hpp>
#include <anemone/systems/rendersystem.hpp>
#include <anemone/systems/damagesystem.hpp>
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
std::shared_ptr<DamageSystem> damageSystem;
std::shared_ptr<RenderSystem> renderSystem;

b2Vec2 gGravity = {0.0f, 0.0f};

b2WorldDef worldDef;

b2WorldId gWorldId;
float mTimeStep = 1.0f / 60.0f;
int mSubStepCount = 8;

Game::Game() {}
Game::~Game() {}

bool Game::Initialize() 
{
    gCoreHandler = std::make_unique<CoreHandler>();
    gWindow = std::make_unique<Window>();
    gResourceHandler = std::make_unique<ResourceHandler>();
    gEventHandler = std::make_unique<EventHandler>();
    gCoreHandler->Init();
    isRunning = gWindow->CreateWindow("my game", 800, 600);

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
    damageSystem = gCoreHandler->CreateSystem<DamageSystem>();

    Entity tank = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(tank, TransformComponent{glm::vec2{10, 30}});
    gCoreHandler->AddComponent(tank, RigidBodyComponent{});
    gCoreHandler->AddComponent(tank, SpriteComponent{"tank_image", 32, 32});
    gCoreHandler->AddComponent(tank, BoxColliderComponent{glm::vec2{28, 19}, glm::vec2{5, 12}});

    CreateBody(tank, b2_dynamicBody);

    gPlayerController = std::make_unique<PlayerController>(tank);

    Entity truck = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(truck, TransformComponent{glm::vec2{10, 160}});
    gCoreHandler->AddComponent(truck, RigidBodyComponent{});
    gCoreHandler->AddComponent(truck, SpriteComponent{"truck_image", 32, 32});
    gCoreHandler->AddComponent(truck, BoxColliderComponent{glm::vec2{28, 19}, glm::vec2{5, 12}});

    // CreateBody(truck, b2_staticBody);
    CreateBody(truck, b2_staticBody);

    return true;
}

void Game::CreateBody(Entity e, b2BodyType bodyType)
{
    auto& transform = gCoreHandler->GetComponent<TransformComponent>(e);
    auto& rigidbody = gCoreHandler->GetComponent<RigidBodyComponent>(e);

    b2BodyDef bodyDef;
    bodyDef = b2DefaultBodyDef();
    bodyDef.type = bodyType;
    bodyDef.position = b2Vec2{transform.Position.x, transform.Position.y};
    bodyDef.fixedRotation = false;

    rigidbody.body = b2CreateBody(gWorldId, &bodyDef);

    b2Body_SetLinearDamping(rigidbody.body, 0.0f);

    if(gCoreHandler->HasComponent<BoxColliderComponent>(e))
    {
        auto& box_collider = gCoreHandler->GetComponent<BoxColliderComponent>(e);
    
        box_collider.boxCollider = b2MakeBox(box_collider.size.x, box_collider.size.y); 

        b2ShapeDef shapeDef = b2DefaultShapeDef();
        shapeDef.density = 1.0f;
        shapeDef.friction = 0.0f;// 0.3f;
        shapeDef.restitution = 0.0;
        b2CreatePolygonShape(rigidbody.body, &shapeDef, &box_collider.boxCollider);
    }

    Logger::Log("CreateBody");
}

void Game::ProcessInput() 
{
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
                gEventHandler->TriggerEvent<KeyPressedEvent>(sdlEvent.key.keysym.sym);
                break;
            case SDL_KEYUP:
                gEventHandler->TriggerEvent<KeyReleasedEvent>(sdlEvent.key.keysym.sym);
        }
    }
}

void Game::Update() 
{
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);

    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    float deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    millisecsPreviousFrame = SDL_GetTicks();

    gEventHandler->Clear();

    // Subscribe Systems

    damageSystem->Subscribe();

    gPlayerController->Subscribe();

    // Update Systems

    gPlayerController->Update(deltaTime);

    renderSystem->Update(deltaTime);

    //collisionSystem->Update(deltaTime);

    damageSystem->Update(deltaTime);

    // Update Objects

    gCoreHandler->Update();

    UpdateBox2d();
}

void Game::UpdateBox2d()
{
    b2World_Step(gWorldId, mTimeStep, mSubStepCount);
}

void Game::Render() 
{
    gWindow->RenderClear(222, 222, 222, 255);

    renderSystem->Render();

    gWindow->RenderPresent();
}

void Game::Run() 
{
    while (isRunning) 
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


