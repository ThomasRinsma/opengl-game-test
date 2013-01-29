#include "text2d.ih"

Text2D::~Text2D()
{
	glDeleteTextures(1, &d_tex);
	glDeleteBuffers(1, &d_vbo);
	glDeleteVertexArrays(1, &d_vao);
}