#include "text.ih"

void Text::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram->use();

	// Draw letters
	glBindTexture(GL_TEXTURE_2D, d_tex);
	glBindVertexArray(d_vao);

	glm::mat4 localMat = glm::mat4(1.0f);

	for(size_t idx = 0; idx != d_text.length(); ++idx)
	{
		// Update mvp uniform
		glm::mat4 mvpMat = projMat * viewMat * d_modelMat * localMat;
		glUniformMatrix4fv(d_shaderProgram->uniforms["mvp"], 1, GL_FALSE, glm::value_ptr(mvpMat));

		glUniform1i(d_shaderProgram->uniforms["c"], d_text[idx]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Move next char to the right
		localMat = glm::translate(localMat, glm::vec3(0.2f, 0.0f, 0.0f));
	}

}