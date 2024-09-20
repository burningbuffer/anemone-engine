#pragma once
#include <glm/glm.hpp>

struct TransformComponent
{
	TransformComponent(glm::vec2 Position)
	{
		this->Position = Position;
	}

	TransformComponent() = default;

	glm::vec2 Position;
	glm::vec2 Scale;
	double Rotation;
};