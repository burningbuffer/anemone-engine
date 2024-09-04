#include "rendersystem.hpp"
#include "../components/transformcomponent.hpp"
#include "../components/spritecomponent.hpp"
#include "../window/window.hpp"
#include "../resourcehandler/resourcehandler.hpp"
#include <string>
#include <memory>
#include "../core/corehandler.hpp"
#include "../logger/logger.hpp"
#include <SDL2/SDL.h>

extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<Window> gWindow;
extern std::unique_ptr<ResourceHandler> gResourceHandler;

RenderSystem::RenderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<SpriteComponent>();
}

RenderSystem::~RenderSystem()
{

}

void RenderSystem::Update(float DeltaTime)
{
    
}

void RenderSystem::Render()
{
    for (auto entity : mEntities)
	{
		auto& transform = gCoreHandler->GetComponent<TransformComponent>(entity);
		const auto sprite = gCoreHandler->GetComponent<SpriteComponent>(entity);

        SDL_Rect srcRect = sprite.sourceRect;

        SDL_Rect dstRect = 
        {
            static_cast<int>(transform.Position.x), 
            static_cast<int>(transform.Position.y), 
            static_cast<int>(sprite.width * transform.Scale.x), 
            static_cast<int>(sprite.height * transform.Scale.y) 
        };

        SDL_RenderCopyEx(gWindow->GetRenderer(), gResourceHandler->GetTexture(sprite.textureId), &srcRect, &dstRect, transform.Rotation, NULL, SDL_FLIP_NONE);
        
	}
}

template<typename T>
void RenderSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}
