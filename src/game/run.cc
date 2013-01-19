#include "game.ih"

void Game::run()
{
	d_running = true;

	// The run-loop
	while (d_running)
	{
		// TODO: replace ifs with exceptions
		handleEvents();

		if (d_running)
			stepGame();

		if (d_running)
			draw();
	}
}
