#include "game.hpp"

std::unique_ptr<CoreHandler> gCoreHandler;
std::unique_ptr<Window> gWindow;
std::unique_ptr<ResourceHandler> gResourceHandler;
std::shared_ptr<MovementSystem> movementSystem;
std::shared_ptr<RenderSystem> renderSystem;

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
    gResourceHandler->AddTexture("truck_panther_image","resources/images/tank-panther-down.png");

    gCoreHandler->CreateComponent<TransformComponent>();
    gCoreHandler->CreateComponent<RigidBodyComponent>();
    gCoreHandler->CreateComponent<SpriteComponent>();

    movementSystem = gCoreHandler->CreateSystem<MovementSystem>();
    renderSystem = gCoreHandler->CreateSystem<RenderSystem>();

    Entity car = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(car, TransformComponent{ glm::vec2{10, 30}, glm::vec2{1, 1}, 0.0 });
    gCoreHandler->AddComponent(car, RigidBodyComponent{ glm::vec2{40, 0.0} });
    gCoreHandler->AddComponent(car, SpriteComponent{"tank_image", 32, 32});

    Entity boat = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(boat, TransformComponent{ glm::vec2{50, 100}, glm::vec2{1, 1}, 0.0 });
    gCoreHandler->AddComponent(boat, RigidBodyComponent{ glm::vec2{0.0, 50} });
    gCoreHandler->AddComponent(boat, SpriteComponent{"truck_image", 32, 32});

    Entity heli = gCoreHandler->CreateEntity();
    gCoreHandler->AddComponent(heli, TransformComponent{ glm::vec2{100, 100}, glm::vec2{1, 1}, 0.0 });
    gCoreHandler->AddComponent(heli, RigidBodyComponent{ glm::vec2{25.0, 50} });
    gCoreHandler->AddComponent(heli, SpriteComponent{"truck_panther_image", 32, 32});

    //gCoreHandler->RemoveComponent<RigidBodyComponent>(boat);
    //gCoreHandler->DestroyEntity(boat);

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
    gWindow->RenderClear(21, 21, 21, 255);
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
