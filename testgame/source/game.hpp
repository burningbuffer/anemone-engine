#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <glm/glm.hpp>
#include <anemone/core/corehandler.hpp>
#include <anemone/resourcehandler/resourcehandler.hpp>
#include <anemone/components/transformcomponent.hpp>
#include <anemone/components/rigidbodycomponent.hpp>
#include <anemone/components/spritecomponent.hpp>
#include <anemone/systems/movementsystem.hpp>
#include <anemone/systems/rendersystem.hpp>
#include <anemone/systems/collisionsystem.hpp>
#include <anemone/systems/damagesystem.hpp>
#include <anemone/logger/logger.hpp>
#include <anemone/window/window.hpp>
#include <anemone/eventhandler/eventhandler.hpp>
#include <iostream>
#include <memory>

class Game {
public:
    Game();
    ~Game();

    bool Initialize();
    void Run();
    void ProcessInput();
    void Update();
    void Render();
    void Destroy();

private:
    const int FPS = 60;
    const int MILLISECS_PER_FRAME = 1000 / FPS;

    bool isRunning = false;
    int millisecsPreviousFrame = 0;
};
