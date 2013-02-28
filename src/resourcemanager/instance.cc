#include "resourcemanager.ih"

ResourceManager &ResourceManager::instance()
{
	// guaranteed to be destroyed,
	// instantiated on first use
	static ResourceManager instance;

	return instance;
}