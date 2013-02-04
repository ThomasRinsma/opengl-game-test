#include "game.ih"

void Game::draw()
{
	if (not d_running)
		return;

	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::mat4 viewMat = d_player.viewMatrix();

	// Testing stuff
	glm::mat4 p2view = viewMat * d_portal1->modelMat()
		* glm::rotate(glm::mat4(1.0f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f))
		* glm::inverse(d_portal2->modelMat());


	// Draw portal into the stencil buffer
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_FALSE);
	glStencilFunc(GL_NEVER, 0, 0xFF);
	glStencilOp(GL_INCR, GL_KEEP, GL_KEEP);
	glClear(GL_STENCIL_BUFFER_BIT);
	d_portal1->draw(viewMat, d_projMat);


	// Draw scene objects with p2view, limited to stencil buffer
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	for (Object *object : d_objects)
		object->draw(p2view, d_projMat);


	// Draw portal into depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_TRUE);
	d_portal1->draw(viewMat, d_projMat);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);





	// Draw scene objects
	for (Object *object : d_objects)
		object->draw(viewMat, d_projMat);




	// Draw HUD elements
	for (Drawable *element : d_screenElements)
		element->draw(glm::mat4(1.0f), d_orthoProjMat);

	// Flip buffer
	d_win.Display();
}
