#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <box2d/box2d.h>
#include <iostream>

class Window
{
public:
    Window();
    ~Window();

    bool CreateWindow(const char* windowName, int w, int h);
    bool InitGLFW();
    GLFWwindow* GetWindow();
    void RenderClear(float r, float g, float b, float a);
    void RenderPresent();
    void DestroyWindow();

    int mWindowWidth = 0;
    int mWindowHeight = 0;

    float mAspectRatio = 0.0f;

private:
    const char* mWindowName = nullptr;
    GLFWwindow* mWindow = nullptr;
};