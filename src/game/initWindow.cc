#include "game.ih"

void Game::initWindow()
{
	// Set glew to use modern OpenGL
	glewExperimental = GL_TRUE;

	// Initialize glew
	glewInit();

	// Set VSync
	d_win.UseVerticalSync(d_vsync);

	// Set up ortho matrix, TODO: somewhere else?
	d_orthoProjMat = glm::ortho(0.0f, (float)d_winWidth, 0.0f, (float)d_winHeight, -1.0f, 1.0f);
}