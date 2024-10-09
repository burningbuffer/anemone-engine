#pragma once

#include <GLFW/glfw3.h> // Replace SDL with GLFW
#include "../eventhandler/event.hpp"
#include "../utils/common.hpp"

class KeyPressedEvent : public Event 
{
public:
    // Constructor now takes a GLFW key code instead of SDL_Keycode
    KeyPressedEvent(int key)
    {
        this->key = key;
    }

    int key;  // Use int to store GLFW key codes
};