#include "genericmodel.ih"

string const requiredShader = "simpleTexture";

GenericModel::GenericModel(string const &texName, string const &modelName)
:
	SceneObject(ResourceManager::instance().shaderProgram(requiredShader)),
	d_model(ResourceManager::instance().model(modelName)),
	d_texture(ResourceManager::instance().texture(texName))
{
	d_model.initAttributes(d_shaderProgram);
}
