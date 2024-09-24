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
    
        glm::vec2 position = transform.Position;

        SDL_Rect dstRect = 
        {
            static_cast<int>(position.x * SCALE), 
            static_cast<int>(position.y * SCALE),  
            static_cast<int>(sprite.width * SCALE), 
            static_cast<int>(sprite.height * SCALE)
        };

        SDL_RenderCopyEx(gWindow->GetRenderer(), gResourceHandler->GetTexture(sprite.textureId), &srcRect, &dstRect, 0.0f, NULL, SDL_FLIP_NONE);

        RenderPolygon(box_collider.shapeId, rigidbody.body);
	}
}

void RenderSystem::RenderPolygon(b2ShapeId shape, b2BodyId body)
{
    b2Polygon p = b2Shape_GetPolygon(shape);
    const int vertexCount = p.count;
    SDL_Point* points = new SDL_Point[vertexCount + 1];

    for (int i = 0; i < vertexCount; ++i) {
        b2Vec2 worldPoint = b2Body_GetWorldPoint(body, p.vertices[i]);
        points[i].x = (int)(worldPoint.x * SCALE);
        points[i].y = (int)(worldPoint.y * SCALE);
    }
    
    points[vertexCount] = points[0];

    SDL_SetRenderDrawColor(gWindow->GetRenderer(), 255, 0, 0, 255);
    SDL_RenderDrawLines(gWindow->GetRenderer(), points, vertexCount + 1);

    delete[] points;
}

template<typename T>
void RenderSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}
