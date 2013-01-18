#include "drawable.ih"

void Drawable::setScale(glm::vec3 const &scale)
{
	d_scale = scale;
	updateModelMat();
}