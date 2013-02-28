#include "resourcemanager.ih"

void ResourceManager::loadShaders()
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(string(d_resourcePath + "shaders").c_str())) != nullptr)
	{
		while ((ent = readdir(dir)) != nullptr)
		{
			string name(ent->d_name);
			
			if(name != "." and name != ".." and ent->d_type == DT_DIR)
				load(Type::SHADERPROGRAM, name);
		}
		closedir(dir);
	}
	else
		throw string("shaders folder not found at '" + d_resourcePath + "shaders'.");
}