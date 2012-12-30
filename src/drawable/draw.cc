#include "drawable.ih"

void Drawable::draw(glm::mat4 &viewProjMat)
{
	drawImpl(viewProjMat);
}