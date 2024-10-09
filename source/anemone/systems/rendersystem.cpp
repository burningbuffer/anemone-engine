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
#include <SDL2/SDL.h>


extern std::unique_ptr<CoreHandler> gCoreHandler;
extern std::unique_ptr<Window> gWindow;
extern std::unique_ptr<ResourceHandler> gResourceHandler;

std::shared_ptr<Shader> shader;
//std::shared_ptr<Shader> screenShader;

std::unique_ptr<Mesh> quad_mesh;

RenderSystem::RenderSystem()
{
    RequireComponent<TransformComponent>();
    RequireComponent<RigidBodyComponent>();
    RequireComponent<SpriteComponent>();
    RequireComponent<BoxColliderComponent>();



    //shader = std::make_shared<Shader>("shaders/screen_shader_vs.glsl", "shaders/screen_shader_fs.glsl");
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
                                static_cast<float>(gWindow->mWindowWidth), 
                                0.0f, 
                                -1.0f, 
                                1.0f
        );

        b2Vec2 pos = b2Body_GetPosition(rigidbody.body);

        model = glm::translate(model, glm::vec3{pos.x, pos.y, 0.0});  
        //model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f)); 
        model = glm::scale(model, glm::vec3{50.0f, 50.0f, 1.0f}); 

        shader->setMat4("model", model);
        shader->setMat4("projection", projection);

        glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, gResourceHandler->GetTexture(sprite.textureId));

        quad_mesh->Draw(shader);


	}
}

void RenderSystem::RenderPolygon(b2ShapeId shape, b2BodyId body)
{
    // b2Polygon p = b2Shape_GetPolygon(shape);
    // const int vertexCount = p.count;
    // SDL_Point* points = new SDL_Point[vertexCount + 1];

    // for (int i = 0; i < vertexCount; ++i) {
    //     b2Vec2 worldPoint = b2Body_GetWorldPoint(body, p.vertices[i]);
    //     points[i].x = (int)(worldPoint.x * SCALE);
    //     points[i].y = (int)(worldPoint.y * SCALE);
    // }
    
    // points[vertexCount] = points[0];

    // SDL_SetRenderDrawColor(gWindow->GetRenderer(), 255, 0, 0, 255);
    // SDL_RenderDrawLines(gWindow->GetRenderer(), points, vertexCount + 1);

    // delete[] points;
}

template<typename T>
void RenderSystem::RequireComponent()
{
	mSignature.set(gCoreHandler->GetComponentType<T>());
}
