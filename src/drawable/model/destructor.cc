#include "model.ih"

Model::~Model()
{
	glDeleteTextures(1, &d_tex);
	glDeleteBuffers(1, &d_vbo);
	glDeleteVertexArrays(1, &d_vao);
}