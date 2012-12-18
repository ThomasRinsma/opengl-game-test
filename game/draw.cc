#include "game.ih"

void Game::draw()
{
	if (not d_running)
		return;

	// Clear screen
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


	// Rotate model matrix around Y axis
	//mat4 ident;
	//d_modelMat = rotate(ident, d_clock.GetElapsedTime() * 45.0f,
	//	vec3(1.0f, 1.0f, 1.0f));
	
	// Update uniforms
	glUniformMatrix4fv(d_modelMatRef, 1, GL_FALSE, value_ptr(d_modelMat));
	glUniformMatrix4fv(d_viewMatRef, 1, GL_FALSE, value_ptr(d_viewMat));
	glUniformMatrix4fv(d_projMatRef, 1, GL_FALSE, value_ptr(d_projMat));

	// Draw triangle
	glDrawArrays(GL_TRIANGLES, 0, 36);

	// Flip buffer
	d_win->Display();
}
