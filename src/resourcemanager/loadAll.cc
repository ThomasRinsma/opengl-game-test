#include "resourcemanager.ih"

void ResourceManager::loadAll()
{
	loadModels();
	loadTextures();
	loadShaders();
}