#pragma once
#include <SDL2/SDL.h>
#include <string>

struct SpriteComponent
{
    std::string assetId;
    SDL_Rect sourceRect;
    int width;
    int height;

    SpriteComponent(std::string assetId = "", int width = 32, int height = 32)
    {
        this->assetId = assetId;
        this->width = width;
        this->height = height;
        this->sourceRect = {0, 0, width, height};
    }

};