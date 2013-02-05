#include "grid.ih"

void Grid::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();
	
	// Update uniform
	glm::mat4 mvpMat = projMat * viewMat * d_modelMat;
	glUniformMatrix4fv(d_shaderProgram.uniforms["mvp"], 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw grid
	glBindVertexArray(d_vao);
	glDrawArrays(GL_LINES, 0, 84);
}