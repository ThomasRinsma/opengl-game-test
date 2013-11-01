#include <GL/glew.h>
#include <SFML/Graphics.hpp> // for sf::Image
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <vector>
#include "../resourcemanager.h"
#include "grid.h"

using namespace std;

string const requiredShader = "simpleColor";

Grid::Grid()
:
	SceneObject(ResourceManager::instance().shaderProgram(requiredShader))
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	// TODO: color

	vector<float> vertVec;
	for (int x = -10; x <= 10; ++x)
	{
		vertVec.insert(vertVec.end(), {(float)x, 0.0f, -10.0f, 1.0f, 0.0f, 0.0f});
		vertVec.insert(vertVec.end(), {(float)x, 0.0f,  10.0f, 1.0f, 0.0f, 0.0f});
	}

	for (int z = -10; z <= 10; ++z)
	{
		vertVec.insert(vertVec.end(), {-10.0f, 0.0f, (float)z, 1.0f, 0.0f, 0.0f});
		vertVec.insert(vertVec.end(), { 10.0f, 0.0f, (float)z, 1.0f, 0.0f, 0.0f});
	}


	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, vertVec.size() * sizeof(float), vertVec.data(), GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram.attribute("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);

	// Link array buffer to "color" attribute
	GLint colAttrib = d_shaderProgram.attribute("color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
}

Grid::~Grid()
{
	glDeleteBuffers(1, &d_vbo);
	glDeleteVertexArrays(1, &d_vao);
}

void Grid::updateImpl(float deltaTime)
{}

void Grid::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();
	
	// Update uniform
	glm::mat4 mvpMat = projMat * viewMat * d_modelMat;
	glUniform1f(d_shaderProgram.uniform("trans"), 1.0f);
	glUniformMatrix4fv(d_shaderProgram.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw grid
	glBindVertexArray(d_vao);
	glDrawArrays(GL_LINES, 0, 84);
}