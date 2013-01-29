#include "object.ih"

void Object::draw(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	Drawable::draw(modelMat(), viewMat, projMat);
}