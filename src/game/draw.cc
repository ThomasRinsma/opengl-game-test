#include "game.ih"

void Game::draw()
{
	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Draw scene
	d_scene.draw(d_player);

	// Draw GUI/HUD
	d_gui.draw();

	// Flip buffer
	d_win.display();
}
