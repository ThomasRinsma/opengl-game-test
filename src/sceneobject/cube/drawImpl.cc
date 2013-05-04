#include "cube.ih"

void Cube::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();

	glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(d_modelMat)));
	
	// Update uniforms
	glUniformMatrix4fv(d_shaderProgram.uniform("m"), 1, GL_FALSE, glm::value_ptr(d_modelMat));
	glUniformMatrix3fv(d_shaderProgram.uniform("n"), 1, GL_FALSE, glm::value_ptr(normalMat));
	glUniformMatrix4fv(d_shaderProgram.uniform("v"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(d_shaderProgram.uniform("p"), 1, GL_FALSE, glm::value_ptr(projMat));

	// Draw cube
	d_texture.bind(); //glBindTexture(GL_TEXTURE_2D, d_tex);
	glBindVertexArray(d_vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}