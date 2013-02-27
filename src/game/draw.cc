#include "game.ih"

void Game::draw()
{
	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Draw scene
	d_scene.draw(d_player);

	// Draw HUD elements
	for (Drawable *element : d_screenElements)
		element->draw(glm::mat4(1.0f), d_orthoProjMat);

	// Flip buffer
	d_win.display();
}
