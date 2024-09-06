#pragma once

class Game 
{
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
