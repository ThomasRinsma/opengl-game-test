#include "entity.ih"

glm::mat4 const Entity::modelMat() const
{
	glm::mat4 modelMat(1.0f);
	modelMat = glm::scale(glm::translate(modelMat, d_position) * glm::mat4_cast(d_orientation), d_scale);

	return modelMat;
}