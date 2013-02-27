#include "game.ih"

void Game::handleEvents()
{
	if (not d_running)
		return;

	sf::Event event;
	while (d_win.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				d_win.close();
				d_running = false; // TODO: replace with exception
				break;

			case sf::Event::LostFocus:
				d_running = false;
				break;

			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Escape:
						d_win.close();
						d_running = false; // TODO: replace with exception
						break;

					case sf::Keyboard::F1:
						d_vsync = not d_vsync;
						d_win.setVerticalSyncEnabled(d_vsync);
						break;

					default:
						break;
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
