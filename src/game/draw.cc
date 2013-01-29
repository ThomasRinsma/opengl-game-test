#include "game.ih"

void Game::draw()
{
	if (not d_running)
		return;

	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw scene objects
	glm::mat4 viewMat = d_player.viewMatrix();
	for (Object *object : d_objects)
		object->draw(viewMat, d_projMat);

	// Draw HUD elements
	for (Drawable *element : d_screenElements)
		element->draw(glm::mat4(1.0f), d_orthoProjMat);

	// Flip buffer
	d_win.Display();
}
