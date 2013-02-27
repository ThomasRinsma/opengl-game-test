#include "text.ih"

void Text::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();

	// Draw letters
	glBindTexture(GL_TEXTURE_2D, d_tex);
	glBindVertexArray(d_vao);

	glm::mat4 localMat = glm::mat4(1.0f);

	glm::mat4 mvpMat = projMat * viewMat * d_modelMat;
	for(size_t idx = 0, lineLen = 0; idx != d_text.length(); ++idx)
	{
		// special stuff on newline, don't actually draw it
		if (d_text[idx] == '\n')
		{
			localMat = glm::translate(localMat, glm::vec3(lineLen * -1.0f, -1.0f, 0.0f));
			lineLen = 0;
			continue;
		}

		// Update mvp uniform
		glm::mat4 mvplMat = mvpMat * localMat;
		glUniformMatrix4fv(d_shaderProgram.uniforms["mvp"], 1, GL_FALSE, glm::value_ptr(mvplMat));

		glUniform1i(d_shaderProgram.uniforms["c"], d_text[idx]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Move next char to the right
		localMat = glm::translate(localMat, glm::vec3(1.0f, 0.0f, 0.0f));
		++lineLen;
	}
}