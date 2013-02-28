#include "resourcemanager.ih"

void ResourceManager::loadTextures()
{
	DIR *dir;
	struct dirent *ent;

	if ((dir = opendir(string(d_resourcePath + "textures").c_str())) != nullptr)
	{
		while ((ent = readdir(dir)) != nullptr)
		{
			string name(ent->d_name);
			
			if(name != "." and name != ".." and name.substr(name.length()-3, 3) == "png")
				load(Type::TEXTURE, name);
		}
		closedir(dir);
	}
	else
		throw string("texture folder not found at '" + d_resourcePath + "textures'.");
}