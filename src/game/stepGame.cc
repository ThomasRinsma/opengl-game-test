#include "game.ih"

void Game::stepGame()
{
	float deltaTime = d_timer.restart().asSeconds();

	d_player.update(deltaTime);
	d_scene.update(deltaTime);
	d_gui.update(deltaTime);

	d_gui.get<DebugText>("debugText").setFPS(d_fps);
}
