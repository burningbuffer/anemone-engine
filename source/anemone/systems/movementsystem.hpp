#pragma once
#include "../core/system.hpp"
#include "../events/keypressedevent.hpp"
#include "../events/keyreleasedevent.hpp"
#include <box2d/box2d.h>

class MovementSystem : public System
{
public:

	MovementSystem();
	~MovementSystem();

	template<typename T> void RequireComponent();

	void Subscribe();

	void OnKeyPressed(KeyPressedEvent& event);
	void OnKeyReleased(KeyReleasedEvent& event);

	void Update(float DeltaTime);
	
private:

	bool move_y_top = false;
	bool move_y_down = false;

	bool move_x_left = false;
	bool move_x_right = false;

	float speed = 90;
	float force = 150000;

	b2Rot rot{0.0f, 0.0f};

};

