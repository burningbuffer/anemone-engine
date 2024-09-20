#pragma once
#include <anemone/utils/common.hpp>
#include <box2d/box2d.h>

class Game 
{
public:
    Game();
    ~Game();

    bool Initialize();
    void Run();
    void ProcessInput();
    void Update();
    void UpdateBox2d();
    void Render();
    void Destroy();

    void CreateBody(Entity e, b2BodyType bodyType);

private:
    const int FPS = 60;
    const int MILLISECS_PER_FRAME = 1000 / FPS;

    bool isRunning = false;
    int millisecsPreviousFrame = 0;
};
