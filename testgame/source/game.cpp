#include "game.hpp"

std::unique_ptr<CoreHandler> gCoreHandler;
std::unique_ptr<Window> gWindow;
std::unique_ptr<ResourceHandler> gResourceHandler;
std::shared_ptr<MovementSystem> movementSystem;
std::shared_ptr<RenderSystem> renderSystem;
std::shared_ptr<CollisionSystem> collisionSystem;

Game::Game() {}
Game::~Game() {}

bool Game::Initialize() {
	
    gCoreHandler = std::make_unique<CoreHandler>();
    gWindow = std::make_unique<Window>();
    gResourceHandler = std::make_unique<ResourceHandler>();
    gCoreHandler->Init();
    isRunning = gWindow->CreateWindow("my game", 800, 600);

    if (!isRunning) {
        Logger::Err("Window Creation Failed");
        return false;
    }

    gResourceHandler->AddTexture("tank_image","resources/images/tank-panther-right.png");
    gResourceHandler->AddTexture("truck_image","resources/images/truck-ford-right.png");

    gCoreHandler->CreateComponent<TransformComponent>();
    gCoreHandler->CreateComponent<RigidBodyComponent>();
    gCoreHandler->CreateComponent<SpriteComponent>();
    gCoreHandler->CreateComponent<BoxColliderComponent>();

    movementSystem = gCoreHandler->CreateSystem<MovementSystem>();
    renderSystem = gCoreHandler->CreateSystem<RenderSystem>();
    collisionSystem = gCoreHandler->CreateSystem<CollisionSystem>();

    Entity car = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(car, TransformComponent{ glm::vec2{10, 30}, glm::vec2{2, 2}, 0.0 });
    gCoreHandler->AddComponent(car, RigidBodyComponent{ glm::vec2{40, 0.0} });
    gCoreHandler->AddComponent(car, SpriteComponent{"tank_image", 32, 32});
    gCoreHandler->AddComponent(car, BoxColliderComponent{32, 32, glm::vec2{0}});

    Entity boat = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(boat, TransformComponent{ glm::vec2{300, 30}, glm::vec2{2, 2}, 0.0 });
    gCoreHandler->AddComponent(boat, RigidBodyComponent{ glm::vec2{-40.0, 0.0} });
    gCoreHandler->AddComponent(boat, SpriteComponent{"truck_image", 32, 32});
    gCoreHandler->AddComponent(boat, BoxColliderComponent{32, 32, glm::vec2{0}});

    return true;
}

void Game::ProcessInput() {
    SDL_Event sdlEvent;
    while (SDL_PollEvent(&sdlEvent)) {
        switch (sdlEvent.type) {
            case SDL_QUIT:
                isRunning = false;
                break;
            case SDL_KEYDOWN:
                if (sdlEvent.key.keysym.sym == SDLK_ESCAPE) isRunning = false;
                break;
        }
    }
}

void Game::Update() {
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPreviousFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    float deltaTime = (SDL_GetTicks() - millisecsPreviousFrame) / 1000.0;
    millisecsPreviousFrame = SDL_GetTicks();

    gCoreHandler->UpdateSystems(deltaTime);
}

void Game::Render() {
    gWindow->RenderClear(222, 222, 222, 255);
    renderSystem->Render();
    gWindow->RenderPresent();
}

void Game::Run() {
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}

void Game::Destroy() {
    gWindow->DestroyWindow();
    gResourceHandler->ClearResources();
}
