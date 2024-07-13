#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../window/window.hpp"
#include <memory>
#include <string>
#include <unordered_map>

class ResourceHandler {
public:
    ResourceHandler();
    ~ResourceHandler();

    void PrintTextures();
    void ClearResources();
    void AddTexture(const std::string& assetId, const std::string& filePath);
    SDL_Texture* GetTexture(const std::string& assetId);

private:
    std::unordered_map<std::string, SDL_Texture*> mTextures;
};

