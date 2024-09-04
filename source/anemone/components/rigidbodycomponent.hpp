#pragma once
#include <glm/glm.hpp>

struct RigidBodyComponent
{
	RigidBodyComponent(glm::vec2 velocity = glm::vec2(0.0, 0.0))
	{
		this->velocity = velocity;
	}

	glm::vec2 velocity;
};