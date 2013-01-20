#include "game.ih"

void Game::setProjMat(float fov, float near, float far)
{
	d_projMat = glm::perspective(
		fov,
		static_cast<float>(d_win.GetWidth()) /
		static_cast<float>(d_win.GetHeight()),  // Ratio
		near, far
	);
}