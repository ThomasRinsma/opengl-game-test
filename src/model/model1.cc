#include "model.ih"

Model::Model(std::string const &path)
{
	loadModel(path);

	for (WavefrontObject &wo : d_objects)
	{
		// Create a VAO
		glGenVertexArrays(1, &wo.vao);
		glBindVertexArray(wo.vao);

		// Create a VBO
		glGenBuffers(1, &wo.vbo); // Generate 1 buffer
		glBindBuffer(GL_ARRAY_BUFFER, wo.vbo);

		// Copy vertex data into VBO
		glBufferData(GL_ARRAY_BUFFER, wo.vboArray.size() * sizeof(float), wo.vboArray.data(), GL_STATIC_DRAW);
	}
}
