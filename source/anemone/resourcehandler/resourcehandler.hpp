#pragma once
#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../window/window.hpp"
#include <memory>
#include <string>
#include <unordered_map>

class ResourceHandler 
{
public:
    ResourceHandler();
    ~ResourceHandler();
    
    void PrintTextures();
    void ClearResources();
    void AddTexture(const std::string& textureId, const std::string& filePath);
    GLuint GetTexture(const std::string& textureId);

private:
    std::unordered_map<std::string, GLuint> mTextures;
};

