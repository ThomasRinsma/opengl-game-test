#include "game.ih"

void Game::initGraphics()
{
	d_shaderPrograms.push_back(new ShaderProgram("simpleColor", {"mvp"}));
	d_shaderPrograms.push_back(new ShaderProgram("simpleTexture", {"m", "v", "p", "n"}));
	d_shaderPrograms.push_back(new ShaderProgram("simpleText", {"mvp", "c"}));

	d_player.setFov(45.0f);
	d_player.setScreenRatio(static_cast<float>(d_win.getSize().x) /
			static_cast<float>(d_win.getSize().y));
	d_player.setZnear(0.1f);
	d_player.setZfar(100.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// wireframe mode, because why not
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}