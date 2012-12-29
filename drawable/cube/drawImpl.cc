#include "cube.ih"

void Cube::drawImpl(glm::mat4 &viewProjMat)
{
	// Update uniform
	glm::mat4 mvpMat = viewProjMat * glm::mat4(1.0f); // TODO: modelMat
	glUniformMatrix4fv(d_shaderProgram->uniforms["mvp"], 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw cube
	glDrawArrays(GL_TRIANGLES, 0, 36);
}