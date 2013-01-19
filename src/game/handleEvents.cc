#include "game.ih"

void Game::handleEvents()
{
	if (not d_running)
		return;

	sf::Event event;
	while (d_win.GetEvent(event))
	{
		switch (event.Type)
		{
			case sf::Event::Closed:
				d_win.Close();
				d_running = false; // TODO: exit cleanly
				break;

			case sf::Event::KeyPressed:
				switch (event.Key.Code)
				{
					case sf::Key::Escape:
						// TODO: exit cleanly
						break;

					default:
						break;
				}

			default:
				break;
		}
	}
}
