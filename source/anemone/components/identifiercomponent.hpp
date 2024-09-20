#pragma once
#include <string>

struct IdentifierComponent
{
	IdentifierComponent(std::string name)
	{
		this->name = name;
	}

	IdentifierComponent() = default;

    std::string name;
    
};