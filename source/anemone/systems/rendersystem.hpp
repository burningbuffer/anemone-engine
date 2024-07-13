#pragma once
#include <string>
#include <memory>
#include "../core/system.hpp"
#include "../core/corehandler.hpp"
#include "../logger/logger.hpp"

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