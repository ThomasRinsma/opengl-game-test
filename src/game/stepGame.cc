#include "game.ih"

void Game::stepGame()
{
	if (not d_running)
		return;

	float deltaTime = d_win.GetFrameTime();

	d_player.update(deltaTime);

	ostringstream oss;
	oss << "FPS: " << d_fps;
	d_fpsText->setText(oss.str());
}
