#include "window.hpp"
#include "../logger/logger.hpp"

Window::Window(){}
Window::~Window(){}

bool Window::CreateWindow(const char *windowName, int w, int h)
{
    mWindowName = windowName;
    mWindowWidth = w;
    mWindowHeight = h;

    InitSDL();

    return true;
}

bool Window::InitSDL()
{
    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        Logger::Err("Error Initializing SDL !");
        return false;
    }

    // SDL_GetCurrentDisplayMode(0, &mDisplayMode);
    // WindowWidth = mDisplayMode.w;
    // WindowHeight = mDisplayMode.h;

    mWindow = SDL_CreateWindow(mWindowName, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, mWindowWidth, mWindowHeight,0); //SDL_WINDOW_BORDERLESS);

    if(!mWindow)
    {
        Logger::Err("Error Creating SDL Window.");
        return false;
    }

    mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if(!mRenderer)
    {
        Logger::Err("Error Creating SDL_Renderer.");
        return false;
    }

    // SDL_SetWindowFullscreen(mWindow, SDL_WINDOW_FULLSCREEN);

    return true;
}

SDL_Renderer* Window::GetRenderer()
{
    return mRenderer;
}

void Window::RenderClear(int r, int g, int b, int a)
{
    SDL_SetRenderDrawColor(mRenderer, r, g, b, a);
	SDL_RenderClear(mRenderer);
}

void Window::RenderPresent()
{
    SDL_RenderPresent(mRenderer);
}

void Window::DestroyWindow()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}
