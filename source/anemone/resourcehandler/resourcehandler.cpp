#include "resourcehandler.hpp"
#include "../logger/logger.hpp"
#include <iostream>
#include <memory>

extern std::unique_ptr<Window> gWindow;

ResourceHandler::ResourceHandler() {}

ResourceHandler::~ResourceHandler() {
    ClearResources();
}

void ResourceHandler::PrintTextures()
{
    for (auto& texturePair : mTextures) {
        std::cout << texturePair.first << std::endl;
    }
}

void ResourceHandler::ClearResources() {
    for (auto& texturePair : mTextures) {
        SDL_DestroyTexture(texturePair.second);
    }
    mTextures.clear();
}

void ResourceHandler::AddTexture(const std::string& assetId, const std::string& filePath) {
    SDL_Surface* surface = IMG_Load(filePath.c_str());
    SDL_Texture* texture = SDL_CreateTextureFromSurface(gWindow->GetRenderer(), surface);
    SDL_FreeSurface(surface);
    mTextures.insert({assetId, texture});
    Logger::Log("New texture added with id = " + assetId);
}

SDL_Texture* ResourceHandler::GetTexture(const std::string& assetId) {
    return mTextures[assetId];
}

