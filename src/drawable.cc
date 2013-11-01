#include "drawable.h"

using namespace std;

Drawable::Drawable(ShaderProgram &shaderProgram)
:
	d_shaderProgram(shaderProgram)
{}

Drawable::~Drawable()
{}

void Drawable::draw(glm::mat4 const &viewMat, glm::mat4 const &projMat)
{
	drawImpl(viewMat, projMat);
}