#include "model.ih"

void Model::initAttributes(ShaderProgram &shaderProgram)
{
	glBindVertexArray(d_vao);
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);

	// Link array buffer to "position" attribute
	GLint posAttrib = shaderProgram.attribLocation("position");
	glEnableVertexAttribArray(posAttrib);
	glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

	GLint normAttrib = shaderProgram.attribLocation("normal");
	glEnableVertexAttribArray(normAttrib);
	glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));

	// Link array buffer to "texcoord" attribute
	GLint texAttrib = shaderProgram.attribLocation("texcoord");
	glEnableVertexAttribArray(texAttrib);
	glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
}