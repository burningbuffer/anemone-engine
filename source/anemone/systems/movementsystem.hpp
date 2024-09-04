#pragma once
#include "../core/system.hpp"
#include "../events/keypressedevent.hpp"
#include "../events/keyreleasedevent.hpp"

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

};

