#include "scene.ih"

void Scene::draw(Player const &player)
{
	
	// Enable stencil test, increment on fail
	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_INCR, GL_KEEP, GL_KEEP);

	for (Portal *portal : d_portals)
	{
		// Disable color and depth drawing
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
		glDepthMask(GL_FALSE);

		// Always fail stencil test (on the portal pixels)
		glStencilFunc(GL_NEVER, 0, 0xFF);

		// Enable all stencil bits
		glStencilMask(0xFF);

		// Draw portal into empty stencil buffer
		glClear(GL_STENCIL_BUFFER_BIT);
		portal->draw(player.viewMat(), player.projMat());
		
		
		// View matrix as if the player was already teleported
		glm::mat4 destView = player.viewMat() * portal->modelMat()
			* glm::rotate(glm::mat4(1.0f), 180.0f, glm::vec3(0.0f, 1.0f, 0.0f))
			* glm::inverse(portal->destination()->modelMat());


		// Enable color and depth drawing
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDepthMask(GL_TRUE);

		// Disable drawing into stencil buffer
		glStencilMask(0x00);

		// Draw only where stencil value >= 1  (so 1 <= stencil value)
		glStencilFunc(GL_LEQUAL, 1, 0xFF);

		// Draw scene objects with destView, limited to stencil buffer
		drawSceneObjects(destView, player.projMat());
		

	}

	// Disable stencil test and reset OP
	glDisable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);

	

	// Draw portals into depth buffer
	glClear(GL_DEPTH_BUFFER_BIT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
	glDepthMask(GL_TRUE);
	for (Portal *portal : d_portals)
		portal->draw(player.viewMat(), player.projMat());


	// Draw scene objects normally
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDepthMask(GL_TRUE);
	drawSceneObjects(player.viewMat(), player.projMat());
	

}