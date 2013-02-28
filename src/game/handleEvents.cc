#include "game.ih"

void Game::handleEvents()
{
	sf::Event event;
	while (d_win.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				throw true;
				break;

			case sf::Event::LostFocus:
				pause();
				break;

			case sf::Event::GainedFocus:
				if (d_fullscreen)
					unpause();
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						if (d_fullscreen)
							throw true;
						else
							pause();
						break;

					case sf::Keyboard::F1:
						d_vsync = not d_vsync;
						d_win.setVerticalSyncEnabled(d_vsync);
						break;

					default:
						break;
				}
				break;

			case sf::Event::MouseButtonPressed:
				if (d_paused)
					unpause();
				break;

			case sf::Event::MouseWheelMoved:
				d_player.setFov(d_player.fov() - event.mouseWheel.delta * 5.0f);
				if (d_player.fov() > 175)
					d_player.setFov(175);
				
				if (d_player.fov() < 5)
					d_player.setFov(5);
				
				break;

			default:
				break;
		}
	}
}
