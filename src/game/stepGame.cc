#include "game.ih"

void Game::stepGame()
{
	if (not d_running)
		return;

	float deltaTime = d_win.GetFrameTime();

	d_player.update(deltaTime);

}
