#pragma once
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include "./collidercomponent.hpp"

struct BoxColliderComponent : ColliderComponent
{
	BoxColliderComponent(const glm::vec2& size = glm::vec2(32.0f, 32.0f), const glm::vec2& offset = glm::vec2(0.0f)) : size(size), offset(offset) {}

	b2Polygon boxCollider;
	b2ShapeDef shapeDef;

	glm::vec2 size;
    glm::vec2 offset;
};