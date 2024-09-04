#pragma once

#include <SDL2/SDL.h>
#include "../eventhandler/event.hpp"
#include "../utils/common.hpp"

class KeyPressedEvent : public Event 
{
public:
    KeyPressedEvent(SDL_Keycode key)
    {
        this->key = key;
    }

    SDL_Keycode  key;
};