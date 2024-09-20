#include "rendersystem.hpp"
#include "../components/rigidbodycomponent.hpp"
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
    RequireComponent<RigidBodyComponent>();
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
		auto& transform = gCoreHandler->GetComponent<RigidBodyComponent>(entity);
		const auto sprite = gCoreHandler->GetComponent<SpriteComponent>(entity);

        SDL_Rect srcRect = sprite.sourceRect;

        b2Vec2 position = b2Body_GetPosition(transform.body);

        SDL_Rect dstRect = 
        {
            static_cast<int>(position.x), 
            static_cast<int>(position.y), 
            //static_cast<int>(sprite.width * transform.Scale.x), 
            static_cast<int>(sprite.width), 
            //static_cast<int>(sprite.height * transform.Scale.y) 
            static_cast<int>(sprite.height)
        };

        SDL_RenderCopyEx(gWindow->GetRenderer(), gResourceHandler->GetTexture(sprite.textureId), &srcRect, &dstRect, 0.0f, NULL, SDL_FLIP_NONE);
        
	}
}

template<typename T>
void RenderSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}
