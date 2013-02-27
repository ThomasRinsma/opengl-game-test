#include "game.ih"

void Game::run()
{
	sf::Clock sfmlclock;
	float curSec = 2.0f, lastSec = 0.0f;
	size_t frames = 0;

	// The run-loop
	try
	{
		while (true)
		{
			handleEvents();

			if (not d_paused)
				stepGame();

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
	catch (bool error)
	{
		if (error)
			cout << "exited with error" << endl;

		d_win.close();
	}
}
