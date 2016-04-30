#include "Game.h"

int main()
{
	System::GetStartUpInfo();	//	Get info about preferable size and flag for window. 

	Game *game = new Game();	//	Create a instance of game object.
	SDL_Event event;

	game->Init("Game Engine");
	while (game->IsRunning())
	{
		System::SetFrames();

			//	Wait for evenets from keyboard and mouse
		while (SDL_PollEvent(&event))
			game->Events(&event);
		
		game->Update();	//	Update things.
		game->Render();	//	Render things

		System::LimitFrames();
	}
	game->~Game();

	return 0;
}