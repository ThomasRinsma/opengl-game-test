#include "drawable.ih"

void Drawable::setRotation(glm::vec3 const &rotation)
{
	d_rotation = rotation;
	updateModelMat();
}