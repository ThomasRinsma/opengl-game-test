#include "drawable.ih"

void Drawable::draw(glm::mat4 const &modelMat, glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	drawImpl(modelMat, viewMat, projMat);
}