# anemone-engine
Building a 2D Game Engine with SDL and ECS

## ECS Usage example

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
gCoreHandler->AddComponent(tank, TransformComponent{ glm::vec2{10, 30}, glm::vec2{2,2},0.0 });
gCoreHandler->AddComponent(tank, SpriteComponent{"image_map_key", 32, 32});
~~~



