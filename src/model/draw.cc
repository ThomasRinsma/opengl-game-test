#include "model.ih"

void Model::draw() const
{
	glBindVertexArray(d_vao);
	glDrawArrays(GL_TRIANGLES, 0, d_numVerts);
}