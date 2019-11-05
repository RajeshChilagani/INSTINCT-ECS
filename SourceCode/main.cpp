/*This is the starting point of game.An object of Game class is created which has all the game logic*/
#include "game.h"
Game *game = nullptr;
int main(int argc, char *argv[])
{
	const int FPS = 60;
	const int frameDelay = 1000 / FPS;
	Uint32 frameStart;
	int frameTime;
	game = new Game();
	game->init("Instinct",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,1280,720,true); 
	while (game->runing())
	{
		frameStart = SDL_GetTicks();
		game->handleEvents();
		game->update();
		game->render();
		frameTime = SDL_GetTicks() - frameStart;
		if (frameDelay > frameTime)
		{
			SDL_Delay(frameDelay-frameTime);
		}
		
	}
	game->clean();
	return 0;
}
