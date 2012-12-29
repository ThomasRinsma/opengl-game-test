#include "game.ih"

void Game::handleEvents()
{
	if (not d_running)
		return;

	sf::Event event;
	while (d_win->GetEvent(event))
	{
		switch (event.Type)
		{
			case sf::Event::Closed:
				d_win->Close();
				d_running = false;
				break;

			default:
				break;
		}
	}
}
