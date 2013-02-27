#include "game.ih"

void Game::initWindow()
{
	// Set glew to use modern OpenGL
	glewExperimental = GL_TRUE;

	// Initialize glew
	glewInit();

	// Set VSync
	d_win.setVerticalSyncEnabled(d_vsync);
}