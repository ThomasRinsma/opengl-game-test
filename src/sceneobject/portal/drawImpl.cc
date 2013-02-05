#include "portal.ih"

void Portal::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();
	
	// Update uniform
	glm::mat4 mvpMat = projMat * viewMat * d_modelMat;
	glUniformMatrix4fv(d_shaderProgram.uniforms["mvp"], 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw portal
	glBindVertexArray(d_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}