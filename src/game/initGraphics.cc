#include "game.ih"

void Game::initGraphics()
{
	d_shaderPrograms.push_back(new ShaderProgram("simpleColor", {"mvp"}));
	d_shaderPrograms.push_back(new ShaderProgram("simpleTexture", {"m", "v", "p", "n"}));
	d_shaderPrograms.push_back(new ShaderProgram("simpleText", {"mvp", "c"}));
	
	d_player.setProjMat(d_fov,
			static_cast<float>(d_win.getSize().x) /
			static_cast<float>(d_win.getSize().y),
			0.1f, 100.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// wireframe mode, because why not
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}