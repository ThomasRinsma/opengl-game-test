#include "game.ih"

void Game::run()
{
	d_running = true;

	sf::Clock sfmlclock;
	float curSec = 2.0f, lastSec = 0.0f;
	size_t frames = 0;

	// The run-loop
	while (d_running)
	{
		// TODO: replace ifs with exceptions
		handleEvents();

		if (d_running)
			stepGame();

		if (d_running)
			draw();


		curSec = sfmlclock.getElapsedTime().asSeconds();
		if (curSec - lastSec >= 1.0f)
		{
			lastSec = curSec;
			d_fps = frames;
			frames = 0;
		}

		++frames;
	}
}
