#include "game.ih"

void Game::handleEvents()
{
	if (not d_running)
		return;

	Event event;
	while (d_win->GetEvent(event))
	{
		switch (event.Type)
		{
			case Event::Closed:
				d_win->Close();
				d_running = false;
				break;

			default:
				break;
		}
	}
}
