#pragma once
#include "../core/system.hpp"

class RenderSystem : public System 
{
public:

    RenderSystem();
    ~RenderSystem();

    template<typename T> void RequireComponent();

	void Update(float DeltaTime);
    void Render();

private:

};