#include "entity.ih"

glm::mat4 const Entity::modelMat() const
{
	glm::mat4 modelMat(1.0f);

	modelMat = glm::translate(modelMat, d_position);
	modelMat = glm::rotate(modelMat, d_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	modelMat = glm::rotate(modelMat, d_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	modelMat = glm::rotate(modelMat, d_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	modelMat = glm::scale(modelMat, d_scale);

	return modelMat;
}