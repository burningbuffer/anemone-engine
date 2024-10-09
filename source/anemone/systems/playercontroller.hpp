#pragma once
#include "../events/keypressedevent.hpp"
#include "../events/keyreleasedevent.hpp"
#include "../utils/common.hpp"
#include <box2d/box2d.h>

class PlayerController
{
public:

    PlayerController(Entity entity, float speed);
    ~PlayerController();

    void Subscribe();

    void OnKeyPressed(KeyPressedEvent& e);
	void OnKeyReleased(KeyReleasedEvent& e);

    void Update(float DeltaTime);

private:

    Entity entity;

    bool move_y_top = false;
	bool move_y_down = false;

	bool move_x_left = false;
	bool move_x_right = false;

    float speed;

};
