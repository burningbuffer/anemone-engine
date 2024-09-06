#include "./debugrenderingsystem.hpp"
#include "../window/window.hpp"

extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<Window> gWindow;
extern std::unique_ptr<EventHandler> gEventHandler;

DebugRenderingSystem::DebugRenderingSystem()
{
	RequireComponent<TransformComponent>();
    RequireComponent<BoxColliderComponent>();
}

DebugRenderingSystem::~DebugRenderingSystem(){}

void DebugRenderingSystem::Update(float DeltaTime)
{
   
}

void DebugRenderingSystem::Render()
{
     for (auto entity : mEntities)
	{
		auto& transform = gCoreHandler->GetComponent<TransformComponent>(entity);
		const auto box_collider = gCoreHandler->GetComponent<BoxColliderComponent>(entity);

        SDL_Rect boxColliderRect = 
        {
            static_cast<int>(transform.Position.x), 
            static_cast<int>(transform.Position.y), 
            static_cast<int>(box_collider.width * transform.Scale.x), 
            static_cast<int>(box_collider.height * transform.Scale.y) 
        };

        SDL_SetRenderDrawColor(gWindow->GetRenderer(), 255, 0, 0, 255);
        SDL_RenderDrawRect(gWindow->GetRenderer(), &boxColliderRect);


	}
}


template<typename T>
void DebugRenderingSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}

