#include "drawable.ih"

void Drawable::setPosition(glm::vec3 const &position)
{
	d_position = position;
	updateModelMat();
}