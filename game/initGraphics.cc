#include "game.ih"

void Game::initGraphics()
{
	d_shaderProgram = new ShaderProgram("game/shaders/vertex.shader", "game/shaders/fragment.shader", {"mvp"});
	
	d_projMat = glm::perspective(
		45.0f,	// 45 degree FOV
		static_cast<float>(d_win->GetWidth()) /
		static_cast<float>(d_win->GetHeight()),  // Ratio
		0.1f, 100.0f // near/far
	);
}