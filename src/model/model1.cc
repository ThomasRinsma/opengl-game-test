#include "model.ih"

Model::Model(std::string const &path)
{
	loadModel(path);

	// Create a VAO
	glGenVertexArrays(1, &d_vao);
	glBindVertexArray(d_vao);

	// Create a VBO
	glGenBuffers(1, &d_vbo); // Generate 1 buffer

	// Copy vertex data into VBO
	glBindBuffer(GL_ARRAY_BUFFER, d_vbo);
	glBufferData(GL_ARRAY_BUFFER, d_verts.size() * sizeof(float), d_verts.data(), GL_STATIC_DRAW);
}
