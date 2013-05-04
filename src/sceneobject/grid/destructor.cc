#include "grid.ih"

Grid::~Grid()
{
	glDeleteBuffers(1, &d_vbo);
	glDeleteVertexArrays(1, &d_vao);
}