#include "console.ih"

void Console::drawBackground(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();
	
	// Update uniform
	glm::mat4 mvpMat = projMat * viewMat * glm::translate(d_modelMat, glm::vec3(0.0f, -1.0f, 0.0f));
	glUniform1f(d_shaderProgram.uniform("trans"), 0.75f);
	glUniformMatrix4fv(d_shaderProgram.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw console background
	glBindVertexArray(d_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}