#pragma once
#include <SDL2/SDL.h>
#include <string>

struct SpriteComponent
{
    SpriteComponent(std::string textureId = "", int width = 32, int height = 32)
    {
        this->textureId = textureId;
        this->width = width;
        this->height = height;
        this->sourceRect = {0, 0, width, height};
    }

    std::string textureId;
    SDL_Rect sourceRect;
    int width;
    int height;

};