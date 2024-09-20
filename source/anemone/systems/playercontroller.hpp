#pragma once
#include "../events/keypressedevent.hpp"
#include "../events/keyreleasedevent.hpp"
#include "../utils/common.hpp"
#include <box2d/box2d.h>

class PlayerController
{
public:

    PlayerController(Entity entity);
    ~PlayerController();

    void Subscribe();

    void OnKeyPressed(KeyPressedEvent& event);
	void OnKeyReleased(KeyReleasedEvent& event);

    void Update(float DeltaTime);

private:

    Entity entity;

    bool move_y_top = false;
	bool move_y_down = false;

	bool move_x_left = false;
	bool move_x_right = false;

    float speed = 90.0f;

};