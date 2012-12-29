#include "drawable.ih"

Drawable::Drawable(glm::vec3 position, ShaderProgram *shaderProgram)
:
	d_position(position),
	d_shaderProgram(shaderProgram)
{}