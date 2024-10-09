#pragma once
#include <anemone/utils/common.hpp>
#include <box2d/box2d.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

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

    float deltaTime = 0.0f;
    float lastFrame = 0.0f;


};
