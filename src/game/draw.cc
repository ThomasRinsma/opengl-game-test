#include "game.ih"

void Game::draw()
{
	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	glStencilMask(0xFF);
	glClear(GL_STENCIL_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);

	// Draw scene
	d_scene.draw();

	// Draw GUI/HUD
	d_gui.draw();

	// Flip buffer
	d_win.display();
}
