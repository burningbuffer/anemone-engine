#pragma once
#include <string>
#include <memory>
#include "../core/system.hpp"
#include "../components/transformcomponent.hpp"
#include "../components/rigidbodycomponent.hpp"
#include "../core/corehandler.hpp"
#include "../logger/logger.hpp"

class MovementSystem : public System
{
public:

	MovementSystem();
	~MovementSystem();

	template<typename T> void RequireComponent();

	void Update(float DeltaTime);
	
private:


};

