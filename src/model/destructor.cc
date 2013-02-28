#include "model.ih"

Model::~Model()
{
	glDeleteBuffers(1, &d_vbo);
	glDeleteVertexArrays(1, &d_vao);
}