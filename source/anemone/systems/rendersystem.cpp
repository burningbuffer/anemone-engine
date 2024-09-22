#include "rendersystem.hpp"
#include "../components/transformcomponent.hpp"
#include "../components/rigidbodycomponent.hpp"
#include "../components/spritecomponent.hpp"
#include "../components/boxcollidercomponent.hpp"
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
    RequireComponent<RigidBodyComponent>();
    RequireComponent<SpriteComponent>();
    RequireComponent<BoxColliderComponent>();
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
		auto& rigidbody = gCoreHandler->GetComponent<RigidBodyComponent>(entity);
		const auto sprite = gCoreHandler->GetComponent<SpriteComponent>(entity);
        const auto box_collider = gCoreHandler->GetComponent<BoxColliderComponent>(entity);

        SDL_Rect srcRect = sprite.sourceRect;

        b2Vec2 position = b2Body_GetPosition(rigidbody.body);

        // Logger::Log("size");
        // Logger::Log("sprite.width : "+ std::to_string(sprite.width));
        // Logger::Log("sprite.height : "+ std::to_string(sprite.height));

        SDL_Rect dstRect = 
        {
            static_cast<int>(position.x * SCALE), 
            static_cast<int>(position.y * SCALE), 
            //static_cast<int>(sprite.width * transform.Scale.x), 
            static_cast<int>(sprite.width * SCALE), 
            //static_cast<int>(sprite.height * transform.Scale.y) 
            static_cast<int>(sprite.height * SCALE)
        };

        SDL_RenderCopyEx(gWindow->GetRenderer(), gResourceHandler->GetTexture(sprite.textureId), &srcRect, &dstRect, 0.0f, NULL, SDL_FLIP_NONE);

        //b2getpol

        // Logger::Log("size");
        // Logger::Log("box_collider.size.x : "+ std::to_string(box_collider.size.x));
        // Logger::Log("box_collider.size.x : "+ std::to_string(box_collider.size.y));

        //b2AABB ab = b2Shape_GetAABB(box_collider.shapeId);
    
        SDL_Rect boxColliderRect = 
        {
            static_cast<int>(position.x * SCALE), 
            static_cast<int>(position.y * SCALE), 
            static_cast<int>(box_collider.size.x * 2 * SCALE), 
            static_cast<int>(box_collider.size.y * 2 * SCALE) 
            // static_cast<int>(box_collider.size.x * transform.Scale.x), 
            // static_cast<int>(box_collider.size.y * transform.Scale.y) 
        };
        SDL_SetRenderDrawColor(gWindow->GetRenderer(), 255, 0, 0, 255);
        SDL_RenderDrawRect(gWindow->GetRenderer(), &boxColliderRect);

        // b2Polygon shape = b2Shape_GetPolygon(box_collider.shapeId);

        // b2Shape

        // SDL_Rect boxSpriteRect = 
        // {
        //     static_cast<int>(transform.Position.x), 
        //     static_cast<int>(transform.Position.y), 
        //     static_cast<int>(sprite.width), 
        //     static_cast<int>(sprite.height) 
        //     // static_cast<int>(box_collider.size.x * transform.Scale.x), 
        //     // static_cast<int>(box_collider.size.y * transform.Scale.y) 
        // };
        // SDL_SetRenderDrawColor(gWindow->GetRenderer(), 0, 255, 0, 255);
        // SDL_RenderDrawRect(gWindow->GetRenderer(), &boxSpriteRect);


	}
}

template<typename T>
void RenderSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}
