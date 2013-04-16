#include "genericmodel.ih"

void GenericModel::drawImpl(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	d_shaderProgram.use();
	
	glm::mat3 normalMat = glm::transpose(glm::inverse(glm::mat3(d_modelMat)));

	// Update uniforms
	glUniformMatrix4fv(d_shaderProgram.uniform("m"), 1, GL_FALSE, glm::value_ptr(d_modelMat));
	glUniformMatrix3fv(d_shaderProgram.uniform("n"), 1, GL_FALSE, glm::value_ptr(normalMat));
	glUniformMatrix4fv(d_shaderProgram.uniform("v"), 1, GL_FALSE, glm::value_ptr(viewMat));
	glUniformMatrix4fv(d_shaderProgram.uniform("p"), 1, GL_FALSE, glm::value_ptr(projMat));

	// Draw the model
	d_texture.bind();
	d_model.draw();
}