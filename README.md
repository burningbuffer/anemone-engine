# anemone-engine
Building a 2D Game Engine with OpenGL and Entity Component System

## Features

- Entity Component System
- Box2d Physics
- Event system
- Small OpenGL Render system

###  TODO
- Tilemaps
- Shader 2d lighting
- Animation system
- Layer and level loader

### ECS Usage example

 Create a CoreHandler for ecs management

#### Create a component
~~~{.cpp}
gCoreHandler->CreateComponent<TransformComponent>();
gCoreHandler->CreateComponent<SpriteComponent>();
~~~

#### Create systems
~~~{.cpp}
auto movementSystem = gCoreHandler->CreateSystem<MovementSystem>();
auto renderSystem = gCoreHandler->CreateSystem<RenderSystem>();
~~~

#### Create Entity
~~~{.cpp}
Entity tank = gCoreHandler->CreateEntity();
gCoreHandler->AddComponent(tank, TransformComponent{glm::vec2{230, 270}});
gCoreHandler->AddComponent(tank, RigidBodyComponent{});
~~~



