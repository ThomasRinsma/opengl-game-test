#include "drawable.ih"

void Drawable::draw(glm::mat4 viewMat, glm::mat4 projMat)
{
	drawImpl(viewMat, projMat);
}