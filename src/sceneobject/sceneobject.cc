#include "sceneobject.ih"

SceneObject::SceneObject(ShaderProgram &shaderProgram)
:
	Drawable(shaderProgram)
{
	modelMatUpdated();
}