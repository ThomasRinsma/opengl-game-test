#include "sceneobject.h"

using namespace std;

SceneObject::SceneObject(ShaderProgram &shaderProgram)
:
	Drawable(shaderProgram)
{}

SceneObject::~SceneObject()
{}