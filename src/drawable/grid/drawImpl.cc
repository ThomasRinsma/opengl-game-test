#include "grid.ih"

void Grid::drawImpl(glm::mat4 &viewMat, glm::mat4 &projMat)
{
	d_shaderProgram->use();
	
	// Update uniform
	glm::mat4 mvpMat = projMat * viewMat * glm::translate(glm::mat4(1.0f), d_position); // TODO: store modelmat instead of position
	glUniformMatrix4fv(d_shaderProgram->uniforms["mvp"], 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw grid
	glBindVertexArray(d_vao);
	glDrawArrays(GL_LINES, 0, 84);
}