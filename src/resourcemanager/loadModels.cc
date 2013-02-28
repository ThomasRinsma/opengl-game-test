#include "resourcemanager.ih"

void ResourceManager::loadModels()
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(string(d_resourcePath + "models").c_str())) != nullptr)
	{
		while ((ent = readdir(dir)) != nullptr)
		{
			string name(ent->d_name);
			
			if(name != "." and name != ".." and name.substr(name.length()-3, 3) == "obj")
				load(Type::MODEL, name);
		}
		closedir(dir);
	}
	else
		throw string("model folder not found at '" + d_resourcePath + "models'.");
}