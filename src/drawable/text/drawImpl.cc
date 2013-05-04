#include "text.ih"

float colors[8][3] = 
{
	{0.0f, 0.0f, 0.0f}, // black
	{1.0f, 0.0f, 0.0f}, // red
	{0.0f, 1.0f, 0.0f}, // green
	{1.0f, 1.0f, 0.0f}, // yellow
	{0.0f, 0.0f, 1.0f}, // blue
	{0.0f, 1.0f, 1.0f}, // cyan
	{1.0f, 0.0f, 1.0f}, // magenta
	{1.0f, 1.0f, 1.0f}, // white
};

void Text::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();

	// Draw letters
	d_texture.bind();
	glBindVertexArray(d_vao);

	// Initialize color to white (code 7)
	size_t colorCode = 7; // white
	glUniform3f(d_shaderProgram.uniform("color"), colors[colorCode][0], colors[colorCode][1], colors[colorCode][2]);

	glm::mat4 localMat = glm::mat4(1.0f);
	glm::mat4 mvpMat = projMat * viewMat * d_modelMat;
	for (size_t idx = 0, lineLen = 0; idx != d_text.length(); ++idx)
	{
		// special stuff on newline, don't actually draw it
		if (d_text[idx] == '\n')
		{
			localMat = glm::translate(localMat, glm::vec3(lineLen * -1.0f, -1.0f, 0.0f));
			lineLen = 0;
			continue;
		}

		// catch any color codes (quake-style)
		// ignore when we're just before the end of the string
		// or when the next character is not 0-8
		if (d_text[idx] == '^' and idx + 1 < d_text.length() and d_text[idx + 1] >= '0' and d_text[idx + 1] <= '7')
		{
			colorCode = d_text[idx + 1] - '0';
			glUniform3f(d_shaderProgram.uniform("color"), colors[colorCode][0], colors[colorCode][1], colors[colorCode][2]);

			++idx; // also skip the next char (the number)
			continue;
		}

		// Update mvp uniform
		glm::mat4 mvplMat = mvpMat * localMat;
		glUniformMatrix4fv(d_shaderProgram.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvplMat));

		glUniform1i(d_shaderProgram.uniform("c"), d_text[idx]);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		// Move next char to the right
		localMat = glm::translate(localMat, glm::vec3(1.0f, 0.0f, 0.0f));
		++lineLen;
	}
}