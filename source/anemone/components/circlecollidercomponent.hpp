#pragma once
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include "./collidercomponent.hpp"

struct CircleColliderComponent : ColliderComponent
{
	CircleColliderComponent(float r, const glm::vec2& offset = glm::vec2(0.0f)) : radius(r), offset(offset) {}

	float radius;
    glm::vec2 offset;
};