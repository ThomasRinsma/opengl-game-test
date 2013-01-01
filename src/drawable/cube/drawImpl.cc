#include "cube.ih"

void Cube::drawImpl(glm::mat4 &viewProjMat)
{
	d_shaderProgram->use();
	
	// Update uniform
	glm::mat4 mvpMat = viewProjMat * glm::translate(glm::mat4(1.0f), d_position); // TODO: store modelmat instead of position
	glUniformMatrix4fv(d_shaderProgram->uniforms["mvp"], 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw cube
	glBindVertexArray(d_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}