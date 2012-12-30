#include "game.ih"

void Game::run()
{
	// Make sure we're initialized
	if (not d_initialized)
		return;

	d_running = true;

	// Initialize graphics
	initGraphics();

	// Initialize game logic
	initGame();

	// The run-loop
	while (d_running)
	{
		handleEvents();
		stepGame();
		draw();
	}
}
