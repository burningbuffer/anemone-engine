#include <SDL2/SDL.h>
#include "game.hpp"

int main(int argc, char* argv[])
{
    Game game;
    game.Initialize();
    game.Run();
    game.Destroy();
	
    return 0;
}
 