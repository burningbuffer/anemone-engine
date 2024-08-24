#pragma once
#include "../core/system.hpp"
#include "../eventhandler/eventhandler.hpp"
#include "../events/collisionevent.hpp"


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

