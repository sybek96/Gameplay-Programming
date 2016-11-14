#include "Game.h"
#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 

int main(void)
{
	ContextSettings settings;
	settings.depthBits = 24u;
	settings.stencilBits = 8u;
	settings.antialiasingLevel = 32u;
	settings.majorVersion = 3u;
	settings.minorVersion = 0u;
	Game& game = Game(settings);
	game.run();
}