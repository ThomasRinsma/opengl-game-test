#include <GL/glew.h>
#include <SFML/Graphics.hpp> // for sf::Image
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "../resourcemanager.h"
#include "text.h"

using namespace std;

string const fontTexName = "liberationmono";
string const requiredShader = "simpleText";

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

Text::Text(string const &text)
:
	Drawable(ResourceManager::instance().shaderProgram(requiredShader)),
	d_texture(ResourceManager::instance().texture(fontTexName)),
	d_text(text)
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	float vertices[] = {
		 0.0f,  0.0f, 0.0f,   0.0f, 1.0f,
		 1.0f,  0.0f, 0.0f,   1.0f, 1.0f,
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f,
		 1.0f,  1.0f, 0.0f,   1.0f, 0.0f,
		 0.0f,  1.0f, 0.0f,   0.0f, 0.0f,
		 0.0f,  0.0f, 0.0f,   0.0f, 1.0f,
	};


	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram.attribute("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), 0);

	GLint texAttrib = d_shaderProgram.attribute("texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void *)(3 * sizeof(float)));

	d_texture.bind();
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

Text::~Text()
{
	glDeleteBuffers(1, &d_vbo);
	glDeleteVertexArrays(1, &d_vao);
}

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