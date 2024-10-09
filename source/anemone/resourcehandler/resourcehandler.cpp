#include "resourcehandler.hpp"
#include "../logger/logger.hpp"
#include <iostream>
#include <memory>
#define STB_IMAGE_IMPLEMENTATION
#include "../graphics/stb_image.h"

extern std::unique_ptr<Window> gWindow;

ResourceHandler::ResourceHandler() {}

ResourceHandler::~ResourceHandler() 
{
    ClearResources();
}

void ResourceHandler::PrintTextures()
{
    for (auto& texturePair : mTextures) {
        std::cout << texturePair.first << std::endl;
    }
}

void ResourceHandler::ClearResources() 
{
    mTextures.clear();
}

void ResourceHandler::AddTexture(const std::string& textureId, const std::string& filePath) 
{
    GLuint texture;
    glGenTextures(1, &texture);
    int imWidth, ImHeight, nrComponents;
    unsigned char* data = stbi_load(filePath.c_str(), &imWidth, &ImHeight, &nrComponents, 0);

    if(data)
    {
        
        GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, texture);
		glTexImage2D(GL_TEXTURE_2D, 0, format, imWidth, ImHeight, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);

	}
	else
	{
		std::cout << "Texture failed to load at path: " << filePath << std::endl;
		stbi_image_free(data);
	}

    mTextures.insert({textureId, texture});
    Logger::Log("New texture added with id = " + textureId);
}

GLuint ResourceHandler::GetTexture(const std::string& textureId) 
{
    return mTextures[textureId];
}

