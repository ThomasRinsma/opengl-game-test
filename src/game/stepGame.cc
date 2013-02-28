#include "game.ih"

void Game::stepGame()
{
	float deltaTime = d_timer.restart().asSeconds();

	d_player.update(deltaTime);
	d_scene.update(deltaTime);
	d_gui.update(deltaTime);

	
	ostringstream oss;
	oss << "FPS: " << d_fps << "\n\n"
		<< "X: " << d_player.position().x << '\n'
		<< "Y: " << d_player.position().y << '\n'
		<< "Z: " << d_player.position().z << '\n';

	dynamic_cast<Text *>(d_gui.get("debugText"))->setText(oss.str());
}
