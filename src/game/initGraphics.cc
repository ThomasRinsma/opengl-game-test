#include "game.ih"

void Game::initGraphics()
{
	d_shaderPrograms.push_back(new ShaderProgram("simpleColor", {"mvp"}));
	d_shaderPrograms.push_back(new ShaderProgram("simpleTexture", {"m", "v", "p", "n"}));
	
	d_projMat = glm::perspective(
		45.0f,	// 45 degree FOV
		static_cast<float>(d_win->GetWidth()) /
		static_cast<float>(d_win->GetHeight()),  // Ratio
		0.1f, 100.0f // near/far
	);
}