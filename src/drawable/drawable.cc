#include "drawable.ih"

Drawable::Drawable(ShaderProgram *shaderProgram)
:
	d_position(glm::vec3(0.0f)),
	d_rotation(glm::vec3(0.0f)),
	d_scale(glm::vec3(1.0f)),
	d_shaderProgram(shaderProgram)
{
	// initialize model (and normal) matrix
	updateModelMat();
}