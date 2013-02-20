#include "entity.ih"

glm::mat4 const Entity::modelMat() const
{
	glm::mat4 modelMat(1.0f);
	modelMat = glm::scale(glm::mat4_cast(d_orientation) * glm::translate(modelMat, d_position), d_scale);

	return modelMat;
}