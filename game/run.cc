#include "game.ih"

void Game::run()
{
	// Make sure we're initialized
	if (not d_initialized)
		return;

	d_running = true;

	// Initialize game logic
	initGame();

	// Initialize graphics
	initGraphics();

	// The run-loop
	while (d_running)
	{
		handleEvents();
		stepGame();
		draw();
	}
}
