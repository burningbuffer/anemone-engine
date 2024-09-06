#pragma once

#include "../core/system.hpp"
#include "../eventhandler/eventhandler.hpp"
#include "../core/corehandler.hpp"
#include "../components/components.hpp"
#include <SDL2/SDL.h>

class DebugRenderingSystem : public System
{
public:

	DebugRenderingSystem();
	~DebugRenderingSystem();

	template<typename T> void RequireComponent();

    void Subscribe();

	void Update(float DeltaTime);

    void Render();

	
private:


};

