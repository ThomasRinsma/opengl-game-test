#include "game.ih"

void Game::stepGame()
{
	if (not d_running)
		return;

	float deltaTime = d_timer.restart().asSeconds();

	d_player.update(deltaTime);
	d_scene.update(deltaTime);

	ostringstream oss;
	oss << "FPS: " << d_fps << "\n\n"
		<< "X: " << d_player.position().x << '\n'
		<< "Y: " << d_player.position().y << '\n'
		<< "Z: " << d_player.position().z << '\n';
	d_debugText->setText(oss.str());
}
