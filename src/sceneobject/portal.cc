#include <GL/glew.h>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_access.hpp>
#include <iostream>
#include "../resourcemanager.h"
#include "portal.h"

using namespace std;

string const requiredShader = "simpleColor";

Portal::Portal(Entity *destination)
:
	SceneObject(ResourceManager::instance().shaderProgram(requiredShader)),
	d_destination(destination)
{
	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	// Portal vertices:   X, Y, Z
	float vertices[] = {
		-0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		 0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		 0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		-0.5f,  0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
		-0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 0.0f,
	};

	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	

	// Link array buffer to "position" attribute
	GLint posAttrib = d_shaderProgram.attribute("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);


	// Link array buffer to "color" attribute
	GLint colAttrib = d_shaderProgram.attribute("color");
	glEnableVertexAttribArray(colAttrib);
	glVertexAttribPointer(colAttrib, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)(3 * sizeof(float)));
}

Portal::~Portal()
{}

void Portal::updateImpl(float deltaTime)
{}

void Portal::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();
	
	// Update uniform
	glm::mat4 mvpMat = projMat * viewMat * d_modelMat;
	glUniform1f(d_shaderProgram.uniform("trans"), 1.0f);
	glUniformMatrix4fv(d_shaderProgram.uniform("mvp"), 1, GL_FALSE, glm::value_ptr(mvpMat));

	// Draw portal
	glBindVertexArray(d_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
}


// Lengyel, Eric. "Oblique View Frustum Depth Projection and Clipping".
// Journal of Game Development, Vol. 1, No. 2 (2005)
// http://www.terathon.com/code/oblique.html

glm::mat4 const Portal::clippedProjMat(glm::mat4 const &viewMat, glm::mat4 const &projMat) const
{
	float dist = glm::length(d_position);
	glm::vec4 clipPlane(d_orientation * glm::vec3(0.0f, 0.0f, -1.0f), dist);
	clipPlane = glm::inverse(glm::transpose(viewMat)) * clipPlane;

	if (clipPlane.w > 0.0f)
		return projMat;

	glm::vec4 q = glm::inverse(projMat) * glm::vec4(
		glm::sign(clipPlane.x),
		glm::sign(clipPlane.y),
		1.0f,
		1.0f
	);

	glm::vec4 c = clipPlane * (2.0f / (glm::dot(clipPlane, q)));

	glm::mat4 newProj = projMat;
	// third row = clip plane - fourth row
	newProj = glm::row(newProj, 2, c - glm::row(newProj, 3));

	return newProj;
} 