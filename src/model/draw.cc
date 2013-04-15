#include "model.ih"

void Model::draw() const
{
	for (WavefrontObject const &wo : d_objects)
	{
		glBindVertexArray(wo.vao);
		//cout << "drawing " << wo.name << " with " << (wo.vboArray.size() / 8) << "vertices.\n";
		glDrawArrays(GL_TRIANGLES, 0, wo.vboArray.size() / 8);
	}
}