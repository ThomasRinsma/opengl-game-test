#include "model.ih"

void Model::initAttributes(ShaderProgram &shaderProgram)
{
	for (WavefrontObject &wo : d_objects)
	{
		glBindVertexArray(wo.vao);
		glBindBuffer(GL_ARRAY_BUFFER, wo.vbo);

		// Link array buffer to "position" attribute
		GLint posAttrib = shaderProgram.attribute("position");
		glEnableVertexAttribArray(posAttrib);
		glVertexAttribPointer(posAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), 0);

		GLint normAttrib = shaderProgram.attribute("normal");
		glEnableVertexAttribArray(normAttrib);
		glVertexAttribPointer(normAttrib, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(3 * sizeof(float)));

		// Link array buffer to "texcoord" attribute
		GLint texAttrib = shaderProgram.attribute("texcoord");
		glEnableVertexAttribArray(texAttrib);
		glVertexAttribPointer(texAttrib, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *)(6 * sizeof(float)));
	}
}