#pragma once

#include <SDL2/SDL.h>
#include "../eventhandler/event.hpp"
#include "../utils/common.hpp"

class KeyReleasedEvent : public Event 
{
public:
    KeyReleasedEvent(SDL_Keycode key)
    {
        this->key = key;
    }

    SDL_Keycode  key;
};