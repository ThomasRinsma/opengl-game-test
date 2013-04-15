#include "model.ih"

Model::~Model()
{
	for (WavefrontObject &wo : d_objects)
	{
		glDeleteBuffers(1, &wo.vbo);
		glDeleteVertexArrays(1, &wo.vao);
	}
}