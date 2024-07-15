#pragma once
#include <string>
#include <memory>
#include "../core/system.hpp"
#include "../components/transformcomponent.hpp"
#include "../components/rigidbodycomponent.hpp"
#include "../components/boxcollidercomponent.hpp"
#include "../core/corehandler.hpp"
#include "../logger/logger.hpp"

class CollisionSystem : public System
{
public:

	CollisionSystem();
	~CollisionSystem();

	template<typename T> void RequireComponent();

	void Update(float DeltaTime);

	bool CheckAABBCollision(double aX, double aY, double aW, double aH, double bX, double bY, double bW, double bH);
	
private:


};

