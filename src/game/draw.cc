#include "game.ih"

void Game::draw()
{
	if (not d_running)
		return;

	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw everything
	glm::mat4 viewMat = d_player.viewMatrix();

	for (Drawable *drawable : d_drawables)
		drawable->draw(viewMat, d_projMat);

	// Flip buffer
	d_win.Display();
}
