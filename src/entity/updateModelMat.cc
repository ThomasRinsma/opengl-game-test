#include "entity.ih"

void Entity::updateModelMat()
{
	d_modelMat = glm::scale(glm::translate(glm::mat4(1.0f), d_position) * glm::mat4_cast(d_orientation), d_scale);
}