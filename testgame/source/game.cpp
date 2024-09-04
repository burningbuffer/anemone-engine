#include "game.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <anemone/core/corehandler.hpp>
#include <anemone/resourcehandler/resourcehandler.hpp>
#include <anemone/components/components.hpp>
#include <anemone/systems/movementsystem.hpp>
#include <anemone/systems/rendersystem.hpp>
#include <anemone/systems/collisionsystem.hpp>
#include <anemone/systems/damagesystem.hpp>
#include <anemone/logger/logger.hpp>
#include <anemone/window/window.hpp>
#include <anemone/eventhandler/eventhandler.hpp>
#include <anemone/events/keypressedevent.hpp>
#include <anemone/events/keyreleasedevent.hpp>
#include <iostream>
#include <memory>

std::unique_ptr<CoreHandler> gCoreHandler;
std::unique_ptr<Window> gWindow;
std::unique_ptr<ResourceHandler> gResourceHandler;
std::unique_ptr<EventHandler> gEventHandler;

std::shared_ptr<MovementSystem> movementSystem;
std::shared_ptr<DamageSystem> damageSystem;
std::shared_ptr<RenderSystem> renderSystem;
std::shared_ptr<CollisionSystem> collisionSystem;

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

    gResourceHandler->AddTexture("tank_image","resources/images/tank-panther-right.png");
    gResourceHandler->AddTexture("truck_image","resources/images/truck-ford-right.png");

    gCoreHandler->CreateComponent<TransformComponent>();
    gCoreHandler->CreateComponent<RigidBodyComponent>();
    gCoreHandler->CreateComponent<SpriteComponent>();
    gCoreHandler->CreateComponent<BoxColliderComponent>();
    gCoreHandler->CreateComponent<PlayerControllerComponent>();

    movementSystem = gCoreHandler->CreateSystem<MovementSystem>();
    renderSystem = gCoreHandler->CreateSystem<RenderSystem>();
    collisionSystem = gCoreHandler->CreateSystem<CollisionSystem>();
    damageSystem = gCoreHandler->CreateSystem<DamageSystem>();

    Entity tank = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(tank, TransformComponent{ glm::vec2{10, 30}, glm::vec2{2, 2}, 0.0 });
    gCoreHandler->AddComponent(tank, RigidBodyComponent{ glm::vec2{100.0, 100.0} });
    gCoreHandler->AddComponent(tank, SpriteComponent{"tank_image", 32, 32});
    gCoreHandler->AddComponent(tank, BoxColliderComponent{32, 32, glm::vec2{0}});
    gCoreHandler->AddComponent(tank, PlayerControllerComponent{});

    Entity truck = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(truck, TransformComponent{ glm::vec2{300, 30}, glm::vec2{2, 2}, 0.0 });
    gCoreHandler->AddComponent(truck, RigidBodyComponent{ glm::vec2{100.0, 100.0} });
    gCoreHandler->AddComponent(truck, SpriteComponent{"truck_image", 32, 32});
    gCoreHandler->AddComponent(truck, BoxColliderComponent{32, 32, glm::vec2{0}});

    return true;
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

    movementSystem->Subscribe();

    // Update Systems

    movementSystem->Update(deltaTime);

    renderSystem->Update(deltaTime);

    collisionSystem->Update(deltaTime);

    damageSystem->Update(deltaTime);

    // Update Objects

    gCoreHandler->Update();
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
}
