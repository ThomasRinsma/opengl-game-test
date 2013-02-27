#include "game.ih"

void Game::initWindow()
{
	d_win.setPosition(sf::Vector2i(0, 0));
	
	// Set glew to use modern OpenGL
	glewExperimental = GL_TRUE;

	// Initialize glew
	glewInit();

	// Set VSync
	d_win.setVerticalSyncEnabled(d_vsync);

	// Set up ortho matrix, TODO: somewhere else?
	d_orthoProjMat = glm::ortho(0.0f, (float)d_win.getSize().x, 0.0f, (float)d_win.getSize().y, -1.0f, 1.0f);
}