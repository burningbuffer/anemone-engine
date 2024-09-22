#pragma once
#include <SDL2/SDL.h>

class Window
{
public:

    Window();
    ~Window();

    bool CreateWindow(const char* windowName, int w, int h);
    bool InitSDL();
    SDL_Renderer* GetRenderer();
    void RenderClear(int r, int g, int b, int a);
    void RenderPresent();
    void DestroyWindow();

    int mWindowWidth = NULL;
    int mWindowHeight = NULL;

    float mAspectRatio = NULL;

private:

    const char* mWindowName = nullptr;
    SDL_Window* mWindow = NULL;
    SDL_Renderer* mRenderer = NULL;
    SDL_Texture* mTexture = NULL;
    SDL_DisplayMode mDisplayMode;

};