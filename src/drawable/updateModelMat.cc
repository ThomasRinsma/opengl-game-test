#include "drawable.ih"

void Drawable::updateModelMat()
{
	d_modelMat = glm::translate(glm::mat4(1.0f), d_position);
	d_modelMat = glm::rotate(d_modelMat, d_rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
	d_modelMat = glm::rotate(d_modelMat, d_rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
	d_modelMat = glm::rotate(d_modelMat, d_rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
	d_modelMat = glm::scale(d_modelMat, d_scale);

	// update normal matrix as well
	d_normalMat = glm::transpose(glm::inverse(glm::mat3(d_modelMat)));
}