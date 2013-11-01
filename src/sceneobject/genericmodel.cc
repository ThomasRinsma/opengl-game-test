#include <GL/glew.h>
#include <SFML/Graphics.hpp> // for sf::Image
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include "../resourcemanager.h"
#include "genericmodel.h"

using namespace std;

string const requiredShader = "simpleTexture";

GenericModel::GenericModel(string const &texName, string const &modelName)
:
	SceneObject(ResourceManager::instance().shaderProgram(requiredShader)),
	d_model(ResourceManager::instance().model(modelName)),
	d_texture(ResourceManager::instance().texture(texName))
{
	d_model.initAttributes(d_shaderProgram);
}

GenericModel::~GenericModel()
{}

void GenericModel::updateImpl(float deltaTime)
{}

void GenericModel::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();
	
	glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(d_modelMat)));

	// Update uniforms
	glUniformMatrix4fv(d_shaderProgram.uniform("m"), 1, GL_FALSE, glm::value_ptr(d_modelMat));
	glUniformMatrix3fv(d_shaderProgram.uniform("n"), 1, GL_FALSE, glm::value_ptr(normalMat));
	glUniformMatrix4fv(d_shaderProgram.uniform("v"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(d_shaderProgram.uniform("p"), 1, GL_FALSE, glm::value_ptr(projMat));

	// Draw the model
	d_texture.bind();
	d_model.draw();
}
