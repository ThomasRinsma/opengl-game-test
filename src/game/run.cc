#include "game.ih"

void Game::run()
{
	d_running = true;

	// The run-loop
	while (d_running)
	{
		handleEvents();
		stepGame();
		draw();
	}
}
