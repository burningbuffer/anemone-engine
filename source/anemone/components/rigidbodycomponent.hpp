#pragma once
#include <glm/glm.hpp>
#include <box2d/box2d.h>
#include "../utils/check.hpp"

struct RigidBodyComponent
{
	RigidBodyComponent() = default;

	glm::vec2 velocity = glm::vec2{0.0f, 0.0f};
    
	b2BodyId body;
    float density = 1.0f;
    float friction = 0.3f;
    float restitution = 0.1f;
    bool fixedRotation = false;
};