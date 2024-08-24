#pragma once
#include <string>
#include <memory>
#include "../core/system.hpp"
#include "../components/transformcomponent.hpp"
#include "../components/rigidbodycomponent.hpp"
#include "../components/boxcollidercomponent.hpp"
#include "../components/spritecomponent.hpp"
#include "../core/corehandler.hpp"
#include "../logger/logger.hpp"
#include "../events/collisionevent.hpp"
#include "../eventhandler/eventhandler.hpp"

class DamageSystem : public System
{
public:

	DamageSystem();
	~DamageSystem();

	template<typename T> void RequireComponent();

    void Subscribe();

	void Update(float DeltaTime);

	void OnCollision(CollisionEvent& event);
	
private:


};

