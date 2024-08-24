#pragma once
#include "../core/system.hpp"

class MovementSystem : public System
{
public:

	MovementSystem();
	~MovementSystem();

	template<typename T> void RequireComponent();

	void Update(float DeltaTime);
	
private:


};

