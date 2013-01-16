#include "cube.ih"

void Cube::drawImpl(glm::mat4 &viewMat, glm::mat4 &projMat)
{
	d_shaderProgram->use();
	
	// Update uniform
	glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), d_position); // TODO: store modelmat instead of position
	glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(modelMat)));
	
	glUniformMatrix4fv(d_shaderProgram->uniforms["m"], 1, GL_FALSE, glm::value_ptr(modelMat));
	glUniformMatrix4fv(d_shaderProgram->uniforms["v"], 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(d_shaderProgram->uniforms["p"], 1, GL_FALSE, glm::value_ptr(projMat));
	glUniformMatrix3fv(d_shaderProgram->uniforms["n"], 1, GL_FALSE, glm::value_ptr(normalMat));

	// Draw cube
	glBindVertexArray(d_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}