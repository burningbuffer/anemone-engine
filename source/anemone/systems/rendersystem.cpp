#include "rendersystem.hpp"
#include "../components/transformcomponent.hpp"
#include "../components/rigidbodycomponent.hpp"
#include "../components/spritecomponent.hpp"
#include "../components/boxcollidercomponent.hpp"
#include "../window/window.hpp"
#include "../resourcehandler/resourcehandler.hpp"
#include "../graphics/shader.hpp"
#include "../graphics/mesh.hpp"
#include "../graphics/quad.hpp"
#include <string>
#include <memory>
#include "../core/corehandler.hpp"
#include "../logger/logger.hpp"

extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<Window> gWindow;
extern std::unique_ptr<ResourceHandler> gResourceHandler;

std::shared_ptr<Shader> shader;
std::unique_ptr<Mesh> quad_mesh;

RenderSystem::RenderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<RigidBodyComponent>();
    RequireComponent<SpriteComponent>();
    RequireComponent<BoxColliderComponent>();

    shader = std::make_shared<Shader>("resources/shaders/vs.glsl", "resources/shaders/fs.glsl");
    quad_mesh = std::make_unique<Mesh>(quad_vertices, quad_indices);

    shader->useShader();
    
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);  

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

        shader->useShader();

        glm::mat4 model = glm::mat4(1.0f);
		glm::mat4 projection = glm::mat4(1.0f);

        projection = glm::ortho(
                                0.0f, 
                                static_cast<float>(gWindow->mWindowWidth), 
                                static_cast<float>(gWindow->mWindowHeight), 
                                0.0f, 
                                -1.0f, 
                                1.0f
        );
        
        b2Vec2 pos = b2Body_GetPosition(rigidbody.body);

        model = glm::translate(model, glm::vec3{pos.x, pos.y, 0.0});  
        model = glm::scale(model, glm::vec3{32.0f, 32.0f, 1.0f}); 

        shader->setMat4("model", model);
        shader->setMat4("projection", projection);

        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gResourceHandler->GetTexture(sprite.textureId));

        quad_mesh->Draw(shader);

	}
}

template<typename T>
void RenderSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}
