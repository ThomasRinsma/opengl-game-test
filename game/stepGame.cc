#include "game.ih"

void Game::stepGame()
{
	if (not d_running)
		return;

	float velZ = d_input.moveBack() ? 1.0f : 0.0f;
	velZ -= d_input.moveForward() ? 1.0f : 0.0f;
	float velX = d_input.moveRight() ? 1.0f : 0.0f;
	velX -= d_input.moveLeft() ? 1.0f : 0.0f;
	float velY = 0.0f;

	d_player.setVelocity(vec3(velX, velY, velZ));
	d_player.integratePosition(d_win->GetFrameTime() * 2.0f);
}
