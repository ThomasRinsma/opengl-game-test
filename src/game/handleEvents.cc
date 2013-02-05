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
				d_running = false; // TODO: replace with exception
				break;

			case sf::Event::KeyPressed:
				switch (event.Key.Code)
				{
					case sf::Key::Escape:
						d_win.Close();
						d_running = false; // TODO: replace with exception
						break;

					case sf::Key::F1:
						d_vsync = not d_vsync;
						d_win.UseVerticalSync(d_vsync);
						break;

					default:
						break;
				}
				break;

			case sf::Event::MouseWheelMoved:
				d_fov -= event.MouseWheel.Delta * 5.0f;
				if (d_fov > 175) d_fov = 175;
				if (d_fov < 5) d_fov = 5;
				d_player.setProjMat(d_fov,
					static_cast<float>(d_win.GetWidth()) /
					static_cast<float>(d_win.GetHeight()),
					0.1f, 100.0f);
				break;

			default:
				break;
		}
	}
}
