#include "game.ih"

void Game::handleEvents()
{
	sf::Event event;
	while (d_win.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				throw false; // no error, exit cleanly
				break;

			case sf::Event::LostFocus:
				d_paused = true;
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						if (d_fullscreen)
							throw false;
						else
						{
							d_paused = true;
							d_win.setMouseCursorVisible(true);
						}
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
				{
					d_paused = false;
					d_win.setMouseCursorVisible(false);
				}
				break;

			case sf::Event::MouseWheelMoved:
				d_fov -= event.mouseWheel.delta * 5.0f;
				if (d_fov > 175) d_fov = 175;
				if (d_fov < 5) d_fov = 5;
				d_player.setProjMat(d_fov,
					static_cast<float>(d_win.getSize().x) /
					static_cast<float>(d_win.getSize().y),
					0.1f, 100.0f);
				break;

			default:
				break;
		}
	}
}
